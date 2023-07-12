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

/*! \file pcf_http2-server.h
 \brief
 \author  Rohan Kharade
 \company Openairinterface Software Allianse
 \date 2022
 \email: rohan.kharade@openairinterface.org
 */

#include "pcf-http2-server.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#include <boost/thread/future.hpp>
#include <nlohmann/json.hpp>
#include <regex>
#include <string>

#include "3gpp_29.500.h"
#include "logger.hpp"
#include "pcf.h"
#include "pcf_config.hpp"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
using namespace oai::pcf::model;
using namespace oai::pcf::config;

extern std::unique_ptr<pcf_config> pcf_cfg;

//------------------------------------------------------------------------------
void pcf_http2_server::start() {
  boost::system::error_code ec;

  Logger::pcf_sbi().info("HTTP2 server started");
  std::string nfId           = {};
  std::string subscriptionID = {};

  // Get list of supported APIs
  server.handle(
      "/", [&](const request& request, const response& /* response */) {
        request.on_data([&](const uint8_t* /* data */, std::size_t /* len */) {
          if (request.method().compare("GET") == 0) {
            // this->get_api_list(response);
          }
        });
      });

  if (server.listen_and_serve(ec, m_address, std::to_string(m_port))) {
    std::cerr << "HTTP Server error: " << ec.message() << std::endl;
  }
}

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// void pcf_http2_server::get_api_list(const response &response) {
//   int http_code = 0;
//   nlohmann::json json_data = {};
//   std::string content_type = "application/json";
//   header_map h;
//   h.emplace("content-type", header_value{content_type});
//   if (pcf_cfg.get_api_list(json_data)) {
//     http_code = HTTP_STATUS_CODE_200_OK;
//     response.write_head(http_code, h);
//     response.end(json_data.dump(4).c_str());
//   } else {
//     http_code = HTTP_STATUS_CODE_503_SERVICE_UNAVAILABLE;
//     response.write_head(http_code, h);
//     response.end();
//   }
// }
//------------------------------------------------------------------------------
void pcf_http2_server::stop() {
  server.stop();
}
