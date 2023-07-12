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

/*! \file 3gpp_conversions.hpp
 \brief
 \author
 \company Eurecom
 \email:
 */

#ifndef FILE_3GPP_CONVERSIONS_HPP_SEEN
#define FILE_3GPP_CONVERSIONS_HPP_SEEN

#include "AmfCreateEventSubscription.h"
#include "AmfEventReport.h"
#include "MonitoringEventReport.h"
#include "MonitoringEventSubscription.h"
#include "nef.h"

namespace xgpp_conv {

/*
 * Convert from a Monitoring Event Subscription to an AMF Event Subscription
 * @param [const oai::nef::model::MonitoringEventSubscription& ]
 * monitoring_event_sub: Monitoring Event Subscription
 * @param [oai::nef::model::AmfEventSubscription& ] amf_event_sub: AMF Event
 * Subscription
 * @return true if the conversion is successful, otherwise false
 */
bool monitoring_event_to_amf_event(
    const oai::nef::model::MonitoringEventSubscription& monitoring_event_sub,
    oai::nef::model::AmfCreateEventSubscription& amf_event_sub);

/*
 * Convert from an AMF Event Report to a Monitoring Event Report
 * @param [const oai::nef::model::AmfEventReport& ] amf_report: AMF Event Report
 * @param [oai::nef::model::MonitoringEventReport& ] monitoring_report:
 * Monitoring Event Report
 * @return true if the conversion is successful, otherwise false
 */
bool amf_report_to_monitoring_report(
    const oai::nef::model::AmfEventReport& amf_report,
    oai::nef::model::MonitoringEventReport& monitoring_report);

/*
 * Convert a string to Patch operation
 * @param [const std::string &] str: string input
 * @return the corresponding Patch operation
 */
patch_op_type_t string_to_patch_operation(const std::string& str);

}  // namespace xgpp_conv

#endif /* FILE_3GPP_CONVERSIONS_HPP_SEEN */
