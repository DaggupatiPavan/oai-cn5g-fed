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

#ifndef _5GMM_CAPABILITY_H_
#define _5GMM_CAPABILITY_H_

#include <stdint.h>

constexpr uint8_t k5gmmCapabilityMinimumLength = 3;
constexpr uint8_t k5gmmCapabilityMaximumLength = 15;

namespace nas {

class _5GMMCapability {
 public:
  _5GMMCapability();
  _5GMMCapability(const uint8_t iei, uint8_t value);
  ~_5GMMCapability();

  void setValue(uint8_t iei, uint8_t value);
  uint8_t getValue();

  int encode2buffer(uint8_t* buf, int len);
  int decodefrombuffer(uint8_t* buf, int len, bool is_option = true);

 private:
  uint8_t m_iei;
  uint8_t octet3_;  // minimum length of 3 octets
  uint8_t length;
};

}  // namespace nas

#endif
