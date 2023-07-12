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

#include "MulticastAccessControl.h"

namespace oai::udr::model {

MulticastAccessControl::MulticastAccessControl() {
  m_SrcIpv4Addr          = "";
  m_SrcIpv4AddrIsSet     = false;
  m_SrcIpv6AddrIsSet     = false;
  m_MulticastV4Addr      = "";
  m_MulticastV4AddrIsSet = false;
  m_MulticastV6AddrIsSet = false;
}

MulticastAccessControl::~MulticastAccessControl() {}

void MulticastAccessControl::validate() {
  // TODO: implement validation
}

void to_json(nlohmann::json& j, const MulticastAccessControl& o) {
  j = nlohmann::json();
  if (o.srcIpv4AddrIsSet()) j["srcIpv4Addr"] = o.m_SrcIpv4Addr;
  if (o.srcIpv6AddrIsSet()) j["srcIpv6Addr"] = o.m_SrcIpv6Addr;
  if (o.multicastV4AddrIsSet()) j["multicastV4Addr"] = o.m_MulticastV4Addr;
  if (o.multicastV6AddrIsSet()) j["multicastV6Addr"] = o.m_MulticastV6Addr;
  j["accStatus"] = o.m_AccStatus;
}

void from_json(const nlohmann::json& j, MulticastAccessControl& o) {
  if (j.find("srcIpv4Addr") != j.end()) {
    j.at("srcIpv4Addr").get_to(o.m_SrcIpv4Addr);
    o.m_SrcIpv4AddrIsSet = true;
  }
  if (j.find("srcIpv6Addr") != j.end()) {
    j.at("srcIpv6Addr").get_to(o.m_SrcIpv6Addr);
    o.m_SrcIpv6AddrIsSet = true;
  }
  if (j.find("multicastV4Addr") != j.end()) {
    j.at("multicastV4Addr").get_to(o.m_MulticastV4Addr);
    o.m_MulticastV4AddrIsSet = true;
  }
  if (j.find("multicastV6Addr") != j.end()) {
    j.at("multicastV6Addr").get_to(o.m_MulticastV6Addr);
    o.m_MulticastV6AddrIsSet = true;
  }
  j.at("accStatus").get_to(o.m_AccStatus);
}

std::string MulticastAccessControl::getSrcIpv4Addr() const {
  return m_SrcIpv4Addr;
}
void MulticastAccessControl::setSrcIpv4Addr(std::string const& value) {
  m_SrcIpv4Addr      = value;
  m_SrcIpv4AddrIsSet = true;
}
bool MulticastAccessControl::srcIpv4AddrIsSet() const {
  return m_SrcIpv4AddrIsSet;
}
void MulticastAccessControl::unsetSrcIpv4Addr() {
  m_SrcIpv4AddrIsSet = false;
}
Ipv6Addr MulticastAccessControl::getSrcIpv6Addr() const {
  return m_SrcIpv6Addr;
}
void MulticastAccessControl::setSrcIpv6Addr(Ipv6Addr const& value) {
  m_SrcIpv6Addr      = value;
  m_SrcIpv6AddrIsSet = true;
}
bool MulticastAccessControl::srcIpv6AddrIsSet() const {
  return m_SrcIpv6AddrIsSet;
}
void MulticastAccessControl::unsetSrcIpv6Addr() {
  m_SrcIpv6AddrIsSet = false;
}
std::string MulticastAccessControl::getMulticastV4Addr() const {
  return m_MulticastV4Addr;
}
void MulticastAccessControl::setMulticastV4Addr(std::string const& value) {
  m_MulticastV4Addr      = value;
  m_MulticastV4AddrIsSet = true;
}
bool MulticastAccessControl::multicastV4AddrIsSet() const {
  return m_MulticastV4AddrIsSet;
}
void MulticastAccessControl::unsetMulticastV4Addr() {
  m_MulticastV4AddrIsSet = false;
}
Ipv6Addr MulticastAccessControl::getMulticastV6Addr() const {
  return m_MulticastV6Addr;
}
void MulticastAccessControl::setMulticastV6Addr(Ipv6Addr const& value) {
  m_MulticastV6Addr      = value;
  m_MulticastV6AddrIsSet = true;
}
bool MulticastAccessControl::multicastV6AddrIsSet() const {
  return m_MulticastV6AddrIsSet;
}
void MulticastAccessControl::unsetMulticastV6Addr() {
  m_MulticastV6AddrIsSet = false;
}
AccessRightStatus MulticastAccessControl::getAccStatus() const {
  return m_AccStatus;
}
void MulticastAccessControl::setAccStatus(AccessRightStatus const& value) {
  m_AccStatus = value;
}

}  // namespace oai::udr::model
