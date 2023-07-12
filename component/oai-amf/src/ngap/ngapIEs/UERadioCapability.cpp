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

#include "UERadioCapability.hpp"

#include "conversions.hpp"

namespace ngap {

//------------------------------------------------------------------------------
UERadioCapability::UERadioCapability() {}

//------------------------------------------------------------------------------
UERadioCapability::~UERadioCapability() {}

//------------------------------------------------------------------------------
bool UERadioCapability::encode(Ngap_UERadioCapability_t& ueRadioCapability) {
  return conv::octet_string_copy(ueRadioCapability, ue_radio_capability_);
}

//------------------------------------------------------------------------------
bool UERadioCapability::decode(Ngap_UERadioCapability_t& ueRadioCapability) {
  return conv::octet_string_copy(ue_radio_capability_, ueRadioCapability);
}

//------------------------------------------------------------------------------
bool UERadioCapability::set(const OCTET_STRING_t& capability) {
  return conv::octet_string_copy(ue_radio_capability_, capability);
}

//------------------------------------------------------------------------------
bool UERadioCapability::get(OCTET_STRING_t& capability) {
  return conv::octet_string_copy(capability, ue_radio_capability_);
}

//------------------------------------------------------------------------------
bool UERadioCapability::set(const bstring& capability) {
  return conv::bstring_2_octet_string(capability, ue_radio_capability_);
}

//------------------------------------------------------------------------------
bool UERadioCapability::get(bstring& capability) {
  return conv::octet_string_2_bstring(ue_radio_capability_, capability);
}

}  // namespace ngap
