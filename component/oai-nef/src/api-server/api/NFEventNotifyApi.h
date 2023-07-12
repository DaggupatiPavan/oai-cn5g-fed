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

/*
 * NFEventNotifyApi.h
 *
 *
 */

#ifndef NFEventNotifyApi_H_
#define NFEventNotifyApi_H_

#include <pistache/http.h>
#include <pistache/http_headers.h>
#include <pistache/optional.h>
#include <pistache/router.h>

#include "AmfEventNotification.h"
#include "MonitoringReport.h"
#include "NefEventExposureNotif.h"
#include "NsmfEventExposureNotification.h"
#include "ProblemDetails.h"

namespace oai::nef::api {

using namespace oai::nef::model;

class NFEventNotifyApi {
 public:
  NFEventNotifyApi(std::shared_ptr<Pistache::Rest::Router>);
  virtual ~NFEventNotifyApi() {}
  void init();
  static const std::string base;

 private:
  void setupRoutes();

  void notify_udm_event_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);
  void notify_amf_event_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);
  void notify_smf_event_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);

  void notify_nf_event_default_handler(
      const Pistache::Rest::Request& request,
      Pistache::Http::ResponseWriter response);

  std::shared_ptr<Pistache::Rest::Router> router;

  /// <summary>
  ///
  /// </summary>
  /// <remarks>
  ///
  /// </remarks>
  /// <param name="NefEventExposureNotif"></param>
  virtual void receive_nf_event_notification(
      const NefEventExposureNotif& eventExposureNotif,
      Pistache::Http::ResponseWriter& response) = 0;

  virtual void receive_amf_event_notification(
      const AmfEventNotification& amfEventNotification,
      Pistache::Http::ResponseWriter& response) = 0;

  virtual void receive_smf_event_notification(
      const NsmfEventExposureNotification& smfEventExposureNotification,
      Pistache::Http::ResponseWriter& response) = 0;

  virtual void receive_udm_event_notification(
      const std::vector<MonitoringReport>& eventExposureNotif,
      Pistache::Http::ResponseWriter& response) = 0;
};

}  // namespace oai::nef::api

#endif /* NFEventNotifyApi_H_ */
