/**
 * 3gpp-mo-lcs-notify
 * API for UE updated location information notification. © 2021, 3GPP
 * Organizational Partners (ARIB, ATIS, CCSA, ETSI, TSDSI, TTA, TTC). All rights
 * reserved.
 *
 * The version of the OpenAPI document: 1.0.1
 *
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * (https://openapi-generator.tech). https://openapi-generator.tech Do not edit
 * the class manually.
 */
/*
 * GADShape.h
 *
 *
 */

#ifndef GADShape_H_
#define GADShape_H_

#include <nlohmann/json.hpp>

#include "SupportedGADShapes.h"

namespace oai::nef::model {

/// <summary>
///
/// </summary>
class GADShape {
 public:
  GADShape();
  virtual ~GADShape() = default;

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

  bool operator==(const GADShape& rhs) const;
  bool operator!=(const GADShape& rhs) const;

  /////////////////////////////////////////////
  /// GADShape members

  /// <summary>
  ///
  /// </summary>
  SupportedGADShapes getShape() const;
  void setShape(SupportedGADShapes const& value);

  friend void to_json(nlohmann::json& j, const GADShape& o);
  friend void from_json(const nlohmann::json& j, GADShape& o);

 protected:
  SupportedGADShapes m_Shape;
};

}  // namespace oai::nef::model

#endif /* GADShape_H_ */