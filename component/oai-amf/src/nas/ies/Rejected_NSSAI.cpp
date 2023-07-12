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

#include "Rejected_NSSAI.hpp"

#include "common_defs.h"
#include "logger.hpp"
using namespace nas;

//------------------------------------------------------------------------------
Rejected_NSSAI::Rejected_NSSAI(uint8_t iei) {
  _iei   = iei;
  length = 0;
}

//------------------------------------------------------------------------------
Rejected_NSSAI::Rejected_NSSAI() {
  _iei   = 0;
  length = 0;
}

//------------------------------------------------------------------------------
Rejected_NSSAI::~Rejected_NSSAI() {}

//------------------------------------------------------------------------------
void Rejected_NSSAI::setRejectedSNSSAIs(
    const std::vector<Rejected_SNSSAI>& nssais) {
  rejected_nssais = nssais;
  for (auto n : nssais) {
    length += n.getLength();
  }
}

//------------------------------------------------------------------------------
void Rejected_NSSAI::getRejectedSNSSAIs(std::vector<Rejected_SNSSAI>& nssais) {
  nssais = rejected_nssais;
}
//------------------------------------------------------------------------------
int Rejected_NSSAI::encode2buffer(uint8_t* buf, int len) {
  Logger::nas_mm().debug("Encoding Rejected_NSSAI");
  uint8_t ie_len = 0;
  if (_iei) {
    ie_len = length + 2;
  } else {
    ie_len = length + 1;
  }
  if (len < ie_len) {
    Logger::nas_mm().error("len is less than %d", ie_len);
    return 0;
  }

  int encoded_size = 0;
  if (_iei) {
    ENCODE_U8(buf + encoded_size, _iei, encoded_size);
  }

  // Skip Length for now
  uint8_t len_pos = encoded_size;
  encoded_size++;
  uint8_t payload_len = 0;

  for (auto n : rejected_nssais) {
    int size = n.encode2buffer(buf + encoded_size, len - encoded_size);
    if (size > -1) {
      encoded_size += size;
      payload_len += size;
    } else {
      return -1;
    }
  }

  // Length
  uint8_t encoded_size_length = 0;
  ENCODE_U8(buf + len_pos, payload_len, encoded_size_length);

  Logger::nas_mm().debug("Encoded Rejected_NSSAI (len %d)", encoded_size);
  return encoded_size;
}

//------------------------------------------------------------------------------
int Rejected_NSSAI::decodefrombuffer(uint8_t* buf, int len, bool is_option) {
  Logger::nas_mm().debug("Decoding Rejected_NSSAI");
  int decoded_size = 0;
  if (is_option) {
    DECODE_U8(buf + decoded_size, _iei, decoded_size);
  }
  DECODE_U8(buf + decoded_size, length, decoded_size);
  int ie_len = length;
  while (ie_len > 0) {
    Rejected_SNSSAI snssai = {};
    int size = snssai.decodefrombuffer(buf + decoded_size, len - decoded_size);
    if (size > -1) {
      decoded_size += size;
      ie_len -= size;
      rejected_nssais.push_back(snssai);
    } else {
      return -1;
    }
  }
  Logger::nas_mm().debug("Decoded Rejected_NSSAI (len %d)", decoded_size);
  return decoded_size;
}
