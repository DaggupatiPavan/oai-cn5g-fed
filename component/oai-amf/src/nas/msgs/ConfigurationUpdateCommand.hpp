/*
 * Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The OpenAirInterface Software Alliance licenses this file to You under
 * the OAI Public License, Version 1.1  (the "License"); you may not use this
 * file except in compliance with the License. You may obtain a copy of the
 * License at
 *
 *      http://www.openairinterface.org/?page_id=698
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------------------
 * For more information about the OpenAirInterface (OAI) Software Alliance:
 *      contact@openairinterface.org
 */

#ifndef CONFIGURATION_UPDATE_COMMAND_H_
#define CONFIGURATION_UPDATE_COMMAND_H_

#include <bstrlib.h>
#include <stdint.h>
#include <string>

#include "nas_ie_header.hpp"
namespace nas {

class ConfigurationUpdateCommand {
 public:
  ConfigurationUpdateCommand();
  ~ConfigurationUpdateCommand();

  void setHeader(uint8_t security_header_type);
  void getSecurityHeaderType(uint8_t security_header_type);
  bool verifyHeader();

  void setFullNameForNetwork(const NetworkName& name);
  void setFullNameForNetwork(const std::string& text_string);
  void getFullNameForNetwork(std::optional<NetworkName>& name) const;

  void setShortNameForNetwork(const NetworkName& name);
  void setShortNameForNetwork(const std::string& text_string);
  void getShortNameForNetwork(NetworkName& name) const;

  int encode2Buffer(uint8_t* buf, int len);
  int decodeFromBuffer(uint8_t* buf, int len);

 public:
  NasMmPlainHeader*
      plain_header;  // TODO: Should be removed in the new NAS version
  // Optional
  // TODO: Configuration update indication
  // TODO: 5G-GUTI
  // TODO: TAI list
  // TODO: Allowed NSSAI
  // TODO: Service area list
  // Full name for network
  std::optional<NetworkName> full_name_for_network;
  // Short name for network
  std::optional<NetworkName> short_name_for_network;
  // TODO: Local time zone
  // TODO: Universal time and local time zone
  // TODO: Network daylight saving time
  // TODO: LADN information
  // TODO: MICO indication
  // TODO: Network slicing indication
  // TODO: Configured NSSAI
  // TODO: Rejected NSSAI
  // TODO: Operator-defined access category definitions
  // TODO: SMS indication
  // TODO: T3447 value
};

}  // namespace nas

#endif
