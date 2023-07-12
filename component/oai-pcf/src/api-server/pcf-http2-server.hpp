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

#ifndef FILE_PCF_HTTP2_SERVER_SEEN
#define FILE_PCF_HTTP2_SERVER_SEEN

#include "conversions.hpp"
#include "pcf.h"
#include "pcf_app.hpp"
#include "string.hpp"
#include "uint_generator.hpp"
#include <nghttp2/asio_http2_server.h>
#include "IndividualSMPolicyDocumentApiImpl.h"
#include "SMPoliciesCollectionApiImpl.h"

class pcf_http2_server {
 public:
  pcf_http2_server(
      const std::string& addr, uint32_t port,
      const std::unique_ptr<oai::pcf::app::pcf_app>& pcf_app_inst)
      : m_address(addr),
        m_port(port),
        server(),
        smpc_service(pcf_app_inst->get_pcf_smpc_service()){};

  void start();
  void init(size_t /* thr */) {}

  // PCF

  void stop();

 private:
  util::uint_generator<uint32_t> m_promise_id_generator;
  std::string m_address;
  uint32_t m_port;

  nghttp2::asio_http2::server::http2 server;

  std::shared_ptr<oai::pcf::app::pcf_smpc> smpc_service;
};

#endif
