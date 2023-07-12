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

#include "ConfigurationUpdateCommand.hpp"

#include "3gpp_ts24501.hpp"
#include "String2Value.hpp"
#include "logger.hpp"

using namespace nas;

//------------------------------------------------------------------------------
ConfigurationUpdateCommand::ConfigurationUpdateCommand() {
  plain_header           = nullptr;
  full_name_for_network  = nullopt;
  short_name_for_network = nullopt;
}

//------------------------------------------------------------------------------
ConfigurationUpdateCommand::~ConfigurationUpdateCommand() {}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::setHeader(uint8_t security_header_type) {
  plain_header = new NasMmPlainHeader();
  plain_header->setHeader(
      EPD_5GS_MM_MSG, security_header_type, CONFIGURATION_UPDATE_COMMAND);
}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::setFullNameForNetwork(
    const NetworkName& name) {
  full_name_for_network = std::optional<NetworkName>(name);
}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::setFullNameForNetwork(
    const std::string& text_string) {
  NetworkName full_name_for_network_tmp;
  full_name_for_network_tmp.setIEI(kIeiFullNameForNetwork);
  full_name_for_network_tmp.setCodingScheme(0);
  full_name_for_network_tmp.setAddCI(0);
  full_name_for_network_tmp.setNumberOfSpareBits(0x07);  // TODO:
  full_name_for_network_tmp.setTextString(text_string);
  full_name_for_network = std::optional<NetworkName>(full_name_for_network_tmp);
}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::getFullNameForNetwork(
    std::optional<NetworkName>& name) const {
  name = full_name_for_network;
}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::setShortNameForNetwork(
    const std::string& text_string) {
  NetworkName short_name_for_network_tmp;
  short_name_for_network_tmp.setIEI(kIeiShortNameForNetwork);  // TODO
  short_name_for_network_tmp.setCodingScheme(0);
  short_name_for_network_tmp.setAddCI(0);
  short_name_for_network_tmp.setNumberOfSpareBits(0x07);  // TODO
  short_name_for_network_tmp.setTextString(text_string);
  short_name_for_network =
      std::optional<NetworkName>(short_name_for_network_tmp);
}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::setShortNameForNetwork(
    const NetworkName& name) {
  short_name_for_network = std::optional<NetworkName>(name);
}

//------------------------------------------------------------------------------
void ConfigurationUpdateCommand::getShortNameForNetwork(
    NetworkName& name) const {}

//------------------------------------------------------------------------------
int ConfigurationUpdateCommand::encode2Buffer(uint8_t* buf, int len) {
  Logger::nas_mm().debug("Encoding ConfigurationUpdateCommand message");
  int encoded_size = 0;
  if (!plain_header) {
    Logger::nas_mm().error("Mandatory IE missing Header");
    return -1;
  }
  uint8_t encoded_size_ie = 0;
  if (!(encoded_size_ie = plain_header->encode2buffer(buf, len))) return 0;
  encoded_size += encoded_size_ie;

  if (!full_name_for_network.has_value()) {
    Logger::nas_mm().debug("IE Full Name For Network is not available");
  } else {
    if (int size = full_name_for_network.value().encode2buffer(
            buf + encoded_size, len - encoded_size)) {
      encoded_size += size;
    } else {
      Logger::nas_mm().error("Encoding Full Name For Network error");
      return 0;
    }
  }

  if (!short_name_for_network.has_value()) {
    Logger::nas_mm().debug("IE Short Name For Network is not available");
  } else {
    if (int size = short_name_for_network.value().encode2buffer(
            buf + encoded_size, len - encoded_size)) {
      encoded_size += size;
    } else {
      Logger::nas_mm().error("Encoding Short Name For Network error");
      return 0;
    }
  }

  Logger::nas_mm().debug(
      "Encoded ConfigurationUpdateCommand message (len %d)", encoded_size);
  return encoded_size;
}

//------------------------------------------------------------------------------
int ConfigurationUpdateCommand::decodeFromBuffer(uint8_t* buf, int len) {
  Logger::nas_mm().debug("Decoding ConfigurationUpdateCommand message");
  int decoded_size        = 0;
  uint8_t decoded_size_ie = 0;
  if (!(decoded_size_ie = plain_header->decodefrombuffer(buf, len))) return 0;
  decoded_size += decoded_size_ie;

  uint8_t octet = *(buf + decoded_size);
  Logger::nas_mm().debug("First option IEI (0x%x)", octet);
  while ((octet != 0x0)) {
    switch (octet) {
      case kIeiFullNameForNetwork: {
        Logger::nas_mm().debug("Decoding IEI 0x43: Full Name for Network");
        NetworkName full_name_for_network_tmp;
        decoded_size += full_name_for_network_tmp.decodefrombuffer(
            buf + decoded_size, len - decoded_size, true);
        full_name_for_network =
            std::optional<NetworkName>(full_name_for_network_tmp);
        octet = *(buf + decoded_size);
        Logger::nas_mm().debug("Next IEI (0x%x)", octet);
      } break;
      case kIeiShortNameForNetwork: {
        Logger::nas_mm().debug("Decoding IEI 0x45: Short Name for Network");
        NetworkName short_name_for_network_tmp;
        decoded_size += short_name_for_network_tmp.decodefrombuffer(
            buf + decoded_size, len - decoded_size, true);
        short_name_for_network =
            std::optional<NetworkName>(short_name_for_network_tmp);
        octet = *(buf + decoded_size);
        Logger::nas_mm().debug("Next IEI (0x%x)", octet);
      } break;
    }
  }

  Logger::nas_mm().debug(
      "Decoded ConfigurationUpdateCommand message (len %d)", decoded_size);
  return decoded_size;
}
