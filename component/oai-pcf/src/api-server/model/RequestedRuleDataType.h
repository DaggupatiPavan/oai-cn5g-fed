/**
 * Npcf_SMPolicyControl API
 * Session Management Policy Control Service © 2020, 3GPP Organizational
 * Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights reserved.
 *
 * The version of the OpenAPI document: 1.1.1.alpha-5
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * RequestedRuleDataType.h
 *
 * Possible values are - CH_ID: Indicates that the requested rule data is the
 * charging identifier.  - MS_TIME_ZONE: Indicates that the requested access
 * network info type is the UE&#39;s timezone. - USER_LOC_INFO: Indicates that
 * the requested access network info type is the UE&#39;s location. -
 * RES_RELEASE: Indicates that the requested rule data is the result of the
 * release of resource. - SUCC_RES_ALLO: Indicates that the requested rule data
 * is the successful resource allocation. - EPS_FALLBACK: Indicates that the
 * requested rule data is the report of QoS flow rejection due to EPS fallback.
 */

#ifndef RequestedRuleDataType_H_
#define RequestedRuleDataType_H_

#include "RequestedRuleDataType_anyOf.h"
#include <nlohmann/json.hpp>

namespace oai {
namespace pcf {
namespace model {

/// <summary>
/// Possible values are - CH_ID: Indicates that the requested rule data is the
/// charging identifier.  - MS_TIME_ZONE: Indicates that the requested access
/// network info type is the UE&#39;s timezone. - USER_LOC_INFO: Indicates that
/// the requested access network info type is the UE&#39;s location. -
/// RES_RELEASE: Indicates that the requested rule data is the result of the
/// release of resource. - SUCC_RES_ALLO: Indicates that the requested rule data
/// is the successful resource allocation. - EPS_FALLBACK: Indicates that the
/// requested rule data is the report of QoS flow rejection due to EPS fallback.
/// </summary>
class RequestedRuleDataType {
 public:
  RequestedRuleDataType();
  virtual ~RequestedRuleDataType() = default;

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

  bool operator==(const RequestedRuleDataType& rhs) const;
  bool operator!=(const RequestedRuleDataType& rhs) const;

  /////////////////////////////////////////////
  /// RequestedRuleDataType members

  RequestedRuleDataType_anyOf getValue() const;
  void setValue(RequestedRuleDataType_anyOf value);
  RequestedRuleDataType_anyOf::eRequestedRuleDataType_anyOf getEnumValue()
      const;
  void setEnumValue(
      RequestedRuleDataType_anyOf::eRequestedRuleDataType_anyOf value);
  friend void to_json(nlohmann::json& j, const RequestedRuleDataType& o);
  friend void from_json(const nlohmann::json& j, RequestedRuleDataType& o);
  friend void to_json(nlohmann::json& j, const RequestedRuleDataType_anyOf& o);
  friend void from_json(
      const nlohmann::json& j, RequestedRuleDataType_anyOf& o);

 protected:
  RequestedRuleDataType_anyOf m_value;
};

}  // namespace model
}  // namespace pcf
}  // namespace oai
#endif /* RequestedRuleDataType_H_ */
