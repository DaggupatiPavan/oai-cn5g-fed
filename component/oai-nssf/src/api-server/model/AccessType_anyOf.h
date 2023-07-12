/**
 * NSSF NS Selection
 * NSSF Network Slice Selection Service. © 2021, 3GPP Organizational Partners
 * (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 2.1.2
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * AccessType_anyOf.h
 *
 *
 */

#ifndef AccessType_anyOf_H_
#define AccessType_anyOf_H_

#include <nlohmann/json.hpp>

namespace oai {
namespace nssf_server {
namespace model {

/// <summary>
///
/// </summary>
class AccessType_anyOf {
 public:
  AccessType_anyOf();
  virtual ~AccessType_anyOf() = default;

  enum class eAccessType_anyOf {
    // To have a valid default value.
    // Avoiding nameclashes with user defined
    // enum values
    INVALID_VALUE_OPENAPI_GENERATED = 0,
    ACCESS_3GPP,
    ACCESS_NON_3GPP
  };

  /// <summary>
  /// Validate the current data in the model. Throws a ValidationException on
  /// failure.
  /// </summary>
  void validate() const;

  /// <summary>
  /// Validate the current data in the model. Returns false on error and writes
  /// an error message into the given stringstream.
  /// </summary>
  bool validate(std::stringstream& msg) const;

  /// <summary>
  /// Helper overload for validate. Used when one model stores another model and
  /// calls it's validate. Not meant to be called outside that case.
  /// </summary>
  bool validate(std::stringstream& msg, const std::string& pathPrefix) const;

  bool operator==(const AccessType_anyOf& rhs) const;
  bool operator!=(const AccessType_anyOf& rhs) const;

  /////////////////////////////////////////////
  /// AccessType_anyOf members

  AccessType_anyOf::eAccessType_anyOf getValue() const;
  void setValue(AccessType_anyOf::eAccessType_anyOf value);

  friend void to_json(nlohmann::json& j, const AccessType_anyOf& o);
  friend void from_json(const nlohmann::json& j, AccessType_anyOf& o);

 protected:
  AccessType_anyOf::eAccessType_anyOf m_value =
      AccessType_anyOf::eAccessType_anyOf::INVALID_VALUE_OPENAPI_GENERATED;
};

}  // namespace model
}  // namespace nssf_server
}  // namespace oai

#endif /* AccessType_anyOf_H_ */
