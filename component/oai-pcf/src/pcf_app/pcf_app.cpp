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

/*! \file pcf_app.cpp
 \brief
 \author  Rohan Kharade
 \company Openairinterface Software Alliance
 \date 2022
 \email: rohan.kharade@openairinterface.org
 */

#include "pcf_app.hpp"
#include "pcf_nrf.hpp"
#include "logger.hpp"
#include "pcf_config.hpp"

#include <stdexcept>

using namespace oai::pcf::app;
using namespace oai::pcf::config;
using namespace oai::pcf::model;

using namespace std;

extern std::unique_ptr<pcf_config> pcf_cfg;

//------------------------------------------------------------------------------
pcf_app::pcf_app(pcf_event& ev) : m_event_sub(ev) {
  Logger::pcf_app().startup("Starting...");

  Logger::pcf_app().startup("Reading local Policy configuration...");
  m_policy_storage = std::make_shared<sm_policy::policy_storage>();

  m_provisioning_file =
      std::make_shared<sm_policy::policy_provisioning_file>(m_policy_storage);

  if (!m_provisioning_file->read_all_policy_files()) {
    Logger::pcf_app().error(
        "Cannot read policy configuration from file. Exiting");
    exit(-1);
  }

  // Register to NRF
  if (pcf_cfg->pcf_features.register_nrf) {
    m_pcf_nrf_inst = std::make_unique<pcf_nrf>(ev);
    m_pcf_nrf_inst->register_to_nrf();
    Logger::pcf_app().info("NRF TASK Created ");
  }

  m_pcf_smpc_service = std::make_shared<pcf_smpc>(m_policy_storage);
}

//------------------------------------------------------------------------------
pcf_app::~pcf_app() {
  Logger::pcf_app().debug("Delete PCF_APP instance...");
}

std::shared_ptr<pcf_smpc> pcf_app::get_pcf_smpc_service() {
  return m_pcf_smpc_service;
}

void pcf_app::stop() {
  if (m_pcf_nrf_inst) {
    m_pcf_nrf_inst->deregister_to_nrf();
  }
}