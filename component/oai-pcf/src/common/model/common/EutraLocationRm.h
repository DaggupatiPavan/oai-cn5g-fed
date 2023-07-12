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
 * EutraLocationRm.h
 *
 *
 */

#ifndef EutraLocationRm_H_
#define EutraLocationRm_H_

#include "Ecgi.h"
#include "EutraLocation.h"
#include "Tai.h"
#include <string>
#include "GlobalRanNodeId.h"
#include "NullValue.h"
#include <nlohmann/json.hpp>

namespace oai::model::common {

/// <summary>
///
/// </summary>
class EutraLocationRm {
 public:
  EutraLocationRm();
  virtual ~EutraLocationRm() = default;

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

  bool operator==(const EutraLocationRm& rhs) const;
  bool operator!=(const EutraLocationRm& rhs) const;

  /////////////////////////////////////////////
  /// EutraLocationRm members

  /// <summary>
  ///
  /// </summary>
  oai::model::common::Tai getTai() const;
  void setTai(oai::model::common::Tai const& value);
  /// <summary>
  ///
  /// </summary>
  oai::model::common::Ecgi getEcgi() const;
  void setEcgi(oai::model::common::Ecgi const& value);
  /// <summary>
  ///
  /// </summary>
  bool isIgnoreEcgi() const;
  void setIgnoreEcgi(bool const value);
  bool ignoreEcgiIsSet() const;
  void unsetIgnoreEcgi();
  /// <summary>
  ///
  /// </summary>
  int32_t getAgeOfLocationInformation() const;
  void setAgeOfLocationInformation(int32_t const value);
  bool ageOfLocationInformationIsSet() const;
  void unsetAgeOfLocationInformation();
  /// <summary>
  ///
  /// </summary>
  std::string getUeLocationTimestamp() const;
  void setUeLocationTimestamp(std::string const& value);
  bool ueLocationTimestampIsSet() const;
  void unsetUeLocationTimestamp();
  /// <summary>
  ///
  /// </summary>
  std::string getGeographicalInformation() const;
  void setGeographicalInformation(std::string const& value);
  bool geographicalInformationIsSet() const;
  void unsetGeographicalInformation();
  /// <summary>
  ///
  /// </summary>
  std::string getGeodeticInformation() const;
  void setGeodeticInformation(std::string const& value);
  bool geodeticInformationIsSet() const;
  void unsetGeodeticInformation();
  /// <summary>
  ///
  /// </summary>
  oai::model::common::GlobalRanNodeId getGlobalNgenbId() const;
  void setGlobalNgenbId(oai::model::common::GlobalRanNodeId const& value);
  bool globalNgenbIdIsSet() const;
  void unsetGlobalNgenbId();
  /// <summary>
  ///
  /// </summary>
  oai::model::common::GlobalRanNodeId getGlobalENbId() const;
  void setGlobalENbId(oai::model::common::GlobalRanNodeId const& value);
  bool globalENbIdIsSet() const;
  void unsetGlobalENbId();

  friend void to_json(nlohmann::json& j, const EutraLocationRm& o);
  friend void from_json(const nlohmann::json& j, EutraLocationRm& o);

 protected:
  oai::model::common::Tai m_Tai;

  oai::model::common::Ecgi m_Ecgi;

  bool m_IgnoreEcgi;
  bool m_IgnoreEcgiIsSet;
  int32_t m_AgeOfLocationInformation;
  bool m_AgeOfLocationInformationIsSet;
  std::string m_UeLocationTimestamp;
  bool m_UeLocationTimestampIsSet;
  std::string m_GeographicalInformation;
  bool m_GeographicalInformationIsSet;
  std::string m_GeodeticInformation;
  bool m_GeodeticInformationIsSet;
  oai::model::common::GlobalRanNodeId m_GlobalNgenbId;
  bool m_GlobalNgenbIdIsSet;
  oai::model::common::GlobalRanNodeId m_GlobalENbId;
  bool m_GlobalENbIdIsSet;
};

}  // namespace oai::model::common

#endif /* EutraLocationRm_H_ */
