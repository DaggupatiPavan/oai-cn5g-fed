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

/*! \file pcf_client.hpp
 \author  Tien-Thinh NGUYEN
 \company Eurecom
 \date 2020
 \email: Tien-Thinh.Nguyen@eurecom.fr
 */

#pragma once

#include <curl/curl.h>

#include <map>
#include <thread>
#include "3gpp_29.500.h"

namespace oai::pcf::app {

enum class http_method_e { POST, GET, PUT, PATCH, DELETE };

class pcf_client_iface {
 public:
  /**
   * Send a POST request to the URl specified in url
   * @param url URL to send the request to
   * @param body body to send in JSON representation
   * @param response Response
   * @param resp_headers Response headers
   * @return HTTP response code
   */
  virtual http_status_code_e send_post(
      const std::string& url, const std::string& body, std::string& response,
      std::string& resp_headers) = 0;

  /**
   * Send a GET request to the URL specified in url
   * @param url URL to send the request to
   * @param response
   * @param resp_header
   * @return HTTP response code
   */
  virtual http_status_code_e send_get(
      const std::string& url, std::string& response,
      std::string& resp_header) = 0;

  /**
   * Send a PUT request to the URL specified in url
   * @param url URL to send the request to
   * @param body body to send in JSON representation
   * @param response Response
   * @param resp_headers Response headers
   * @return HTTP response code
   */
  virtual http_status_code_e send_put(
      const std::string& url, const std::string& body, std::string& response,
      std::string& resp_headers) = 0;

  /**
   * Send a PATCH request to the URL specified in url
   * @param url URL to send the request to
   * @param body body to send in JSON representation
   * @param response Response
   * @param resp_headers Response headers
   * @return HTTP response code
   */
  virtual http_status_code_e send_patch(
      const std::string& url, const std::string& body, std::string& response,
      std::string& resp_headers) = 0;

  /**
   * Send a DELETE request to the URL specified in url
   * @param url URL to send the request to
   * @param response Response
   * @param resp_headers Response headers
   * @return HTTP response code
   */
  virtual http_status_code_e send_delete(
      const std::string& url, std::string& response,
      std::string& resp_headers) = 0;
};

class pcf_client : pcf_client_iface {
 private:
  static http_status_code_e do_request(
      const std::string& url, const http_method_e& method,
      const std::string& body, std::string& response,
      std::string& resp_headers);

  static void prepare_curl_method(CURL*& curl, const http_method_e& method);

 public:
  pcf_client();
  virtual ~pcf_client();

  http_status_code_e send_post(
      const std::string& url, const std::string& body, std::string& response,
      std::string& resp_headers) override;

  http_status_code_e send_get(
      const std::string& url, std::string& response,
      std::string& resp_header) override;

  http_status_code_e send_put(
      const std::string& url, const std::string& body, std::string& response,
      std::string& resp_headers) override;

  http_status_code_e send_patch(
      const std::string& url, const std::string& body, std::string& response,
      std::string& resp_headers) override;

  http_status_code_e send_delete(
      const std::string& url, std::string& response,
      std::string& resp_headers) override;

  pcf_client(pcf_client const&) = delete;
};
}  // namespace oai::pcf::app
