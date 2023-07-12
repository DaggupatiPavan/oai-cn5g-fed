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

/*! \file pcf_client.cpp
 \brief
 \author  Tien-Thinh NGUYEN
 \company Eurecom
 \date 2020
 \email: Tien-Thinh.Nguyen@eurecom.fr
 */

#include "pcf_client.hpp"

#include <curl/curl.h>

#include <nlohmann/json.hpp>
#include <stdexcept>

#include "logger.hpp"
#include "3gpp_29.500.h"
#include "pcf.h"
#include "pcf_config.hpp"

using namespace oai::pcf::app;
using json = nlohmann::json;

using namespace oai::pcf::config;
extern std::unique_ptr<pcf_config> pcf_cfg;

//------------------------------------------------------------------------------
// To read content of the response from NF
static std::size_t callback(
    const char* in, std::size_t size, std::size_t num, std::string* out) {
  const std::size_t totalBytes(size * num);
  out->append(in, totalBytes);
  return totalBytes;
}

//------------------------------------------------------------------------------
pcf_client::pcf_client() {
  curl_global_init(CURL_GLOBAL_ALL);
}

//------------------------------------------------------------------------------
pcf_client::~pcf_client() {
  curl_global_cleanup();
  Logger::pcf_app().debug("Delete PCF Client instance...");
}

http_status_code_e pcf_client::send_post(
    const std::string& url, const std::string& body, std::string& response,
    std::string& resp_headers) {
  return do_request(url, http_method_e::POST, body, response, resp_headers);
}

http_status_code_e pcf_client::send_get(
    const std::string& url, std::string& response, std::string& resp_header) {
  return do_request(url, http_method_e::GET, "", response, resp_header);
}

http_status_code_e pcf_client::send_put(
    const std::string& url, const std::string& body, std::string& response,
    std::string& resp_headers) {
  return do_request(url, http_method_e::PUT, body, response, resp_headers);
}

http_status_code_e pcf_client::send_patch(
    const std::string& url, const std::string& body, std::string& response,
    std::string& resp_headers) {
  return do_request(url, http_method_e::PATCH, body, response, resp_headers);
}

http_status_code_e pcf_client::send_delete(
    const std::string& url, std::string& response, std::string& resp_headers) {
  return do_request(url, http_method_e::DELETE, "", response, resp_headers);
}

http_status_code_e pcf_client::do_request(
    const std::string& url, const http_method_e& method,
    const std::string& body, std::string& response, std::string& resp_headers) {
  CURL* curl = curl_easy_init();
  if (!curl) {
    Logger::pcf_sbi().error("Could not create HTTP Client");
    return http_status_code_e::NO_RESPONSE;
  }
  prepare_curl_method(curl, method);

  // other CURL options
  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, NF_CURL_TIMEOUT_MS);
  curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1);
  curl_easy_setopt(curl, CURLOPT_INTERFACE, pcf_cfg->sbi.if_name.c_str());

  if (pcf_cfg->pcf_features.use_http2) {
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    // we use a self-signed test server, skip verification during debugging
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(
        curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE);
  }

  // Custom headers
  struct curl_slist* headers = nullptr;
  if (!body.empty()) {
    std::string content_type = "Content-Type: application/json";
    headers                  = curl_slist_append(headers, content_type.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body.length());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
  }
  // to prevent splitting it into two HTTP messages
  headers = curl_slist_append(headers, "Expect: ");

  // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);

  std::string body_response;
  std::string http_headers_response;

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &body_response);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, &http_headers_response);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK) {
    Logger::pcf_sbi().warn(
        "Could not perform HTTP request to %s. CURL Error code: %d",
        url.c_str(), res);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    return http_status_code_e::NO_RESPONSE;
  }
  long http_code = -1;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

  response.append(body_response);
  resp_headers.append(http_headers_response);

  curl_slist_free_all(headers);
  curl_easy_cleanup(curl);

  return http_status_code_e(http_code);
}

void pcf_client::prepare_curl_method(CURL*& curl, const http_method_e& method) {
  switch (method) {
    case http_method_e::GET:
      curl_easy_setopt(curl, CURLOPT_HTTPGET, 1);
      break;
    case http_method_e::POST:
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, 1);
      break;
    case http_method_e::PATCH:
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PATCH");
      break;
    case http_method_e::PUT:
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
      break;
    case http_method_e::DELETE:
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
      break;
  }
}
