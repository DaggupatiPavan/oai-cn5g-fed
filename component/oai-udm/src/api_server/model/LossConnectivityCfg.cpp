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
/**
 * Nudm_EE
 * Nudm Event Exposure Service. © 2021, 3GPP Organizational Partners (ARIB,
 * ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.2.0-alpha.3
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "LossConnectivityCfg.h"
#include "Helpers.h"

#include <sstream>

namespace oai::udm::model {

LossConnectivityCfg::LossConnectivityCfg() {
  m_MaxDetectionTime      = 0;
  m_MaxDetectionTimeIsSet = false;
}

void LossConnectivityCfg::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw oai::udm::helpers::ValidationException(msg.str());
  }
}

bool LossConnectivityCfg::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool LossConnectivityCfg::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "LossConnectivityCfg" : pathPrefix;

  return success;
}

bool LossConnectivityCfg::operator==(const LossConnectivityCfg& rhs) const {
  return

      ((!maxDetectionTimeIsSet() && !rhs.maxDetectionTimeIsSet()) ||
       (maxDetectionTimeIsSet() && rhs.maxDetectionTimeIsSet() &&
        getMaxDetectionTime() == rhs.getMaxDetectionTime()))

          ;
}

bool LossConnectivityCfg::operator!=(const LossConnectivityCfg& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const LossConnectivityCfg& o) {
  j = nlohmann::json();
  if (o.maxDetectionTimeIsSet()) j["maxDetectionTime"] = o.m_MaxDetectionTime;
}

void from_json(const nlohmann::json& j, LossConnectivityCfg& o) {
  if (j.find("maxDetectionTime") != j.end()) {
    j.at("maxDetectionTime").get_to(o.m_MaxDetectionTime);
    o.m_MaxDetectionTimeIsSet = true;
  }
}

int32_t LossConnectivityCfg::getMaxDetectionTime() const {
  return m_MaxDetectionTime;
}
void LossConnectivityCfg::setMaxDetectionTime(int32_t const value) {
  m_MaxDetectionTime      = value;
  m_MaxDetectionTimeIsSet = true;
}
bool LossConnectivityCfg::maxDetectionTimeIsSet() const {
  return m_MaxDetectionTimeIsSet;
}
void LossConnectivityCfg::unsetMaxDetectionTime() {
  m_MaxDetectionTimeIsSet = false;
}

}  // namespace oai::udm::model
