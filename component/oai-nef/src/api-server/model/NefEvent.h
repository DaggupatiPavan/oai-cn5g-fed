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
/*
 * NefEvent.h
 *
 *
 */

#ifndef NefEvent_H_
#define NefEvent_H_

#include <nlohmann/json.hpp>

#include "NefEvent_anyOf.h"

namespace oai::nef::model {

/// <summary>
///
/// </summary>
class NefEvent {
 public:
  NefEvent();
  virtual ~NefEvent() = default;

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

  bool operator==(const NefEvent& rhs) const;
  bool operator!=(const NefEvent& rhs) const;

  /////////////////////////////////////////////
  /// NefEvent members

  NefEvent_anyOf getValue() const;
  void setValue(NefEvent_anyOf value);
  NefEvent_anyOf::eNefEvent_anyOf getEnumValue() const;
  void setEnumValue(NefEvent_anyOf::eNefEvent_anyOf value);
  friend void to_json(nlohmann::json& j, const NefEvent& o);
  friend void from_json(const nlohmann::json& j, NefEvent& o);
  friend void to_json(nlohmann::json& j, const NefEvent_anyOf& o);
  friend void from_json(const nlohmann::json& j, NefEvent_anyOf& o);

 protected:
  NefEvent_anyOf m_value;
};

}  // namespace oai::nef::model

#endif /* NefEvent_H_ */
