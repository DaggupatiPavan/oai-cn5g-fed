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

#ifndef _REJECTED_NSSAI_H_
#define _REJECTED_NSSAI_H_

#include <Rejected_SNSSAI.hpp>

#include <stdint.h>
#include <vector>

namespace nas {

class Rejected_NSSAI {
 public:
  Rejected_NSSAI();
  Rejected_NSSAI(uint8_t iei);
  ~Rejected_NSSAI();
  void setRejectedSNSSAIs(const std::vector<Rejected_SNSSAI>& nssais);
  void getRejectedSNSSAIs(std::vector<Rejected_SNSSAI>& nssais);
  int encode2buffer(uint8_t* buf, int len);
  int decodefrombuffer(uint8_t* buf, int len, bool is_option);

 private:
  uint8_t _iei;
  uint8_t length;
  std::vector<Rejected_SNSSAI> rejected_nssais;
};

}  // namespace nas

#endif
