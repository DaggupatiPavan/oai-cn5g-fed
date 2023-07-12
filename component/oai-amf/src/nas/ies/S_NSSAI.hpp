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

/*! \file
 \brief
 \author  Keliang DU, BUPT
 \date 2020
 \email: contact@openairinterface.org
 */

#ifndef __S_NSSAI_H_
#define __S_NSSAI_H_

#include <stdint.h>

#include "nas_ie_header.hpp"
#include <optional>

namespace nas {

class S_NSSAI {
 public:
  S_NSSAI();
  S_NSSAI(std::optional<uint8_t> iei, SNSSAI_s snssai);
  ~S_NSSAI();
  int encode2buffer(uint8_t* buf, int len);
  int decodefrombuffer(uint8_t* buf, int len, const bool is_option = true);
  void getValue(SNSSAI_t& snssai);
  void SetSNSSAI(
      std::optional<int8_t> iei, uint8_t sst, std::optional<int32_t> sd,
      std::optional<int8_t> mapped_hplmn_sst,
      std::optional<int32_t> mapped_hplmn_sd);
  uint8_t GetLength();
  std::string ToString();

 private:
  std::optional<int8_t> iei_;
  uint8_t length;
  uint8_t sst_;
  std::optional<int32_t> sd_;
  std::optional<int8_t> mapped_hplmn_sst_;
  std::optional<int32_t> mapped_hplmn_sd_;
};

}  // namespace nas

#endif
