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

#ifndef FILE_PCF_SEEN
#define FILE_PCF_SEEN

#include "3gpp_29.571.h"
#include <nlohmann/json.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HEART_BEAT_TIMER 10

#define _unused(x) ((void) (x))

// typedef struct dnn_pcf_info_item_s {
//   std::string dnn;
// } dnn_pcf_info_item_t;

typedef struct supi_range_s {
  std::string start;
  std::string end;
  std::string pattern;
} supi_range_t;

typedef struct supi_range_pcf_info_item_s {
  supi_range_t supi_range;
} supi_range_pcf_info_item_t;

typedef struct identity_range_s {
  std::string start;
  std::string end;
  std::string pattern;
} identity_range_t;

typedef struct identity_range_pcf_info_item_s {
  identity_range_t identity_range;
} identity_range_pcf_info_item_t;

typedef struct pcf_info_s {
  std::string groupid;
  std::vector<supi_range_pcf_info_item_t> supi_ranges;
  std::vector<identity_range_pcf_info_item_t> gpsi_ranges;
  std::vector<std::string> dnn_list;
} pcf_info_t;

typedef struct nf_service_version_s {
  std::string api_version_in_uri;  // apiVersionInUri
  std::string api_full_version;    // apiFullVersion

  nf_service_version_s& operator=(const nf_service_version_s& s) {
    api_version_in_uri = s.api_version_in_uri;
    api_full_version   = s.api_full_version;
    return *this;
  }

  std::string to_string() const {
    std::string s = {};
    s.append(", Version (");
    s.append("apiVersionInUri: ");
    s.append(api_version_in_uri);
    s.append(", apiFullVersion: ");
    s.append(api_full_version);
    s.append(" )");
    return s;
  }
} nf_service_version_t;

typedef struct ip_endpoint_s {
  // struct in6_addr  ipv6_address;
  struct in_addr ipv4_address;
  std::string transport;  // TCP
  unsigned int port;
  std::string to_string() const {
    std::string s = {};
    s.append("Ipv4 Address: ");
    s.append(inet_ntoa(ipv4_address));
    s.append(", TransportProtocol: ");
    s.append(transport);
    s.append(", Port: ");
    s.append(std::to_string(port));
    return s;
  }
} ip_endpoint_t;

typedef struct nf_service_s {
  std::string service_instance_id;
  std::string service_name;
  std::vector<nf_service_version_t> versions;
  std::string scheme;
  std::string nf_service_status;
  std::vector<ip_endpoint_t> ip_endpoints;

  std::string to_string() const {
    std::string s = {};
    s.append("Service Instance ID: ");
    s.append(service_instance_id);
    s.append(", Service name: ");
    s.append(service_name);
    for (auto const& v : versions) {
      s.append(v.to_string());
    }
    s.append(", Scheme: ");
    s.append(scheme);
    s.append(", Service status: ");
    s.append(nf_service_status);
    s.append(",  IpEndPoints: ");
    for (auto endpoint : ip_endpoints) {
      s.append(endpoint.to_string());
    }
    return s;
  }
} nf_service_t;

#define ROAMING_IND_NON_ROAMING (1)
#define ROAMING_IND_LOCAL_BREAKOUT (2)
#define ROAMING_IND_HOME_ROUTED_ROAMING (3)

// NF TYPES
#define NF_TYPE_NWDAP "NWDAP"
#define NF_TYPE_PCF "PCF"
#define NF_TYPE_PCF "PCF"
#define NF_TYPE_AMF "AMF"

// NRF
#define NNRF_NFM_BASE "/nnrf-nfm/"
#define NNRF_DISC_INSTANCES "/nf-instances/"
#define NNRF_NF_STATUS_SUBSCRIBE_URL "/subscriptions"

// for CURL
#define NF_CURL_TIMEOUT_MS 100L
#define MAX_WAIT_MSECS 10000  // 1 second
#define AMF_NUMBER_RETRIES 3
#define UDM_NUMBER_RETRIES 3

#define SM_POLICY_API_NAME "npcf-smpolicycontrol";

#endif
