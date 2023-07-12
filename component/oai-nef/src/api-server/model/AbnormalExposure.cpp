/**
 * 3gpp-analyticsexposure
 * API for Analytics Exposure. © 2021, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.0.3
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "AbnormalExposure.h"

#include <sstream>

#include "Helpers.h"

namespace oai::nef::model {

AbnormalExposure::AbnormalExposure() {
  m_GpsisIsSet        = false;
  m_AppId             = "";
  m_AppIdIsSet        = false;
  m_Ratio             = 0;
  m_RatioIsSet        = false;
  m_Confidence        = 0;
  m_ConfidenceIsSet   = false;
  m_AddtMeasInfoIsSet = false;
}

void AbnormalExposure::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw oai::nef::helpers::ValidationException(msg.str());
  }
}

bool AbnormalExposure::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool AbnormalExposure::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "AbnormalExposure" : pathPrefix;

  if (gpsisIsSet()) {
    const std::vector<std::string>& value = m_Gpsis;
    const std::string currentValuePath    = _pathPrefix + ".gpsis";

    if (value.size() < 1) {
      success = false;
      msg << currentValuePath << ": must have at least 1 elements;";
    }
    {  // Recursive validation of array elements
      const std::string oldValuePath = currentValuePath;
      int i                          = 0;
      for (const std::string& value : value) {
        const std::string currentValuePath =
            oldValuePath + "[" + std::to_string(i) + "]";

        i++;
      }
    }
  }

  if (ratioIsSet()) {
    const int32_t& value               = m_Ratio;
    const std::string currentValuePath = _pathPrefix + ".ratio";

    if (value < 1) {
      success = false;
      msg << currentValuePath << ": must be greater than or equal to 1;";
    }
    if (value > 100) {
      success = false;
      msg << currentValuePath << ": must be less than or equal to 100;";
    }
  }

  if (confidenceIsSet()) {
    const int32_t& value               = m_Confidence;
    const std::string currentValuePath = _pathPrefix + ".confidence";

    if (value < 0) {
      success = false;
      msg << currentValuePath << ": must be greater than or equal to 0;";
    }
  }

  return success;
}

bool AbnormalExposure::operator==(const AbnormalExposure& rhs) const {
  return

      ((!gpsisIsSet() && !rhs.gpsisIsSet()) ||
       (gpsisIsSet() && rhs.gpsisIsSet() && getGpsis() == rhs.getGpsis())) &&

      ((!appIdIsSet() && !rhs.appIdIsSet()) ||
       (appIdIsSet() && rhs.appIdIsSet() && getAppId() == rhs.getAppId())) &&

      (getExcep() == rhs.getExcep()) &&

      ((!ratioIsSet() && !rhs.ratioIsSet()) ||
       (ratioIsSet() && rhs.ratioIsSet() && getRatio() == rhs.getRatio())) &&

      ((!confidenceIsSet() && !rhs.confidenceIsSet()) ||
       (confidenceIsSet() && rhs.confidenceIsSet() &&
        getConfidence() == rhs.getConfidence())) &&

      ((!addtMeasInfoIsSet() && !rhs.addtMeasInfoIsSet()) ||
       (addtMeasInfoIsSet() && rhs.addtMeasInfoIsSet() &&
        getAddtMeasInfo() == rhs.getAddtMeasInfo()))

          ;
}

bool AbnormalExposure::operator!=(const AbnormalExposure& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const AbnormalExposure& o) {
  j = nlohmann::json();
  if (o.gpsisIsSet() || !o.m_Gpsis.empty()) j["gpsis"] = o.m_Gpsis;
  if (o.appIdIsSet()) j["appId"] = o.m_AppId;
  j["excep"] = o.m_Excep;
  if (o.ratioIsSet()) j["ratio"] = o.m_Ratio;
  if (o.confidenceIsSet()) j["confidence"] = o.m_Confidence;
  if (o.addtMeasInfoIsSet()) j["addtMeasInfo"] = o.m_AddtMeasInfo;
}

void from_json(const nlohmann::json& j, AbnormalExposure& o) {
  if (j.find("gpsis") != j.end()) {
    j.at("gpsis").get_to(o.m_Gpsis);
    o.m_GpsisIsSet = true;
  }
  if (j.find("appId") != j.end()) {
    j.at("appId").get_to(o.m_AppId);
    o.m_AppIdIsSet = true;
  }
  j.at("excep").get_to(o.m_Excep);
  if (j.find("ratio") != j.end()) {
    j.at("ratio").get_to(o.m_Ratio);
    o.m_RatioIsSet = true;
  }
  if (j.find("confidence") != j.end()) {
    j.at("confidence").get_to(o.m_Confidence);
    o.m_ConfidenceIsSet = true;
  }
  if (j.find("addtMeasInfo") != j.end()) {
    j.at("addtMeasInfo").get_to(o.m_AddtMeasInfo);
    o.m_AddtMeasInfoIsSet = true;
  }
}

std::vector<std::string> AbnormalExposure::getGpsis() const {
  return m_Gpsis;
}
void AbnormalExposure::setGpsis(std::vector<std::string> const& value) {
  m_Gpsis      = value;
  m_GpsisIsSet = true;
}
bool AbnormalExposure::gpsisIsSet() const {
  return m_GpsisIsSet;
}
void AbnormalExposure::unsetGpsis() {
  m_GpsisIsSet = false;
}
std::string AbnormalExposure::getAppId() const {
  return m_AppId;
}
void AbnormalExposure::setAppId(std::string const& value) {
  m_AppId      = value;
  m_AppIdIsSet = true;
}
bool AbnormalExposure::appIdIsSet() const {
  return m_AppIdIsSet;
}
void AbnormalExposure::unsetAppId() {
  m_AppIdIsSet = false;
}
Exception AbnormalExposure::getExcep() const {
  return m_Excep;
}
void AbnormalExposure::setExcep(Exception const& value) {
  m_Excep = value;
}
int32_t AbnormalExposure::getRatio() const {
  return m_Ratio;
}
void AbnormalExposure::setRatio(int32_t const value) {
  m_Ratio      = value;
  m_RatioIsSet = true;
}
bool AbnormalExposure::ratioIsSet() const {
  return m_RatioIsSet;
}
void AbnormalExposure::unsetRatio() {
  m_RatioIsSet = false;
}
int32_t AbnormalExposure::getConfidence() const {
  return m_Confidence;
}
void AbnormalExposure::setConfidence(int32_t const value) {
  m_Confidence      = value;
  m_ConfidenceIsSet = true;
}
bool AbnormalExposure::confidenceIsSet() const {
  return m_ConfidenceIsSet;
}
void AbnormalExposure::unsetConfidence() {
  m_ConfidenceIsSet = false;
}
AdditionalMeasurement AbnormalExposure::getAddtMeasInfo() const {
  return m_AddtMeasInfo;
}
void AbnormalExposure::setAddtMeasInfo(AdditionalMeasurement const& value) {
  m_AddtMeasInfo      = value;
  m_AddtMeasInfoIsSet = true;
}
bool AbnormalExposure::addtMeasInfoIsSet() const {
  return m_AddtMeasInfoIsSet;
}
void AbnormalExposure::unsetAddtMeasInfo() {
  m_AddtMeasInfoIsSet = false;
}

}  // namespace oai::nef::model