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
 * AuthStatus.h
 *
 * Possible values are - \&quot;EAP_SUCCESS\&quot;: The NSSAA status is
 * EAP-Success. - \&quot;EAP_FAILURE\&quot;: The NSSAA status is EAP-Failure. -
 * \&quot;PENDING\&quot;: The NSSAA status is Pending.
 */

#ifndef AuthStatus_H_
#define AuthStatus_H_

#include "AuthStatus_anyOf.h"
#include <nlohmann/json.hpp>

namespace oai::model::common {

/// <summary>
/// Possible values are - \&quot;EAP_SUCCESS\&quot;: The NSSAA status is
/// EAP-Success. - \&quot;EAP_FAILURE\&quot;: The NSSAA status is EAP-Failure. -
/// \&quot;PENDING\&quot;: The NSSAA status is Pending.
/// </summary>
class AuthStatus {
 public:
  AuthStatus();
  virtual ~AuthStatus() = default;

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

  bool operator==(const AuthStatus& rhs) const;
  bool operator!=(const AuthStatus& rhs) const;

  /////////////////////////////////////////////
  /// AuthStatus members

  AuthStatus_anyOf getValue() const;
  void setValue(AuthStatus_anyOf value);
  AuthStatus_anyOf::eAuthStatus_anyOf getEnumValue() const;
  void setEnumValue(AuthStatus_anyOf::eAuthStatus_anyOf value);
  friend void to_json(nlohmann::json& j, const AuthStatus& o);
  friend void from_json(const nlohmann::json& j, AuthStatus& o);
  friend void to_json(nlohmann::json& j, const AuthStatus_anyOf& o);
  friend void from_json(const nlohmann::json& j, AuthStatus_anyOf& o);

 protected:
  AuthStatus_anyOf m_value;
};

}  // namespace oai::model::common

#endif /* AuthStatus_H_ */
