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

#include "PduSessionType_anyOf.h"
#include "Helpers.h"
#include <stdexcept>
#include <sstream>

namespace oai::model::common {

PduSessionType_anyOf::PduSessionType_anyOf() {}

void PduSessionType_anyOf::validate() const {
  std::stringstream msg;
  if (!validate(msg)) {
    throw oai::model::common::helpers::ValidationException(msg.str());
  }
}

bool PduSessionType_anyOf::validate(std::stringstream& msg) const {
  return validate(msg, "");
}

bool PduSessionType_anyOf::validate(
    std::stringstream& msg, const std::string& pathPrefix) const {
  bool success = true;
  const std::string _pathPrefix =
      pathPrefix.empty() ? "PduSessionType_anyOf" : pathPrefix;

  if (m_value == PduSessionType_anyOf::ePduSessionType_anyOf::
                     INVALID_VALUE_OPENAPI_GENERATED) {
    success = false;
    msg << _pathPrefix << ": has no value;";
  }

  return success;
}

bool PduSessionType_anyOf::operator==(const PduSessionType_anyOf& rhs) const {
  return getValue() == rhs.getValue()

      ;
}

bool PduSessionType_anyOf::operator!=(const PduSessionType_anyOf& rhs) const {
  return !(*this == rhs);
}

void to_json(nlohmann::json& j, const PduSessionType_anyOf& o) {
  j = nlohmann::json();

  switch (o.getValue()) {
    case PduSessionType_anyOf::ePduSessionType_anyOf::
        INVALID_VALUE_OPENAPI_GENERATED:
      j = "INVALID_VALUE_OPENAPI_GENERATED";
      break;
    case PduSessionType_anyOf::ePduSessionType_anyOf::IPV4:
      j = "IPV4";
      break;
    case PduSessionType_anyOf::ePduSessionType_anyOf::IPV6:
      j = "IPV6";
      break;
    case PduSessionType_anyOf::ePduSessionType_anyOf::IPV4V6:
      j = "IPV4V6";
      break;
    case PduSessionType_anyOf::ePduSessionType_anyOf::UNSTRUCTURED:
      j = "UNSTRUCTURED";
      break;
    case PduSessionType_anyOf::ePduSessionType_anyOf::ETHERNET:
      j = "ETHERNET";
      break;
  }
}

void from_json(const nlohmann::json& j, PduSessionType_anyOf& o) {
  auto s = j.get<std::string>();
  if (s == "IPV4") {
    o.setValue(PduSessionType_anyOf::ePduSessionType_anyOf::IPV4);
  } else if (s == "IPV6") {
    o.setValue(PduSessionType_anyOf::ePduSessionType_anyOf::IPV6);
  } else if (s == "IPV4V6") {
    o.setValue(PduSessionType_anyOf::ePduSessionType_anyOf::IPV4V6);
  } else if (s == "UNSTRUCTURED") {
    o.setValue(PduSessionType_anyOf::ePduSessionType_anyOf::UNSTRUCTURED);
  } else if (s == "ETHERNET") {
    o.setValue(PduSessionType_anyOf::ePduSessionType_anyOf::ETHERNET);
  } else {
    std::stringstream ss;
    ss << "Unexpected value " << s << " in json"
       << " cannot be converted to enum of type"
       << " PduSessionType_anyOf::ePduSessionType_anyOf";
    throw std::invalid_argument(ss.str());
  }
}

PduSessionType_anyOf::ePduSessionType_anyOf PduSessionType_anyOf::getValue()
    const {
  return m_value;
}
void PduSessionType_anyOf::setValue(
    PduSessionType_anyOf::ePduSessionType_anyOf value) {
  m_value = value;
}

}  // namespace oai::model::common
