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
 * Nudr_DataRepository API OpenAPI file
 * Unified Data Repository Service. © 2020, 3GPP Organizational Partners (ARIB,
 * ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 2.1.2
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "ServiceAreaRestriction.h"

namespace oai::udr::model {

ServiceAreaRestriction::ServiceAreaRestriction() {
  m_RestrictionTypeIsSet               = false;
  m_AreasIsSet                         = false;
  m_MaxNumOfTAs                        = 0;
  m_MaxNumOfTAsIsSet                   = false;
  m_MaxNumOfTAsForNotAllowedAreas      = 0;
  m_MaxNumOfTAsForNotAllowedAreasIsSet = false;
}

ServiceAreaRestriction::~ServiceAreaRestriction() {}

void ServiceAreaRestriction::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json& j, const ServiceAreaRestriction& o) {
  j = nlohmann::json();
  if (o.restrictionTypeIsSet()) j["restrictionType"] = o.m_RestrictionType;
  if (o.areasIsSet() || !o.m_Areas.empty()) j["areas"] = o.m_Areas;
  if (o.maxNumOfTAsIsSet()) j["maxNumOfTAs"] = o.m_MaxNumOfTAs;
  if (o.maxNumOfTAsForNotAllowedAreasIsSet())
    j["maxNumOfTAsForNotAllowedAreas"] = o.m_MaxNumOfTAsForNotAllowedAreas;
}

void from_json(const nlohmann::json& j, ServiceAreaRestriction& o) {
  if (j.find("restrictionType") != j.end()) {
    j.at("restrictionType").get_to(o.m_RestrictionType);
    o.m_RestrictionTypeIsSet = true;
  }
  if (j.find("areas") != j.end()) {
    j.at("areas").get_to(o.m_Areas);
    o.m_AreasIsSet = true;
  }
  if (j.find("maxNumOfTAs") != j.end()) {
    j.at("maxNumOfTAs").get_to(o.m_MaxNumOfTAs);
    o.m_MaxNumOfTAsIsSet = true;
  }
  if (j.find("maxNumOfTAsForNotAllowedAreas") != j.end()) {
    j.at("maxNumOfTAsForNotAllowedAreas")
        .get_to(o.m_MaxNumOfTAsForNotAllowedAreas);
    o.m_MaxNumOfTAsForNotAllowedAreasIsSet = true;
  }
}

RestrictionType ServiceAreaRestriction::getRestrictionType() const {
  return m_RestrictionType;
}
void ServiceAreaRestriction::setRestrictionType(RestrictionType const& value) {
  m_RestrictionType      = value;
  m_RestrictionTypeIsSet = true;
}
bool ServiceAreaRestriction::restrictionTypeIsSet() const {
  return m_RestrictionTypeIsSet;
}
void ServiceAreaRestriction::unsetRestrictionType() {
  m_RestrictionTypeIsSet = false;
}
std::vector<Area>& ServiceAreaRestriction::getAreas() {
  return m_Areas;
}
void ServiceAreaRestriction::setAreas(std::vector<Area> const& value) {
  m_Areas      = value;
  m_AreasIsSet = true;
}
bool ServiceAreaRestriction::areasIsSet() const {
  return m_AreasIsSet;
}
void ServiceAreaRestriction::unsetAreas() {
  m_AreasIsSet = false;
}
int32_t ServiceAreaRestriction::getMaxNumOfTAs() const {
  return m_MaxNumOfTAs;
}
void ServiceAreaRestriction::setMaxNumOfTAs(int32_t const value) {
  m_MaxNumOfTAs      = value;
  m_MaxNumOfTAsIsSet = true;
}
bool ServiceAreaRestriction::maxNumOfTAsIsSet() const {
  return m_MaxNumOfTAsIsSet;
}
void ServiceAreaRestriction::unsetMaxNumOfTAs() {
  m_MaxNumOfTAsIsSet = false;
}
int32_t ServiceAreaRestriction::getMaxNumOfTAsForNotAllowedAreas() const {
  return m_MaxNumOfTAsForNotAllowedAreas;
}
void ServiceAreaRestriction::setMaxNumOfTAsForNotAllowedAreas(
    int32_t const value) {
  m_MaxNumOfTAsForNotAllowedAreas      = value;
  m_MaxNumOfTAsForNotAllowedAreasIsSet = true;
}
bool ServiceAreaRestriction::maxNumOfTAsForNotAllowedAreasIsSet() const {
  return m_MaxNumOfTAsForNotAllowedAreasIsSet;
}
void ServiceAreaRestriction::unsetMaxNumOfTAsForNotAllowedAreas() {
  m_MaxNumOfTAsForNotAllowedAreasIsSet = false;
}

}  // namespace oai::udr::model