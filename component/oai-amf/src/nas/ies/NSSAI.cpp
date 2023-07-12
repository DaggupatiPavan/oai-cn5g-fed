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

#include "NSSAI.hpp"

#include <vector>

#include "logger.hpp"
#include "amf.hpp"

using namespace nas;

//------------------------------------------------------------------------------
NSSAI::NSSAI(uint8_t iei) {
  _iei   = iei;
  length = 0;
}

//------------------------------------------------------------------------------
NSSAI::NSSAI(const uint8_t iei, std::vector<struct SNSSAI_s> nssai) {
  _iei   = iei;
  length = 0;
  S_NSSAIs.assign(nssai.begin(), nssai.end());
  for (int i = 0; i < nssai.size(); i++) {
    length += (1 + nssai[i].length);  // 1 for length of NSSAI[i]
    // if (nssai[i].sd != SD_NO_VALUE) length += SD_LENGTH;
    // if (nssai[i].mHplmnSst != -1) length += SST_LENGTH;
    // if (nssai[i].mHplmnSd != SD_NO_VALUE) length += SD_LENGTH;
  }
}

//------------------------------------------------------------------------------
NSSAI::NSSAI() : _iei(), length(), S_NSSAIs() {}

//------------------------------------------------------------------------------
NSSAI::~NSSAI() {}

//------------------------------------------------------------------------------
void NSSAI::setS_NAASI(uint8_t SST) {}

//------------------------------------------------------------------------------
void NSSAI::getValue(std::vector<struct SNSSAI_s>& nssai) {
  nssai.assign(S_NSSAIs.begin(), S_NSSAIs.end());
}

//------------------------------------------------------------------------------
int NSSAI::encode2buffer(uint8_t* buf, int len) {
  Logger::nas_mm().debug("Encoding NSSAI IEI (0x%x)", _iei);
  if (len < length) {
    Logger::nas_mm().error("len is less than %d", length);
    return 0;
  }
  int encoded_size = 0;
  if (_iei) {
    ENCODE_U8(buf + encoded_size, _iei, encoded_size);
  }

  ENCODE_U8(buf + encoded_size, length, encoded_size);

  for (int i = 0; i < S_NSSAIs.size(); i++) {
    int len_s_nssai = SST_LENGTH;
    encoded_size++;
    *(buf + encoded_size) = S_NSSAIs.at(i).sst;
    encoded_size++;
    if (S_NSSAIs.at(i).sd != SD_NO_VALUE) {
      len_s_nssai += SD_LENGTH;
      *(buf + encoded_size) = (S_NSSAIs.at(i).sd & 0x00ff0000) >> 16;
      encoded_size++;
      Logger::nas_mm().debug(
          "Encoded NSSAI SD first octet (%x)", *(buf + encoded_size - 1));
      *(buf + encoded_size) = (S_NSSAIs.at(i).sd & 0x0000ff00) >> 8;
      encoded_size++;
      Logger::nas_mm().debug(
          "Encoded NSSAI SD second octet (%x)", *(buf + encoded_size - 1));
      *(buf + encoded_size) = S_NSSAIs.at(i).sd & 0x000000ff;
      encoded_size++;
      Logger::nas_mm().debug(
          "Encoded NSSAI SD third octet (%x)", *(buf + encoded_size - 1));
    }
    if (S_NSSAIs.at(i).length > (SST_LENGTH + SD_LENGTH)) {
      if (S_NSSAIs.at(i).mHplmnSst != -1) {
        len_s_nssai += SST_LENGTH;
        *(buf + encoded_size) = S_NSSAIs.at(i).mHplmnSst;
        encoded_size++;
      }
      if (S_NSSAIs.at(i).mHplmnSd != SD_NO_VALUE) {
        len_s_nssai += SD_LENGTH;
        *(buf + encoded_size) = (S_NSSAIs.at(i).mHplmnSd & 0x00ff0000) >> 16;
        encoded_size++;
        *(buf + encoded_size) = (S_NSSAIs.at(i).mHplmnSd & 0x0000ff00) >> 8;
        encoded_size++;
        *(buf + encoded_size) = S_NSSAIs.at(i).mHplmnSd & 0x000000ff;
        encoded_size++;
      }
    }

    *(buf + encoded_size - len_s_nssai - 1) = len_s_nssai;
  }

  Logger::nas_mm().debug("Encoded NSSAI len (%d)", encoded_size);
  return encoded_size;
}

//------------------------------------------------------------------------------
int NSSAI::decodefrombuffer(uint8_t* buf, int len, bool is_option) {
  Logger::nas_mm().debug("Decoding NSSAI IEI (0x%x)", *buf);
  int decoded_size = 0;
  SNSSAI_s a       = {0, 0, 0, 0};
  if (is_option) {
    decoded_size++;
  }
  length = *(buf + decoded_size);
  decoded_size++;
  int length_tmp = length;

  while (length_tmp) {
    switch (*(buf + decoded_size)) {
      case 1: {
        decoded_size++;  // snssai—length
        length_tmp--;
        a.sst = *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd        = SD_NO_VALUE;
        a.mHplmnSst = 0;
        a.mHplmnSd  = 0;
      } break;
      case 4: {
        decoded_size++;
        length_tmp--;
        a.sst = *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd <<= 8;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd <<= 8;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSst = 0;
        a.mHplmnSd  = 0;
      } break;
      case 5: {
        decoded_size++;
        length_tmp--;
        a.sst = *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd <<= 8;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd <<= 8;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSst = *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSd = SD_NO_VALUE;
      } break;
      case 8: {
        decoded_size++;
        length_tmp--;
        a.sst = *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd <<= 8;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.sd <<= 8;
        a.sd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSst = *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSd <<= 8;
        a.mHplmnSd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
        a.mHplmnSd <<= 8;
        a.mHplmnSd |= *(buf + decoded_size);
        decoded_size++;
        length_tmp--;
      } break;
    }

    S_NSSAIs.insert(S_NSSAIs.end(), a);
    a = {0, 0, 0, 0};
  }

  for (int i = 0; i < S_NSSAIs.size(); i++) {
    Logger::nas_mm().debug(
        "Decoded NSSAI %s", S_NSSAIs.at(i).ToString().c_str());
  }
  Logger::nas_mm().debug("Decoded NSSAI len (%d)", decoded_size);
  return decoded_size;
}
