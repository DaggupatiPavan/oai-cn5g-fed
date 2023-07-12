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

#include "V2xSubscriptionData.h"

namespace oai::udr::model {

V2xSubscriptionData::V2xSubscriptionData() {
  m_NrV2xServicesAuthIsSet  = false;
  m_LteV2xServicesAuthIsSet = false;
  m_NrUePc5Ambr             = "";
  m_NrUePc5AmbrIsSet        = false;
  m_LtePc5Ambr              = "";
  m_LtePc5AmbrIsSet         = false;
}

V2xSubscriptionData::~V2xSubscriptionData() {}

void V2xSubscriptionData::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json& j, const V2xSubscriptionData& o) {
  j = nlohmann::json();
  if (o.nrV2xServicesAuthIsSet())
    j["nrV2xServicesAuth"] = o.m_NrV2xServicesAuth;
  if (o.lteV2xServicesAuthIsSet())
    j["lteV2xServicesAuth"] = o.m_LteV2xServicesAuth;
  if (o.nrUePc5AmbrIsSet()) j["nrUePc5Ambr"] = o.m_NrUePc5Ambr;
  if (o.ltePc5AmbrIsSet()) j["ltePc5Ambr"] = o.m_LtePc5Ambr;
}

void from_json(const nlohmann::json& j, V2xSubscriptionData& o) {
  if (j.find("nrV2xServicesAuth") != j.end()) {
    j.at("nrV2xServicesAuth").get_to(o.m_NrV2xServicesAuth);
    o.m_NrV2xServicesAuthIsSet = true;
  }
  if (j.find("lteV2xServicesAuth") != j.end()) {
    j.at("lteV2xServicesAuth").get_to(o.m_LteV2xServicesAuth);
    o.m_LteV2xServicesAuthIsSet = true;
  }
  if (j.find("nrUePc5Ambr") != j.end()) {
    j.at("nrUePc5Ambr").get_to(o.m_NrUePc5Ambr);
    o.m_NrUePc5AmbrIsSet = true;
  }
  if (j.find("ltePc5Ambr") != j.end()) {
    j.at("ltePc5Ambr").get_to(o.m_LtePc5Ambr);
    o.m_LtePc5AmbrIsSet = true;
  }
}

NrV2xAuth V2xSubscriptionData::getNrV2xServicesAuth() const {
  return m_NrV2xServicesAuth;
}
void V2xSubscriptionData::setNrV2xServicesAuth(NrV2xAuth const& value) {
  m_NrV2xServicesAuth      = value;
  m_NrV2xServicesAuthIsSet = true;
}
bool V2xSubscriptionData::nrV2xServicesAuthIsSet() const {
  return m_NrV2xServicesAuthIsSet;
}
void V2xSubscriptionData::unsetNrV2xServicesAuth() {
  m_NrV2xServicesAuthIsSet = false;
}
LteV2xAuth V2xSubscriptionData::getLteV2xServicesAuth() const {
  return m_LteV2xServicesAuth;
}
void V2xSubscriptionData::setLteV2xServicesAuth(LteV2xAuth const& value) {
  m_LteV2xServicesAuth      = value;
  m_LteV2xServicesAuthIsSet = true;
}
bool V2xSubscriptionData::lteV2xServicesAuthIsSet() const {
  return m_LteV2xServicesAuthIsSet;
}
void V2xSubscriptionData::unsetLteV2xServicesAuth() {
  m_LteV2xServicesAuthIsSet = false;
}
std::string V2xSubscriptionData::getNrUePc5Ambr() const {
  return m_NrUePc5Ambr;
}
void V2xSubscriptionData::setNrUePc5Ambr(std::string const& value) {
  m_NrUePc5Ambr      = value;
  m_NrUePc5AmbrIsSet = true;
}
bool V2xSubscriptionData::nrUePc5AmbrIsSet() const {
  return m_NrUePc5AmbrIsSet;
}
void V2xSubscriptionData::unsetNrUePc5Ambr() {
  m_NrUePc5AmbrIsSet = false;
}
std::string V2xSubscriptionData::getLtePc5Ambr() const {
  return m_LtePc5Ambr;
}
void V2xSubscriptionData::setLtePc5Ambr(std::string const& value) {
  m_LtePc5Ambr      = value;
  m_LtePc5AmbrIsSet = true;
}
bool V2xSubscriptionData::ltePc5AmbrIsSet() const {
  return m_LtePc5AmbrIsSet;
}
void V2xSubscriptionData::unsetLtePc5Ambr() {
  m_LtePc5AmbrIsSet = false;
}

}  // namespace oai::udr::model
