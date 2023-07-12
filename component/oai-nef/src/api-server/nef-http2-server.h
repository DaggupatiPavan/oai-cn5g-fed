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

/*! \file nef_http2-server.h
 \brief
 \author  Tien-Thinh NGUYEN
 \company Eurecom
 \date 2022
 \email: tien-thinh.nguyen@eurecom.fr
 */

#ifndef FILE_NEF_HTTP2_SERVER_SEEN
#define FILE_NEF_HTTP2_SERVER_SEEN

#include "conversions.hpp"

//#include "nef.h"
#include <nghttp2/asio_http2_server.h>

#include "nef_app.hpp"
#include "uint_generator.hpp"

using namespace nghttp2::asio_http2;
using namespace nghttp2::asio_http2::server;
// using namespace oai::nef::model;
using namespace oai::nef::app;

class nef_http2_server {
 public:
  nef_http2_server(std::string addr, uint32_t port, nef_app* nef_app_inst)
      : m_address(addr), m_port(port), server(), m_nef_app(nef_app_inst) {}
  void start();
  void init(size_t thr) {}

  void stop();

 private:
  util::uint_generator<uint32_t> m_promise_id_generator;
  std::string m_address;
  uint32_t m_port;
  http2 server;
  nef_app* m_nef_app;

 protected:
  static uint64_t generate_promise_id() {
    return util::uint_uid_generator<uint64_t>::get_instance().get_uid();
  }
};

#endif
