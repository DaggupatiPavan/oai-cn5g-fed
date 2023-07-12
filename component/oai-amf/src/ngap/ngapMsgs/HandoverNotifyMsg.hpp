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

#ifndef _HANDOVER_NOTIFY_MSG_H_
#define _HANDOVER_NOTIFY_MSG_H_

#include "AMF-UE-NGAP-ID.hpp"
#include "UserLocationInformation.hpp"
#include "NgapUEMessage.hpp"

extern "C" {
#include "Ngap_HandoverNotify.h"
}

namespace ngap {
class HandoverNotifyMsg : public NgapUEMessage {
 public:
  HandoverNotifyMsg();
  virtual ~HandoverNotifyMsg();

  void initialize();
  void setAmfUeNgapId(const unsigned long& id) override;
  void setRanUeNgapId(const uint32_t& id) override;
  bool decodeFromPdu(Ngap_NGAP_PDU_t* ngapMsgPdu) override;

  void setUserLocationInfoNR(const NrCgi_t& cig, const Tai_t& tai);
  bool getUserLocationInfoNR(NrCgi_t& cig, Tai_t& tai);

 private:
  Ngap_HandoverNotify_t* handoverNotifyIEs;
  // AMF_UE_NGAP_ID (Mandatory)
  // RAN_UE_NGAP_ID (Mandatory)
  UserLocationInformation userLocationInformation;  // Mandatory
};

}  // namespace ngap
#endif