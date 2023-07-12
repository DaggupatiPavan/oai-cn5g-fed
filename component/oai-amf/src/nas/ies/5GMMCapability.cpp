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

#include "5GMMCapability.hpp"

#include "common_defs.h"
#include "logger.hpp"

using namespace nas;

//------------------------------------------------------------------------------
_5GMMCapability::_5GMMCapability(const uint8_t iei, uint8_t value) {
  m_iei   = iei;
  octet3_ = value;
  length  = k5gmmCapabilityMinimumLength;
}

//------------------------------------------------------------------------------
_5GMMCapability::_5GMMCapability() {}

//------------------------------------------------------------------------------
_5GMMCapability::~_5GMMCapability() {}

//------------------------------------------------------------------------------
void _5GMMCapability::setValue(uint8_t iei, uint8_t value) {
  m_iei   = iei;
  octet3_ = value;
}

//------------------------------------------------------------------------------
uint8_t _5GMMCapability::getValue() {
  return octet3_;
}

//------------------------------------------------------------------------------
int _5GMMCapability::encode2buffer(uint8_t* buf, int len) {
  Logger::nas_mm().debug("Encoding _5GMMCapability IEI (0x%x)", m_iei);
  if (len < length) {
    Logger::nas_mm().error("Len is less than %d", length);
    return 0;
  }

  int encoded_size = 0;
  if (m_iei) {
    ENCODE_U8(buf + encoded_size, m_iei, encoded_size);
    ENCODE_U8(buf + encoded_size, length - 2, encoded_size);
  } else {
    ENCODE_U8(buf + encoded_size, length - 1, encoded_size);
  }

  ENCODE_U8(buf + encoded_size, octet3_, encoded_size);
  // TODO: Encode spare for the rest
  uint8_t spare = 0;
  for (int i = 0; i < (length - encoded_size); i++) {
    ENCODE_U8(buf + encoded_size, spare, encoded_size);
  }

  Logger::nas_mm().debug("Encoded _5GMMCapability len (%d)", encoded_size);
  return encoded_size;
}

//------------------------------------------------------------------------------
int _5GMMCapability::decodefrombuffer(uint8_t* buf, int len, bool is_option) {
  uint8_t decoded_size = 0;

  Logger::nas_mm().debug("Decoding _5GMMCapability IEI (0x%x)", *buf);
  if (is_option) {
    decoded_size++;
  }

  uint8_t ie_len = 0;
  DECODE_U8(buf + decoded_size, ie_len, decoded_size);
  length = ie_len + decoded_size;

  DECODE_U8(buf + decoded_size, octet3_, decoded_size);
  // TODO: decode the rest as spare for now
  uint8_t spare = 0;
  for (int i = 0; i < (ie_len - 1); i++) {
    ENCODE_U8(buf + decoded_size, spare, decoded_size);
  }

  Logger::nas_mm().debug("Decoded _5GMMCapability value(0x%x)", octet3_);
  Logger::nas_mm().debug("Decoded _5GMMCapability len(%d)", decoded_size);
  return decoded_size;
}
