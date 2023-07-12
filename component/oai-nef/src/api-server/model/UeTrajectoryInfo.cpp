/**
 * Nnef_EventExposure
 * NEF Event Exposure Service. © 2021, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.0.5
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "UeTrajectoryInfo.h"

#include <sstream>

#include "Helpers.h"

namespace oai::nef::model {

UeTrajectoryInfo::UeTrajectoryInfo() {
  m_Ts = "";
}

void UeTrajectoryInfo::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw oai::nef::helpers::ValidationException(msg.str());
  }
}

bool UeTrajectoryInfo::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool UeTrajectoryInfo::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "UeTrajectoryInfo" : pathPrefix;

  return success;
}

bool UeTrajectoryInfo::operator==(const UeTrajectoryInfo& rhs) const {
  return

      (getTs() == rhs.getTs()) &&

      (getLocation() == rhs.getLocation())

          ;
}

bool UeTrajectoryInfo::operator!=(const UeTrajectoryInfo& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const UeTrajectoryInfo& o) {
  j             = nlohmann::json();
  j["ts"]       = o.m_Ts;
  j["location"] = o.m_Location;
}

void from_json(const nlohmann::json& j, UeTrajectoryInfo& o) {
  j.at("ts").get_to(o.m_Ts);
  j.at("location").get_to(o.m_Location);
}

std::string UeTrajectoryInfo::getTs() const {
  return m_Ts;
}
void UeTrajectoryInfo::setTs(std::string const& value) {
  m_Ts = value;
}
UserLocation UeTrajectoryInfo::getLocation() const {
  return m_Location;
}
void UeTrajectoryInfo::setLocation(UserLocation const& value) {
  m_Location = value;
}

}  // namespace oai::nef::model
