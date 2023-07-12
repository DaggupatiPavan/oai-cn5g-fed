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

#include "MeasurementPeriodLteMdt.h"
#include "Helpers.h"

#include <sstream>

namespace oai::model::common {

MeasurementPeriodLteMdt::MeasurementPeriodLteMdt() {}

void MeasurementPeriodLteMdt::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw oai::model::common::helpers::ValidationException(msg.str());
  }
}

bool MeasurementPeriodLteMdt::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool MeasurementPeriodLteMdt::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "MeasurementPeriodLteMdt" : pathPrefix;

  if (!m_value.validate(msg)) {
    success = false;
  }
  return success;
}

bool MeasurementPeriodLteMdt::operator==(
    const MeasurementPeriodLteMdt& rhs) const {
  return

      getValue() == rhs.getValue();
}

bool MeasurementPeriodLteMdt::operator!=(
    const MeasurementPeriodLteMdt& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const MeasurementPeriodLteMdt& o) {
  j = nlohmann::json();
  to_json(j, o.m_value);
}

void from_json(const nlohmann::json& j, MeasurementPeriodLteMdt& o) {
  from_json(j, o.m_value);
}

CollectionPeriodRmmLteMdt_anyOf MeasurementPeriodLteMdt::getValue() const {
  return m_value;
}

void MeasurementPeriodLteMdt::setValue(CollectionPeriodRmmLteMdt_anyOf value) {
  m_value = value;
}

CollectionPeriodRmmLteMdt_anyOf::eCollectionPeriodRmmLteMdt_anyOf
MeasurementPeriodLteMdt::getEnumValue() const {
  return m_value.getValue();
}

void MeasurementPeriodLteMdt::setEnumValue(
    CollectionPeriodRmmLteMdt_anyOf::eCollectionPeriodRmmLteMdt_anyOf value) {
  m_value.setValue(value);
}

}  // namespace oai::model::common
