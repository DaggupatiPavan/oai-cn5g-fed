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
 * IpMulticastAddressInfo.h
 *
 *
 */

#ifndef IpMulticastAddressInfo_H_
#define IpMulticastAddressInfo_H_

#include <string>
#include "Ipv6Addr.h"
#include <nlohmann/json.hpp>

namespace oai {
namespace pcf {
namespace model {

/// <summary>
///
/// </summary>
class IpMulticastAddressInfo {
 public:
  IpMulticastAddressInfo();
  virtual ~IpMulticastAddressInfo() = default;

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

  bool operator==(const IpMulticastAddressInfo& rhs) const;
  bool operator!=(const IpMulticastAddressInfo& rhs) const;

  /////////////////////////////////////////////
  /// IpMulticastAddressInfo members

  /// <summary>
  ///
  /// </summary>
  std::string getSrcIpv4Addr() const;
  void setSrcIpv4Addr(std::string const& value);
  bool srcIpv4AddrIsSet() const;
  void unsetSrcIpv4Addr();
  /// <summary>
  ///
  /// </summary>
  std::string getIpv4MulAddr() const;
  void setIpv4MulAddr(std::string const& value);
  bool ipv4MulAddrIsSet() const;
  void unsetIpv4MulAddr();
  /// <summary>
  ///
  /// </summary>
  oai::model::common::Ipv6Addr getSrcIpv6Addr() const;
  void setSrcIpv6Addr(oai::model::common::Ipv6Addr const& value);
  bool srcIpv6AddrIsSet() const;
  void unsetSrcIpv6Addr();
  /// <summary>
  ///
  /// </summary>
  oai::model::common::Ipv6Addr getIpv6MulAddr() const;
  void setIpv6MulAddr(oai::model::common::Ipv6Addr const& value);
  bool ipv6MulAddrIsSet() const;
  void unsetIpv6MulAddr();

  friend void to_json(nlohmann::json& j, const IpMulticastAddressInfo& o);
  friend void from_json(const nlohmann::json& j, IpMulticastAddressInfo& o);

 protected:
  std::string m_SrcIpv4Addr;
  bool m_SrcIpv4AddrIsSet;
  std::string m_Ipv4MulAddr;
  bool m_Ipv4MulAddrIsSet;
  oai::model::common::Ipv6Addr m_SrcIpv6Addr;
  bool m_SrcIpv6AddrIsSet;
  oai::model::common::Ipv6Addr m_Ipv6MulAddr;
  bool m_Ipv6MulAddrIsSet;
};

}  // namespace model
}  // namespace pcf
}  // namespace oai
#endif /* IpMulticastAddressInfo_H_ */