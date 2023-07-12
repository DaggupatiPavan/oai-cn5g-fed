/**
 * 3gpp-monitoring-event
 * API for Monitoring Event. © 2021, 3GPP Organizational Partners (ARIB, ATIS,
 * CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.2.0-alpha.4
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */

#include "ResultReason.h"

#include <sstream>

#include "Helpers.h"

namespace oai::nef::model {

ResultReason::ResultReason() {}

void ResultReason::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw oai::nef::helpers::ValidationException(msg.str());
  }
}

bool ResultReason::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool ResultReason::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "ResultReason" : pathPrefix;

  if (!m_value.validate(msg)) {
    success = false;
  }
  return success;
}

bool ResultReason::operator==(const ResultReason& rhs) const {
  return

      getValue() == rhs.getValue();
}

bool ResultReason::operator!=(const ResultReason& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const ResultReason& o) {
  j = nlohmann::json();
  to_json(j, o.m_value);
}

void from_json(const nlohmann::json& j, ResultReason& o) {
  from_json(j, o.m_value);
}

ResultReason_anyOf ResultReason::getValue() const {
  return m_value;
}

void ResultReason::setValue(ResultReason_anyOf value) {
  m_value = value;
}

ResultReason_anyOf::eResultReason_anyOf ResultReason::getEnumValue() const {
  return m_value.getValue();
}

void ResultReason::setEnumValue(ResultReason_anyOf::eResultReason_anyOf value) {
  m_value.setValue(value);
}

}  // namespace oai::nef::model