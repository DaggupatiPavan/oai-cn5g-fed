/*
 * NFEventNotifyApiImpl.h
 *
 *
 */

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

#ifndef NF_EVENT_NOTIFY_API_IMPL_H_
#define NF_EVENT_NOTIFY_API_IMPL_H_

#include <NFEventNotifyApi.h>
#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/optional.h>
#include <pistache/router.h>

#include <memory>

#include "ProblemDetails.h"
#include "nef_app.hpp"

namespace oai::nef::api {

using namespace oai::nef::model;

class NFEventNotifyApiImpl : public oai::nef::api::NFEventNotifyApi {
 public:
  NFEventNotifyApiImpl(
      std::shared_ptr<Pistache::Rest::Router>,
      oai::nef::app::nef_app* nef_app_inst, std::string address);
  ~NFEventNotifyApiImpl() {}

  void receive_nf_event_notification(
      const NefEventExposureNotif& eventExposureNotif,
      Pistache::Http::ResponseWriter& response);

  void receive_amf_event_notification(
      const AmfEventNotification& amfEventNotification,
      Pistache::Http::ResponseWriter& response);

  void receive_smf_event_notification(
      const NsmfEventExposureNotification& smfEventExposureNotification,
      Pistache::Http::ResponseWriter& response);

  void receive_udm_event_notification(
      const std::vector<MonitoringReport>& eventExposureNotif,
      Pistache::Http::ResponseWriter& response);

 private:
  oai::nef::app::nef_app* m_nef_app;
  std::string m_address;
};

}  // namespace oai::nef::api
#endif
