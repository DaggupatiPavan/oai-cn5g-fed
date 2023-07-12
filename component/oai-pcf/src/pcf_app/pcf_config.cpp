/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

/*! \file pcf_config.cpp
 \brief
 \author  Rohan Kharade
 \company Openairinterface Software Allianse
 \date 2022
 \email: rohan.kharade@openairinterface.org
*/

#include "pcf_config.hpp"
#include "common_defs.h"
#include "conversions.hpp"
#include "if.hpp"
#include "string.hpp"
#include "fqdn.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace libconfig;

namespace oai::pcf::config {
// C includes
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

//------------------------------------------------------------------------------
// int pcf_config::execute() { return RETURNok; }

//------------------------------------------------------------------------------
int pcf_config::load_interface(const Setting& if_cfg, interface_cfg_t& cfg) {
  if_cfg.lookupValue(PCF_CONFIG_STRING_INTERFACE_NAME, cfg.if_name);
  util::trim(cfg.if_name);
  if (not boost::iequals(cfg.if_name, "none")) {
    std::string address = {};
    if_cfg.lookupValue(PCF_CONFIG_STRING_IPV4_ADDRESS, address);
    util::trim(address);
    if (boost::iequals(address, "read")) {
      if (get_inet_addr_infos_from_iface(
              cfg.if_name, cfg.addr4, cfg.network4, cfg.mtu)) {
        Logger::pcf_app().error(
            "Could not read %s network interface configuration", cfg.if_name);
        return RETURNerror;
      }
    } else {
      std::vector<std::string> words;
      boost::split(
          words, address, boost::is_any_of("/"), boost::token_compress_on);
      if (words.size() != 2) {
        Logger::pcf_app().error(
            "Bad value " PCF_CONFIG_STRING_IPV4_ADDRESS " = %s in config file",
            address.c_str());
        return RETURNerror;
      }
      unsigned char buf_in_addr[sizeof(struct in6_addr)];  // you never know...
      if (inet_pton(AF_INET, util::trim(words.at(0)).c_str(), buf_in_addr) ==
          1) {
        memcpy(&cfg.addr4, buf_in_addr, sizeof(struct in_addr));
      } else {
        Logger::pcf_app().error(
            "In conversion: Bad value " PCF_CONFIG_STRING_IPV4_ADDRESS
            " = %s in config file",
            util::trim(words.at(0)).c_str());
        return RETURNerror;
      }
      cfg.network4.s_addr = htons(
          ntohs(cfg.addr4.s_addr) &
          0xFFFFFFFF << (32 - std::stoi(util::trim(words.at(1)))));
    }
    if_cfg.lookupValue(PCF_CONFIG_STRING_SBI_PORT_HTTP1, cfg.http1_port);
    if_cfg.lookupValue(PCF_CONFIG_STRING_SBI_PORT_HTTP2, cfg.http2_port);
  }
  return RETURNok;
}
//------------------------------------------------------------------------------
int pcf_config::check_directory(
    const Setting& pcf_cfg, const std::string& path_config, std::string& path) {
  try {
    pcf_cfg.lookupValue(path_config, path);

    struct stat info;
    if (stat(path.c_str(), &info) != 0) {
      Logger::pcf_app().info("Path %s cannot be accessed.", path.c_str());
      return RETURNerror;
    } else if (!(info.st_mode & S_IFDIR)) {
      Logger::pcf_app().info("Path %s is not a directory.", path.c_str());
      return RETURNerror;
    }
  } catch (const SettingNotFoundException& nfex) {
    Logger::pcf_app().info("Configuration %s is not set.", path_config.c_str());
    return RETURNerror;
  }
  return RETURNok;
}
//------------------------------------------------------------------------------
int pcf_config::load(const string& config_file) {
  Config cfg;

  // Read the file. If there is an error, report it and exit.
  try {
    cfg.readFile(config_file.c_str());
  } catch (const FileIOException& fioex) {
    Logger::pcf_app().error(
        "I/O error while reading file %s - %s", config_file.c_str(),
        fioex.what());
    throw;
  } catch (const ParseException& pex) {
    Logger::pcf_app().error(
        "Parse error at %s:%d - %s", pex.getFile(), pex.getLine(),
        pex.getError());
    throw;
  }

  const Setting& root = cfg.getRoot();

  if (root.exists(PCF_CONFIG_STRING_PCF_CONFIG) == false) {
    Logger::pcf_app().error(
        "Setting does not exist: " + std::string{PCF_CONFIG_STRING_PCF_CONFIG});
    return RETURNerror;
  }

  const Setting& pcf_cfg = root[PCF_CONFIG_STRING_PCF_CONFIG];

  try {
    pcf_cfg.lookupValue(PCF_CONFIG_STRING_FQDN, fqdn);
    util::trim(fqdn);
  } catch (const SettingNotFoundException& nfex) {
    Logger::pcf_app().info(
        "%s : %s, No FQDN configured", nfex.what(), nfex.getPath());
  }

  if (check_directory(
          pcf_cfg, PCF_CONFIG_STRING_PCC_RULES_DIRECTORY, pcc_rules_path) !=
      RETURNok) {
    Logger::pcf_app().error(
        "PCC Rules Path is not set or not a valid directory. Exiting");
    return RETURNerror;
  }
  if (check_directory(
          pcf_cfg, PCF_CONFIG_STRING_POLICY_DECISIONS_DIRECTORY,
          policy_decisions_path) != RETURNok) {
    Logger::pcf_app().error(
        "Policy Decisions Path is not set or not a valid directory. Exiting");
    return RETURNerror;
  }
  if (check_directory(
          pcf_cfg, PCF_CONFIG_STRING_TRAFFIC_RULES_DIRECTORY,
          traffic_rules_path) != RETURNok) {
    Logger::pcf_app().warn(
        "Traffic Rules Path is not set or not a valid directory. This feature "
        "is disabled.");
  }

  try {
    const Setting& nw_if_cfg = pcf_cfg[PCF_CONFIG_STRING_INTERFACES];

    const Setting& sbi_cfg = nw_if_cfg[PCF_CONFIG_STRING_SBI_INTERFACE];
    load_interface(sbi_cfg, sbi);

    sbi_cfg.lookupValue(PCF_CONFIG_STRING_API_VERSION, sbi_api_version);
  } catch (const SettingNotFoundException& nfex) {
    Logger::pcf_app().error("%s : %s", nfex.what(), nfex.getPath());
    return RETURNerror;
  }
  // Support features
  try {
    const Setting& support_features =
        pcf_cfg[PCF_CONFIG_STRING_SUPPORT_FEATURES];
    string opt;
    support_features.lookupValue(
        PCF_CONFIG_STRING_SUPPORT_FEATURES_REGISTER_NRF, opt);
    if (boost::iequals(opt, "yes")) {
      pcf_features.register_nrf = true;
    } else {
      pcf_features.register_nrf = false;
    }

    support_features.lookupValue(
        PCF_CONFIG_STRING_SUPPORT_FEATURES_USE_FQDN_DNS, opt);
    if (boost::iequals(opt, "yes")) {
      pcf_features.use_fqdn = true;
    } else {
      pcf_features.use_fqdn = false;
    }

    support_features.lookupValue(
        PCF_CONFIG_STRING_SUPPORT_FEATURES_USE_HTTP2, opt);
    if (boost::iequals(opt, "yes")) {
      pcf_features.use_http2 = true;
    } else {
      pcf_features.use_http2 = false;
    }

  } catch (const SettingNotFoundException& nfex) {
    Logger::pcf_app().error(
        "%s : %s, using defaults", nfex.what(), nfex.getPath());
    return -1;
  }
  try {
    string astring = {};

    // NRF
    if (pcf_features.register_nrf) {
      const Setting& nrf_cfg       = pcf_cfg[PCF_CONFIG_STRING_NRF];
      struct in_addr nrf_ipv4_addr = {};
      unsigned int nrf_port        = {0};
      std::string nrf_api_version  = {};

      if (!pcf_features.use_fqdn) {
        nrf_cfg.lookupValue(PCF_CONFIG_STRING_NRF_IPV4_ADDRESS, astring);
        IPV4_STR_ADDR_TO_INADDR(
            util::trim(astring).c_str(), nrf_ipv4_addr,
            "BAD IPv4 ADDRESS FORMAT FOR NRF !");
        nrf_addr.ipv4_addr = nrf_ipv4_addr;
        if (!(nrf_cfg.lookupValue(PCF_CONFIG_STRING_NRF_PORT, nrf_port))) {
          Logger::pcf_app().error(PCF_CONFIG_STRING_NRF_PORT "failed");
          throw(PCF_CONFIG_STRING_NRF_PORT "failed");
        }
        nrf_addr.port = nrf_port;

        if (!(nrf_cfg.lookupValue(
                PCF_CONFIG_STRING_API_VERSION, nrf_api_version))) {
          Logger::pcf_app().error(PCF_CONFIG_STRING_API_VERSION "failed");
          throw(PCF_CONFIG_STRING_API_VERSION "failed");
        }
        nrf_addr.api_version = nrf_api_version;
      } else {
        nrf_cfg.lookupValue(PCF_CONFIG_STRING_FQDN, astring);
        uint8_t addr_type   = {0};
        std::string address = {};
        fqdn::resolve(astring, address, nrf_port, addr_type);
        if (addr_type != 0) {  // IPv6
          // TODO:
          throw("DO NOT SUPPORT IPV6 ADDR FOR NRF!");
        } else {  // IPv4
          IPV4_STR_ADDR_TO_INADDR(
              util::trim(address).c_str(), nrf_ipv4_addr,
              "BAD IPv4 ADDRESS FORMAT FOR NRF !");
          nrf_addr.ipv4_addr = nrf_ipv4_addr;
          // nrf_addr.port        = nrf_port;
          // We hardcode nrf port from config for the moment
          if (!(nrf_cfg.lookupValue(PCF_CONFIG_STRING_NRF_PORT, nrf_port))) {
            Logger::pcf_app().error(PCF_CONFIG_STRING_NRF_PORT "failed");
            throw(PCF_CONFIG_STRING_NRF_PORT "failed");
          }
          nrf_addr.port        = nrf_port;
          nrf_addr.api_version = "v1";  // TODO: to get API version from DNS
          nrf_addr.fqdn        = astring;
        }
      }
    }
  } catch (const SettingNotFoundException& nfex) {
    Logger::pcf_app().error("%s : %s", nfex.what(), nfex.getPath());
    return RETURNerror;
  }
  return RETURNok;
}

//------------------------------------------------------------------------------
void pcf_config::display() {
  Logger::pcf_app().info(
      "==== OPENAIRINTERFACE %s v%s ====", PACKAGE_NAME, PACKAGE_VERSION);
  Logger::pcf_app().info("Configuration:");
  Logger::pcf_app().info("- FQDN ..................: %s", fqdn.c_str());
  Logger::pcf_app().info(
      "- Policies Path..........: %s", policy_decisions_path.c_str());
  Logger::pcf_app().info(
      "- PCC Rules Path.........: %s", pcc_rules_path.c_str());
  Logger::pcf_app().info(
      "- Traffic Rules Path.....: %s", traffic_rules_path.c_str());

  Logger::pcf_app().info("- SBI:");
  Logger::pcf_app().info("    iface ............: %s", sbi.if_name.c_str());
  Logger::pcf_app().info("    ipv4.addr ........: %s", inet_ntoa(sbi.addr4));
  Logger::pcf_app().info("    ipv4.mask ........: %s", inet_ntoa(sbi.network4));
  Logger::pcf_app().info("    mtu ..............: %d", sbi.mtu);
  Logger::pcf_app().info("    http1_port .......: %u", sbi.http1_port);
  Logger::pcf_app().info("    http2_port .......: %u", sbi.http2_port);
  Logger::pcf_app().info("    api_version ......: %s", sbi_api_version.c_str());
  if (pcf_features.register_nrf) {
    Logger::pcf_app().info("- NRF:");
    Logger::pcf_app().info(
        "    IPv4 Addr ...........: %s",
        inet_ntoa(*((struct in_addr*) &nrf_addr.ipv4_addr)));
    Logger::pcf_app().info("    Port ................: %lu  ", nrf_addr.port);
    Logger::pcf_app().info(
        "    API version .........: %s", nrf_addr.api_version.c_str());
    if (pcf_features.use_fqdn)
      Logger::pcf_app().info(
          "    FQDN ................: %s", nrf_addr.fqdn.c_str());
  }
  Logger::pcf_app().info("- Supported Features:");
  Logger::pcf_app().info(
      "    Register to NRF........: %s",
      pcf_features.register_nrf ? "Yes" : "No");
  Logger::pcf_app().info(
      "    Use FQDN ..............: %s", pcf_features.use_fqdn ? "Yes" : "No");
  Logger::pcf_app().info(
      "    Use HTTP2..............: %s", pcf_features.use_http2 ? "Yes" : "No");
}

//------------------------------------------------------------------------------
// bool pcf_config::get_slice_config(nlohmann::json& slice_config) {
//   slice_config = pcf_slice_config;
//   return true;
// }

//------------------------------------------------------------------------------
// bool pcf_config::get_api_list(nlohmann::json &api_list) {
//   api_list["OAI-PCF"] = {
//       {"Organisation", "Openairinterface Software Aliance"},
//       {"Description", "OAI-PCF initial Release"},
//       {"Version", "1.0.0"},
//       {"Supported APIs",
//        {{"API", "Network Slice Information (Document)"},
//         {"Method", "GET"},
//         {"URI Path",
//          "/npcf-nsselection/<api_version>/network-slice-information"},
//         {"Details",
//          "Retrieve the Network Slice Selection Information (PDU
//          Session)"}}}};
//   return true;
// }
//------------------------------------------------------------------------------

}  // namespace oai::pcf::config
