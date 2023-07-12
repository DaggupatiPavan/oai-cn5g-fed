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

#include "NFEventNotifyApi.h"

#include "Helpers.h"
#include "logger.hpp"
#include "nef_config.hpp"
extern oai::nef::app::nef_config nef_cfg;

namespace oai::nef::api {

using namespace oai::nef::helpers;
using namespace oai::nef::model;
const std::string NFEventNotifyApi::base = "/nnef-nfevent-notify/";

NFEventNotifyApi::NFEventNotifyApi(
    std::shared_ptr<Pistache::Rest::Router> rtr) {
  router = rtr;
}

void NFEventNotifyApi::init() {
  setupRoutes();
}

void NFEventNotifyApi::setupRoutes() {
  using namespace Pistache::Rest;

  Routes::Post(
      *router, base + nef_cfg.sbi.api_version + "/udm",
      Routes::bind(&NFEventNotifyApi::notify_udm_event_handler, this));

  Routes::Post(
      *router, base + nef_cfg.sbi.api_version + "/amf",
      Routes::bind(&NFEventNotifyApi::notify_amf_event_handler, this));

  Routes::Post(
      *router, base + nef_cfg.sbi.api_version + "/smf",
      Routes::bind(&NFEventNotifyApi::notify_smf_event_handler, this));

  /*//TODO:
  Routes::Post(
      *router, base + "/notify",
      Routes::bind(&NFEventNotifyApi::notify_nf_event_change_handler, this));
  */

  // Default handler, called when a route is not found
  router->addCustomHandler(
      Routes::bind(&NFEventNotifyApi::notify_nf_event_default_handler, this));
}

void NFEventNotifyApi::notify_udm_event_handler(
    const Pistache::Rest::Request& request,
    Pistache::Http::ResponseWriter response) {
  // Getting the body param

  std::vector<MonitoringReport> monitoring_reports;
  try {
    nlohmann::json::parse(request.body()).get_to(monitoring_reports);
    this->receive_udm_event_notification(monitoring_reports, response);
  } catch (nlohmann::detail::exception& e) {
    // send a 400 error
    response.send(Pistache::Http::Code::Bad_Request, e.what());
    return;
  } catch (Pistache::Http::HttpError& e) {
    response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
    return;
  } catch (std::exception& e) {
    // send a 500 error
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
    return;
  }
}

void NFEventNotifyApi::notify_amf_event_handler(
    const Pistache::Rest::Request& request,
    Pistache::Http::ResponseWriter response) {
  // Getting the body param
  AmfEventNotification amfEventNotification;

  try {
    nlohmann::json::parse(request.body()).get_to(amfEventNotification);
    this->receive_amf_event_notification(amfEventNotification, response);
  } catch (nlohmann::detail::exception& e) {
    // send a 400 error
    response.send(Pistache::Http::Code::Bad_Request, e.what());
    return;
  } catch (Pistache::Http::HttpError& e) {
    response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
    return;
  } catch (std::exception& e) {
    // send a 500 error
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
    return;
  }
}

void NFEventNotifyApi::notify_smf_event_handler(
    const Pistache::Rest::Request& request,
    Pistache::Http::ResponseWriter response) {
  // Getting the body param
  NsmfEventExposureNotification smfEventExposureNotification;

  try {
    nlohmann::json::parse(request.body()).get_to(smfEventExposureNotification);
    this->receive_smf_event_notification(
        smfEventExposureNotification, response);
  } catch (nlohmann::detail::exception& e) {
    // send a 400 error
    response.send(Pistache::Http::Code::Bad_Request, e.what());
    return;
  } catch (Pistache::Http::HttpError& e) {
    response.send(static_cast<Pistache::Http::Code>(e.code()), e.what());
    return;
  } catch (std::exception& e) {
    // send a 500 error
    response.send(Pistache::Http::Code::Internal_Server_Error, e.what());
    return;
  }
}

void NFEventNotifyApi::notify_nf_event_default_handler(
    const Pistache::Rest::Request&, Pistache::Http::ResponseWriter response) {
  response.send(
      Pistache::Http::Code::Not_Found, "The requested method does not exist");
}

}  // namespace oai::nef::api
