/**
 * Common Data Types
 * Common Data Types for Service Based Interfaces. © 2020, 3GPP Organizational
 * Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.2.1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "Arp.h"
#include "Helpers.h"

#include <sstream>

namespace oai::model::common {

Arp::Arp() {
  m_PriorityLevel = 0;
}

void Arp::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw helpers::ValidationException(msg.str());
  }
}

bool Arp::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool Arp::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success                  = true;
  const std::string _pathPrefix = pathPrefix.empty() ? "Arp" : pathPrefix;

  /* PriorityLevel */ {
    const int32_t& value               = m_PriorityLevel;
    const std::string currentValuePath = _pathPrefix + ".priorityLevel";

    if (value < 1) {
      success = false;
      msg << currentValuePath << ": must be greater than or equal to 1;";
    }
    if (value > 15) {
      success = false;
      msg << currentValuePath << ": must be less than or equal to 15;";
    }
  }

  return success;
}

bool Arp::operator==(const Arp& rhs) const {
  return

      (getPriorityLevel() == rhs.getPriorityLevel()) &&

      (getPreemptCap() == rhs.getPreemptCap()) &&

      (getPreemptVuln() == rhs.getPreemptVuln())

          ;
}

bool Arp::operator!=(const Arp& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const Arp& o) {
  j                  = nlohmann::json();
  j["priorityLevel"] = o.m_PriorityLevel;
  j["preemptCap"]    = o.m_PreemptCap;
  j["preemptVuln"]   = o.m_PreemptVuln;
}

void from_json(const nlohmann::json& j, Arp& o) {
  j.at("priorityLevel").get_to(o.m_PriorityLevel);
  j.at("preemptCap").get_to(o.m_PreemptCap);
  j.at("preemptVuln").get_to(o.m_PreemptVuln);
}

int32_t Arp::getPriorityLevel() const {
  return m_PriorityLevel;
}
void Arp::setPriorityLevel(int32_t const value) {
  m_PriorityLevel = value;
}
oai::model::common::PreemptionCapability Arp::getPreemptCap() const {
  return m_PreemptCap;
}
void Arp::setPreemptCap(oai::model::common::PreemptionCapability const& value) {
  m_PreemptCap = value;
}
oai::model::common::PreemptionVulnerability Arp::getPreemptVuln() const {
  return m_PreemptVuln;
}
void Arp::setPreemptVuln(
    oai::model::common::PreemptionVulnerability const& value) {
  m_PreemptVuln = value;
}

}  // namespace oai::model::common
