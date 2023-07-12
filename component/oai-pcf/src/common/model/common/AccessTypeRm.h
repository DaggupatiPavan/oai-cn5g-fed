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
/*
 * AccessTypeRm.h
 *
 *
 */

#ifndef AccessTypeRm_H_
#define AccessTypeRm_H_

#include "NullValue.h"
#include "AccessType.h"
#include <nlohmann/json.hpp>

namespace oai::model::common {

/// <summary>
///  The same as access type, but it is nullable
/// </summary>
class AccessTypeRm : public AccessType {
 public:
  AccessTypeRm();
  virtual ~AccessTypeRm() = default;

  bool validate(
      std::stringstream& msg, const std::string& pathPrefix) const override;

  friend void to_json(nlohmann::json& j, const AccessTypeRm& o);
  friend void from_json(const nlohmann::json& j, AccessTypeRm& o);

 protected:
};

}  // namespace oai::model::common

#endif /* AccessTypeRm_H_ */
