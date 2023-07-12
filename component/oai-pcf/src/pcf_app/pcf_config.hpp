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

/*! \file pcf_config.hpp
 \brief
 \author  Rohan Kharade
 \company Openairinterface Software Allianse
 \date 2022
 \email: rohan.kharade@openairinterface.org
*/

#ifndef FILE_PCF_CONFIG_HPP_SEEN
#define FILE_PCF_CONFIG_HPP_SEEN

#include "3gpp_29.510.h"
#include "logger.hpp"
#include <libconfig.h++>
#include <mutex>
#include <netinet/in.h>
#include <nlohmann/json.hpp>
#include <stdbool.h>
#include <stdint.h>
#include <string>
#include <unistd.h>

// using namespace oai::pcf::model;

#define PCF_CONFIG_STRING_PCF_CONFIG "PCF"
#define PCF_CONFIG_STRING_FQDN "FQDN"
#define PCF_CONFIG_STRING_PCF_SLICE_CONFIG "PCF_SLICE_CONFIG"
#define PCF_CONFIG_STRING_INTERFACES "INTERFACES"
#define PCF_CONFIG_STRING_INTERFACE_NAME "INTERFACE_NAME"
#define PCF_CONFIG_STRING_IPV4_ADDRESS "IPV4_ADDRESS"
#define PCF_CONFIG_STRING_SBI_PORT_HTTP1 "HTTP1_PORT"
#define PCF_CONFIG_STRING_SBI_PORT_HTTP2 "HTTP2_PORT"
#define PCF_CONFIG_STRING_SBI_INTERFACE "SBI"
#define PCF_CONFIG_STRING_API_VERSION "API_VERSION"

#define PCF_CONFIG_STRING_NETWORK_IPV4 "NETWORK_IPV4"
#define PCF_CONFIG_STRING_NETWORK_IPV6 "NETWORK_IPV6"
#define PCF_CONFIG_STRING_ADDRESS_PREFIX_DELIMITER "/"
#define PCF_CONFIG_STRING_ITTI_TASKS "ITTI_TASKS"
#define PCF_CONFIG_STRING_ITTI_TIMER_SCHED_PARAMS "ITTI_TIMER_SCHED_PARAMS"
#define PCF_CONFIG_STRING_SBI_SCHED_PARAMS "SBI_SCHED_PARAMS"

#define PCF_CONFIG_STRING_SUPPORT_FEATURES "SUPPORT_FEATURES"
#define PCF_CONFIG_STRING_SUPPORT_FEATURES_REGISTER_NRF "REGISTER_NRF"
#define PCF_CONFIG_STRING_NRF "NRF"
#define PCF_CONFIG_STRING_NRF_IPV4_ADDRESS "IPV4_ADDRESS"
#define PCF_CONFIG_STRING_NRF_PORT "PORT"
#define PCF_CONFIG_STRING_NRF_HTTP_VERSION "HTTP_VERSION"
#define PCF_CONFIG_STRING_SUPPORT_FEATURES_USE_HTTP2 "USE_HTTP2"
#define PCF_CONFIG_STRING_SUPPORT_FEATURES_USE_FQDN_DNS "USE_FQDN"

#define PCF_CONFIG_STRING_PCC_RULES_DIRECTORY "PCC_RULES_DIRECTORY"
#define PCF_CONFIG_STRING_POLICY_DECISIONS_DIRECTORY                           \
  "POLICY_DECISIONS_DIRECTORY"
#define PCF_CONFIG_STRING_TRAFFIC_RULES_DIRECTORY "TRAFFIC_RULES_DIRECTORY"

namespace oai::pcf::config {

typedef struct interface_cfg_s {
  std::string if_name;
  struct in_addr addr4;
  struct in_addr network4;
  struct in6_addr addr6;
  unsigned int mtu;
  unsigned int http1_port;
  unsigned int http2_port;
} interface_cfg_t;

class pcf_config {
 protected:
 private:
  int load_interface(const libconfig::Setting& if_cfg, interface_cfg_t& cfg);
  int check_directory(
      const libconfig::Setting& pcf_cfg, const std::string& path_config,
      std::string& path);

 public:
  /* Reader/writer lock for this configuration */
  std::mutex m_rw_lock;
  std::string pid_dir;
  unsigned int instance;
  std::string fqdn;
  interface_cfg_t sbi;
  std::string sbi_api_version;

  std::string gateway;

  std::string pcc_rules_path;
  std::string policy_decisions_path;
  std::string traffic_rules_path;

  struct {
    bool register_nrf;
    bool use_fqdn;
    bool use_http2;

    struct {
      struct in_addr ipv4_addr;
      unsigned int port;
      unsigned int http_version;
      std::string api_version;
      std::string fqdn;
    } nrf_addr;
  } pcf_features;

  struct {
    struct in_addr ipv4_addr;
    unsigned int port;
    unsigned int http_version;
    std::string api_version;
    std::string fqdn;
  } nrf_addr;

  // struct {
  //   struct in_addr ipv4_addr;
  //   unsigned int port;
  //   unsigned int http_version;
  //   std::string api_version;
  //   std::string fqdn;
  // } smf_addr;

  pcf_config() : m_rw_lock(), pid_dir(), instance(0) {
    sbi.http1_port = 8080;
    sbi.http2_port = 80;
  };

  void lock() { m_rw_lock.lock(); };
  void unlock() { m_rw_lock.unlock(); };
  int load(const std::string& config_file);
  int execute();
  void display();

  static bool parse_config();
};
}  // namespace oai::pcf::config

#endif /* FILE_PCF_CONFIG_HPP_SEEN */
