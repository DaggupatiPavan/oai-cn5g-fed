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

#include "amf_n2.hpp"

#include <boost/chrono.hpp>
#include <boost/chrono/chrono.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/system_clocks.hpp>

#include "3gpp_24.501.h"
#include "DefaultPagingDRX.hpp"
#include "DownlinkNasTransport.hpp"
#include "HandoverPreparationFailure.hpp"
#include "InitialContextSetupRequest.hpp"
#include "NGResetAck.hpp"
#include "NGSetupFailure.hpp"
#include "NGSetupResponse.hpp"
#include "Ngap_Cause.h"
#include "Ngap_CauseNas.h"
#include "Ngap_CauseRadioNetwork.h"
#include "Ngap_TimeToWait.h"
#include "PDUSessionResourceHandoverCommandTransfer.hpp"
#include "Paging.hpp"
#include "PduSessionResourceModifyRequest.hpp"
#include "PduSessionResourceReleaseCommand.hpp"
#include "PduSessionResourceSetupRequest.hpp"
#include "RerouteNASRequest.hpp"
#include "UEContextReleaseCommand.hpp"
#include "amf_app.hpp"
#include "amf_config.hpp"
#include "amf_n1.hpp"
#include "amf_sbi.hpp"
#include "amf_statistics.hpp"
#include "comUt.hpp"
#include "itti.hpp"
#include "itti_msg_amf_app.hpp"
#include "logger.hpp"
#include "sctp_server.hpp"

extern "C" {
#include "dynamic_memory_check.h"
}

using namespace amf_application;
using namespace config;
using namespace ngap;
using namespace std;
extern itti_mw* itti_inst;
extern amf_n2* amf_n2_inst;
extern amf_n1* amf_n1_inst;
extern amf_config amf_cfg;
extern amf_app* amf_app_inst;
extern statistics stacs;

void amf_n2_task(void*);

//------------------------------------------------------------------------------
void amf_n2_task(void* args_p) {
  const task_id_t task_id = TASK_AMF_N2;
  itti_inst->notify_task_ready(task_id);
  do {
    std::shared_ptr<itti_msg> shared_msg = itti_inst->receive_msg(task_id);
    auto* msg                            = shared_msg.get();
    switch (msg->msg_type) {
      case NEW_SCTP_ASSOCIATION: {
        Logger::amf_n2().info("Received new SCTP_ASSOCIATION");
        // TODO:
        itti_new_sctp_association* m =
            dynamic_cast<itti_new_sctp_association*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case NG_SETUP_REQ: {
        Logger::amf_n2().info("Received NGSetupRequest message, handling");
        auto msg = std::dynamic_pointer_cast<itti_ng_setup_request>(shared_msg);
        amf_n2_inst->handle_itti_message(msg);
      } break;
      case NG_RESET: {
        Logger::amf_n2().info("Received NGReset message, handling");
        // TODO:
        itti_ng_reset* m = dynamic_cast<itti_ng_reset*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case NG_SHUTDOWN: {
        Logger::amf_n2().info("Received SCTP Shutdown Event, handling");
        // TODO:
        itti_ng_shutdown* m = dynamic_cast<itti_ng_shutdown*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case INITIAL_UE_MSG: {
        Logger::amf_n2().info("Received INITIAL_UE_MESSAGE message, handling");
        itti_initial_ue_message* m =
            dynamic_cast<itti_initial_ue_message*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case ITTI_UL_NAS_TRANSPORT: {
        Logger::amf_n2().info(
            "Received UPLINK_NAS_TRANSPORT message, handling");
        itti_ul_nas_transport* m = dynamic_cast<itti_ul_nas_transport*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case ITTI_DL_NAS_TRANSPORT: {
        Logger::amf_n2().info(
            "Encoding DOWNLINK NAS TRANSPORT message, sending");
        itti_dl_nas_transport* m = dynamic_cast<itti_dl_nas_transport*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case PDU_SESSION_RESOURCE_SETUP_REQUEST: {
        Logger::amf_n2().info(
            "Encoding PDU SESSION RESOURCE SETUP REQUEST message, sending");
        itti_pdu_session_resource_setup_request* m =
            dynamic_cast<itti_pdu_session_resource_setup_request*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case PDU_SESSION_RESOURCE_MODIFY_REQUEST: {
        Logger::amf_n2().info(
            "Received PDU_SESSION_RESOURCE_MODIFY_REQUEST message, handling");
        itti_pdu_session_resource_modify_request* m =
            dynamic_cast<itti_pdu_session_resource_modify_request*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case INITIAL_CONTEXT_SETUP_REQUEST: {
        Logger::amf_n2().info(
            "Encoding INITIAL CONTEXT SETUP REQUEST message, sending");
        itti_initial_context_setup_request* m =
            dynamic_cast<itti_initial_context_setup_request*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case UE_CONTEXT_RELEASE_REQUEST: {
        Logger::amf_n2().info(
            "Received UE_CONTEXT_RELEASE_REQUEST message, handling");
        itti_ue_context_release_request* m =
            dynamic_cast<itti_ue_context_release_request*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case UE_CONTEXT_RELEASE_COMMAND: {
        Logger::amf_n2().info(
            "Received UE_CONTEXT_RELEASE_COMMAND message, handling");
        itti_ue_context_release_command* m =
            dynamic_cast<itti_ue_context_release_command*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case UE_CONTEXT_RELEASE_COMPLETE: {
        Logger::amf_n2().info(
            "Received UE_CONTEXT_RELEASE_COMPLETE message, handling");
        itti_ue_context_release_complete* m =
            dynamic_cast<itti_ue_context_release_complete*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case PDU_SESSION_RESOURCE_RELEASE_COMMAND: {
        Logger::amf_n2().info(
            "Received PDU_SESSION_RESOURCE_RELEASE_COMMAND message, handling");
        itti_pdu_session_resource_release_command* m =
            dynamic_cast<itti_pdu_session_resource_release_command*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case UE_RADIO_CAP_IND: {
        Logger::amf_n2().info("Received UE_RADIO_CAP_IND message, handling");
        itti_ue_radio_capability_indication* m =
            dynamic_cast<itti_ue_radio_capability_indication*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case HANDOVER_REQUIRED_MSG: {
        Logger::amf_n2().info("Received HANDOVER_REQUIRED message, handling");
        itti_handover_required* m = dynamic_cast<itti_handover_required*>(msg);
        if (!amf_n2_inst->handle_itti_message(ref(*m)))
          amf_n2_inst->send_handover_preparation_failure(
              m->handoverReq->getAmfUeNgapId(),
              m->handoverReq->getRanUeNgapId(), m->assoc_id);
      } break;
      case HANDOVER_REQUEST_ACK: {
        Logger::amf_n2().info(
            "Received HANDOVER_REQUEST_ACK message, handling");
        itti_handover_request_Ack* m =
            dynamic_cast<itti_handover_request_Ack*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case HANDOVER_NOTIFY: {
        Logger::amf_n2().info("Received HANDOVER_NOTIFY message, handling");
        itti_handover_notify* m = dynamic_cast<itti_handover_notify*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case UPLINK_RAN_STATUS_TRANSFER: {
        Logger::amf_n2().info(
            "Received UPLINK_RAN_STATUS_TRANSFER message, handling");
        itti_uplink_ran_status_transfer* m =
            dynamic_cast<itti_uplink_ran_status_transfer*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case PAGING: {
        Logger::amf_n2().info("Received Paging message, handling");
        itti_paging* m = dynamic_cast<itti_paging*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case REROUTE_NAS_REQ: {
        Logger::amf_n2().info("Received Reroute NAS Req message, handling");
        itti_rereoute_nas* m = dynamic_cast<itti_rereoute_nas*>(msg);
        amf_n2_inst->handle_itti_message(ref(*m));
      } break;
      case TERMINATE: {
        if (itti_msg_terminate* terminate =
                dynamic_cast<itti_msg_terminate*>(msg)) {
          Logger::amf_n2().info("Received terminate message");
          return;
        }
      } break;
      default:
        Logger::amf_n2().info("No handler for msg type %d", msg->msg_type);
    }
  } while (true);
}

//------------------------------------------------------------------------------
amf_n2::amf_n2(const std::string& address, const uint16_t port_num)
    : ngap_app(address, port_num), m_ranid2uecontext(), m_amfueid2uecontext() {
  if (itti_inst->create_task(TASK_AMF_N2, amf_n2_task, nullptr)) {
    Logger::amf_n2().error("Cannot create task TASK_AMF_N2");
    throw std::runtime_error("Cannot create task TASK_AMF_N2");
  }
  ranid2uecontext   = {};
  amfueid2uecontext = {};
  Logger::amf_n2().startup("amf_n2 started");
}

//------------------------------------------------------------------------------
amf_n2::~amf_n2() {}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_paging& itti_msg) {
  Logger::amf_n2().debug("Handle Paging message...");

  std::shared_ptr<ue_ngap_context> unc = {};

  if (!is_ran_ue_id_2_ue_ngap_context(itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        itti_msg.ran_ue_ngap_id);
    return;
  }

  if (unc->amf_ue_ngap_id != itti_msg.amf_ue_ngap_id) {
    Logger::amf_n2().error(
        "The requested UE (amf_ue_ngap_id: " AMF_UE_NGAP_ID_FMT
        ") is not valid, existed UE "
        "which's amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        itti_msg.amf_ue_ngap_id, unc->amf_ue_ngap_id);
  }

  // TODO: check UE reachability status

  // get NAS context
  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(itti_msg.amf_ue_ngap_id, nc)) {
    Logger::amf_n2().warn(
        "No existed nas_context with amf_ue_ngap_id(" AMF_UE_NGAP_ID_FMT ")",
        itti_msg.amf_ue_ngap_id);
  }
  // Network stops sending paging messages since the mobile reachable timer
  // expires
  if (amf_n1_inst->get_mobile_reachable_timer_timeout(nc)) {
    return;
  }

  PagingMsg paging_msg = {};
  Logger::amf_n2().debug(
      " UE NGAP Context, s_setid (%d), s_pointer (%d), s_tmsi (%d)",
      unc->s_setid, unc->s_pointer, unc->s_tmsi);
  paging_msg.setUEPagingIdentity(unc->s_setid, unc->s_pointer, unc->s_tmsi);

  std ::vector<struct Tai_s> list;
  Tai_t tai = {};
  tai.mcc   = unc->tai.mcc;
  tai.mnc   = unc->tai.mnc;
  tai.tac   = unc->tai.tac;

  list.push_back(tai);
  paging_msg.setTAIListForPaging(list);

  uint8_t buffer[BUFFER_SIZE_512];
  int encoded_size = paging_msg.encode2Buffer(buffer, BUFFER_SIZE_512);
  bstring b        = blk2bstr(buffer, encoded_size);

  amf_n2_inst->sctp_s_38412.sctp_send_msg(
      unc->gnb_assoc_id, unc->sctp_stream_send, &b);

  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_new_sctp_association& new_assoc) {}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(
    std::shared_ptr<itti_ng_setup_request>& itti_msg) {
  Logger::amf_n2().debug("Handle NG Setup Request...");
  Logger::amf_n2().debug(
      "Parameters: assoc_id %d, stream %d", itti_msg->assoc_id,
      itti_msg->stream);

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg->assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existed gNB context with assoc_id(%d)", itti_msg->assoc_id);
    return;
  }

  if (gc->ng_state == NGAP_RESETING || gc->ng_state == NGAP_SHUTDOWN) {
    Logger::amf_n2().warn(
        "Received a new association request on an association that is being "
        "%s, "
        "ignoring",
        ng_gnb_state_str[gc->ng_state]);
  } else {
    Logger::amf_n2().debug(
        "Update gNB context with assoc id (%d)", itti_msg->assoc_id);
  }

  gnb_infos gnbItem = {};

  // Get IE Global RAN Node ID
  uint32_t gnb_id     = {};
  std::string gnb_mcc = {};
  std::string gnb_mnc = {};
  if (!itti_msg->ngSetupReq->getGlobalGnbID(gnb_id, gnb_mcc, gnb_mnc)) {
    Logger::amf_n2().error("Missing Mandatory IE Global RAN Node ID");
    return;
  }
  Logger::amf_n2().debug(
      "RAN Node Info, Global RAN Node ID: 0x%x, MCC %s, MNC %s", gnb_id,
      gnb_mcc.c_str(), gnb_mnc.c_str());
  gc->globalRanNodeId = gnb_id;
  gnbItem.gnb_id      = gnb_id;
  gnbItem.mcc         = gnb_mcc;
  gnbItem.mnc         = gnb_mnc;

  std::string gnb_name = {};
  if (!itti_msg->ngSetupReq->getRanNodeName(gnb_name)) {
    Logger::amf_n2().warn("Missing IE RanNodeName");
  } else {
    gc->gnb_name     = gnb_name;
    gnbItem.gnb_name = gnb_name;
    Logger::amf_n2().debug("IE RanNodeName: %s", gnb_name.c_str());
  }

  // store Paging DRX in gNB context
  // TODO: To fix DefaultPagingDRX value
  int defPagingDrx = itti_msg->ngSetupReq->getDefaultPagingDRX();
  if (defPagingDrx == -1) {
    Logger::amf_n2().error("Missing Mandatory IE DefaultPagingDRX");
    return;
  }
  Logger::amf_n2().debug("IE DefaultPagingDRX: %d", defPagingDrx);

  // Get supported TA List
  vector<SupportedTaItem_t> s_ta_list;
  if (!itti_msg->ngSetupReq->getSupportedTAList(s_ta_list)) {
    Logger::amf_n2().error("Missing Mandatory IE Supported TA List");
    return;
  }

  // Verify PLMN Identity and TAC with configuration and store supportedTAList
  // in gNB context, if verified; else response NG SETUP FAILURE with cause
  // "Unknown PLMN"(9.3.1.2, ts38413)

  if (!get_common_plmn(s_ta_list, gc->s_ta_list)) {
    // encode NG SETUP FAILURE MESSAGE and send back
    uint8_t* buffer = (uint8_t*) calloc(1, BUFFER_SIZE_1024);
    NGSetupFailureMsg ngSetupFailure;
    ngSetupFailure.set(Ngap_CauseRadioNetwork_unspecified, Ngap_TimeToWait_v5s);
    int encoded =
        ngSetupFailure.encode2Buffer((uint8_t*) buffer, BUFFER_SIZE_1024);

    if (encoded < 1) {
      Logger::amf_n2().error("Encode NG Setup Failure message error!");
      return;
    }

    bstring b = blk2bstr(buffer, encoded);
    sctp_s_38412.sctp_send_msg(itti_msg->assoc_id, itti_msg->stream, &b);
    Logger::amf_n2().error(
        "No common PLMN, encoding NG_SETUP_FAILURE with cause (Unknown PLMN)");
    bdestroy_wrapper(&b);
    return;

  } else {
    for (auto i : gc->s_ta_list) {
      gnbItem.plmn_list.push_back(i);
    }
  }

  set_gnb_id_2_gnb_context(gnb_id, gc);

  Logger::amf_n2().debug("Encoding NG_SETUP_RESPONSE ...");
  // encode NG SETUP RESPONSE message with information stored in configuration
  // file and send_msg
  uint8_t* buffer                = (uint8_t*) calloc(1, BUFFER_SIZE_1024);
  NGSetupResponseMsg ngSetupResp = {};
  ngSetupResp.setAMFName(amf_cfg.amf_name);
  std::vector<GuamiItem_t> guami_list;
  for (int i = 0; i < amf_cfg.guami_list.size(); i++) {
    GuamiItem_t tmp = {};
    tmp.mcc         = amf_cfg.guami_list[i].mcc;
    tmp.mnc         = amf_cfg.guami_list[i].mnc;
    tmp.regionID    = amf_cfg.guami_list[i].regionID;
    tmp.AmfSetID    = amf_cfg.guami_list[i].AmfSetID;
    tmp.AmfPointer  = amf_cfg.guami_list[i].AmfPointer;
    guami_list.push_back(tmp);
  }
  ngSetupResp.setGUAMIList(guami_list);

  ngSetupResp.setRelativeAmfCapacity(amf_cfg.relative_amf_capacity);
  std::vector<PlmnSliceSupport_t> plmn_list;
  for (int i = 0; i < amf_cfg.plmn_list.size(); i++) {
    PlmnSliceSupport_t tmp = {};
    tmp.mcc                = amf_cfg.plmn_list[i].mcc;
    tmp.mnc                = amf_cfg.plmn_list[i].mnc;
    for (int j = 0; j < amf_cfg.plmn_list[i].slice_list.size(); j++) {
      S_Nssai s_tmp = {};
      s_tmp.sst     = std::to_string(amf_cfg.plmn_list[i].slice_list[j].sst);
      s_tmp.sd      = std::to_string(amf_cfg.plmn_list[i].slice_list[j].sd);
      tmp.slice_list.push_back(s_tmp);
    }
    plmn_list.push_back(tmp);
  }

  ngSetupResp.setPlmnSupportList(plmn_list);
  int encoded = ngSetupResp.encode2Buffer((uint8_t*) buffer, BUFFER_SIZE_1024);

  if (encoded < 1) {
    Logger::amf_n2().error("Encode NG Setup Response message error!");
    return;
  }

  bstring b = blk2bstr(buffer, encoded);
  sctp_s_38412.sctp_send_msg(itti_msg->assoc_id, itti_msg->stream, &b);
  Logger::amf_n2().debug("Sending NG_SETUP_RESPONSE Ok");
  gc->ng_state = NGAP_READY;
  Logger::amf_n2().debug(
      "gNB with gNB_id 0x%x, assoc_id %d has been attached to AMF",
      gc->globalRanNodeId, itti_msg->assoc_id);
  stacs.add_gnb(gnbItem.gnb_id, gnbItem);
  bdestroy_wrapper(&b);
  return;
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_ng_reset& itti_msg) {
  Logger::amf_n2().debug("Handle NG Reset...");
  Logger::amf_n2().debug(
      "Parameters: assoc_id %d, stream %d", itti_msg.assoc_id, itti_msg.stream);

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existed gNB context with assoc_id(%d)", itti_msg.assoc_id);
    return;
  }

  gc->ng_state = NGAP_RESETING;
  // TODO: (8.7.4.2.2, NG Reset initiated by the NG-RAN node @3GPP TS 38.413
  // V16.0.0) the AMF shall release all allocated resources on NG related to the
  // UE association(s) indicated explicitly or implicitly in the NG RESET
  // message and remove the NGAP ID for the indicated UE associations.
  ResetType reset_type = {};
  std::vector<UEAssociatedLogicalNGConnectionItem>
      ueAssociatedLogicalNGConnectionList;
  itti_msg.ngReset->getResetType(reset_type);
  if (reset_type.getResetType() == Ngap_ResetType_PR_nG_Interface) {
    // Reset all
    // release all the resources related to this interface

    std::vector<std::shared_ptr<ue_ngap_context>> ue_contexts;
    get_ue_ngap_contexts(itti_msg.assoc_id, ue_contexts);

    for (auto ue_context : ue_contexts) {
      remove_ue_context_with_amf_ue_ngap_id(ue_context->amf_ue_ngap_id);
      remove_ue_context_with_ran_ue_ngap_id(ue_context->ran_ue_ngap_id);
    }

    stacs.display();
  } else if (
      reset_type.getResetType() == Ngap_ResetType_PR_partOfNG_Interface) {
    // TODO:
    reset_type.getUE_associatedLogicalNG_connectionList(
        ueAssociatedLogicalNGConnectionList);
    for (auto ue : ueAssociatedLogicalNGConnectionList) {
      unsigned long amf_ue_ngap_id = {0};
      uint32_t ran_ue_ngap_id      = {0};
      if (ue.getAmfUeNgapId(amf_ue_ngap_id)) {
        remove_ue_context_with_amf_ue_ngap_id(amf_ue_ngap_id);
      } else if (ue.getRanUeNgapId(ran_ue_ngap_id)) {
        remove_ue_context_with_ran_ue_ngap_id(ran_ue_ngap_id);
      }
    }
  }

  // TODO: create NGResetAck and reply to gNB
  std::unique_ptr<NGResetAckMsg> ng_reset_ack =
      std::make_unique<NGResetAckMsg>();
  // UEAssociatedLogicalNGConnectionList
  if (ueAssociatedLogicalNGConnectionList.size() > 0) {
    ng_reset_ack->setUE_associatedLogicalNG_connectionList(
        ueAssociatedLogicalNGConnectionList);
  }

  uint8_t buffer[BUFFER_SIZE_512];
  int encoded_size = ng_reset_ack->encode2Buffer(buffer, BUFFER_SIZE_512);

  bstring b = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, itti_msg.stream, &b);
  bdestroy_wrapper(&b);
  return;
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_ng_shutdown& itti_msg) {
  Logger::amf_n2().debug("Handle NG Shutdown ...");
  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existed gNB context with assoc_id(%d)", itti_msg.assoc_id);
    return;
  }

  gc->ng_state = NGAP_SHUTDOWN;

  // Release all the resources related to this interface
  std::vector<std::shared_ptr<ue_ngap_context>> ue_contexts;
  get_ue_ngap_contexts(itti_msg.assoc_id, ue_contexts);

  for (auto ue_context : ue_contexts) {
    remove_ue_context_with_amf_ue_ngap_id(ue_context->amf_ue_ngap_id);
    remove_ue_context_with_ran_ue_ngap_id(ue_context->ran_ue_ngap_id);
  }

  // Delete gNB context
  remove_gnb_context(itti_msg.assoc_id);
  stacs.remove_gnb(gc->globalRanNodeId);

  Logger::amf_n2().debug(
      "Remove gNB with association id %d, globalRanNodeId 0x%x",
      itti_msg.assoc_id, gc->globalRanNodeId);
  stacs.display();
  return;
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_initial_ue_message& init_ue_msg) {
  Logger::amf_n2().debug("Handle Initial UE Message...");

  // Create NGAP-UE context and store in gNB context to store UE information in
  // gNB, for example, here RAN UE NGAP ID and location information and RRC
  // Establishment Cause send NAS-PDU to NAS layer Get INITIAL_UE_MESSAGE IEs

  // Check the gNB context on which  this UE is attached with assoc_id
  std::shared_ptr<itti_nas_signalling_establishment_request> itti_msg =
      std::make_shared<itti_nas_signalling_establishment_request>(
          TASK_AMF_N2, TASK_AMF_APP);

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(init_ue_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", init_ue_msg.assoc_id);
    return;
  }

  if (gc->ng_state == NGAP_RESETING || gc->ng_state == NGAP_SHUTDOWN) {
    Logger::amf_n2().warn(
        "Received new association request on an association that is being %s, "
        "ignoring",
        ng_gnb_state_str[gc->ng_state]);
  } else if (gc->ng_state != NGAP_READY) {
    Logger::amf_n2().debug(
        "gNB with assoc_id (%d) is illegal", init_ue_msg.assoc_id);
    return;
  }

  if (!init_ue_msg.initUeMsg) return;

  // UE NGAP Context
  uint32_t ran_ue_ngap_id = 0;
  if (!init_ue_msg.initUeMsg->getRanUENgapID(ran_ue_ngap_id)) {
    Logger::amf_n2().error("Missing Mandatory IE (RanUeNgapId)");
    return;
  }

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!is_ran_ue_id_2_ue_ngap_context(ran_ue_ngap_id, unc)) {
    Logger::amf_n2().debug(
        "Create a new UE NGAP context with ran_ue_ngap_id " GNB_UE_NGAP_ID_FMT,
        ran_ue_ngap_id);
    unc = std::shared_ptr<ue_ngap_context>(new ue_ngap_context());
    set_ran_ue_ngap_id_2_ue_ngap_context(ran_ue_ngap_id, unc);
  }

  if (unc == nullptr) {
    Logger::amf_n2().error(
        "Failed to get UE NGAP context for ran_ue_ngap_id " GNB_UE_NGAP_ID_FMT,
        ran_ue_ngap_id);
  } else {
    // Store related information into UE NGAP context
    unc->ran_ue_ngap_id   = ran_ue_ngap_id;
    unc->sctp_stream_recv = init_ue_msg.stream;
    unc->sctp_stream_send == gc->next_sctp_stream;
    gc->next_sctp_stream += 1;
    if (gc->next_sctp_stream >= gc->instreams) gc->next_sctp_stream = 1;
    unc->gnb_assoc_id = init_ue_msg.assoc_id;
    NrCgi_t cgi       = {};
    Tai_t tai         = {};

    if (init_ue_msg.initUeMsg->getUserLocationInfoNR(cgi, tai)) {
      itti_msg->cgi = cgi;
      itti_msg->tai = tai;
      unc->tai      = tai;
    } else {
      Logger::amf_n2().error("Missing Mandatory IE UserLocationInfoNR");
      return;
    }

    if (init_ue_msg.initUeMsg->getRRCEstablishmentCause() == -1) {
      Logger::amf_n2().warn("IE RRCEstablishmentCause not present");
      itti_msg->rrc_cause = -1;  // not present, TODO with optional
    } else {
      itti_msg->rrc_cause = init_ue_msg.initUeMsg->getRRCEstablishmentCause();
    }

    if (init_ue_msg.initUeMsg->getUeContextRequest() == -1) {
      Logger::amf_n2().warn("IE UeContextRequest not present");
      itti_msg->ueCtxReq = -1;  // not present, TODO with optional
    } else {
      itti_msg->ueCtxReq = init_ue_msg.initUeMsg->getUeContextRequest();
    }

    std::string _5g_s_tmsi = {};
    if (!init_ue_msg.initUeMsg->get5GS_TMSI(_5g_s_tmsi)) {
      itti_msg->is_5g_s_tmsi_present = false;
      Logger::amf_n2().debug("5g_s_tmsi not present");
    } else {
      itti_msg->is_5g_s_tmsi_present = true;
      itti_msg->_5g_s_tmsi           = _5g_s_tmsi;
      Logger::amf_n2().debug("5g_s_tmsi present");

      init_ue_msg.initUeMsg->get5GS_TMSI(
          unc->s_setid, unc->s_pointer, unc->s_tmsi);
    }

    if (!init_ue_msg.initUeMsg->getNasPdu(itti_msg->nas_buf)) {
      Logger::amf_n2().error("Missing IE NAS-PDU");
      return;
    }
  }

  // Store InitialUEMessage for Rereoute NAS later
  if (unc->initialUEMsg.buf) {
    Logger::amf_n2().debug(
        "Store InitialUEMessage for Reroute NAS (if necessary)");
    uint8_t* initial_ue_msg_buf = (uint8_t*) calloc(1, BUFFER_SIZE_1024);
    int encoded_size            = 0;
    init_ue_msg.initUeMsg->encode2Buffer(initial_ue_msg_buf, encoded_size);

    if (encoded_size > 0) {
      Logger::amf_n2().debug("Encoded InitialUEMessage size %d", encoded_size);
      memcpy(
          (void*) unc->initialUEMsg.buf, (void*) initial_ue_msg_buf,
          encoded_size);
      comUt::print_buffer(
          "ngap", "InitialUEMessage", unc->initialUEMsg.buf, encoded_size);
      unc->initialUEMsg.size = encoded_size;
    }
  }

  itti_msg->ran_ue_ngap_id = ran_ue_ngap_id;
  itti_msg->amf_ue_ngap_id = INVALID_AMF_UE_NGAP_ID;

  int ret = itti_inst->send_msg(itti_msg);
  if (0 != ret) {
    Logger::amf_n2().error(
        "Could not send ITTI message %s to task TASK_AMF_APP",
        itti_msg->get_msg_name());
  }
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_ul_nas_transport& ul_nas_transport) {
  Logger::amf_n2().debug("Handle Uplink NAS Transport...");

  unsigned long amf_ue_ngap_id    = ul_nas_transport.ulNas->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id         = ul_nas_transport.ulNas->getRanUeNgapId();
  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(ul_nas_transport.assoc_id, gc)) {
    Logger::amf_n2().error(
        "gNB with assoc_id (%d) is illegal", ul_nas_transport.assoc_id);
    return;
  }

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!is_ran_ue_id_2_ue_ngap_context(ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "UE with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT
        ") is not attached to gnb with assoc_id "
        "(%d)",
        ran_ue_ngap_id, ul_nas_transport.assoc_id);
    return;
  }

  if (unc->amf_ue_ngap_id != amf_ue_ngap_id) {
    Logger::amf_n2().error(
        "The requested UE (amf_ue_ngap_id: " AMF_UE_NGAP_ID_FMT
        ") is not valid, existed UE "
        "which's amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id, unc->amf_ue_ngap_id);
  }
  /*
     //TODO: check with a correct NGAP state
     if (unc->ng_ue_state != NGAP_UE_CONNECTED) {
      Logger::amf_n2().error(
          "Received NGAP UPLINK_NAS_TRANSPORT while UE in state != "
          "NGAP_UE_CONNECTED");
      // return;
    }
    */

  std::shared_ptr<itti_uplink_nas_data_ind> itti_msg =
      std::make_shared<itti_uplink_nas_data_ind>(TASK_AMF_N2, TASK_AMF_N1);

  itti_msg->is_nas_signalling_estab_req = false;
  itti_msg->amf_ue_ngap_id              = amf_ue_ngap_id;
  itti_msg->ran_ue_ngap_id              = ran_ue_ngap_id;
  itti_msg->is_guti_valid               = false;

  if (!ul_nas_transport.ulNas->getNasPdu(itti_msg->nas_msg)) {
    Logger::amf_n2().error("Missing IE NAS-PDU");
    return;
  }

  // UserLocation
  NrCgi_t cgi = {};
  Tai_t tai   = {};
  if (ul_nas_transport.ulNas->getUserLocationInfoNR(cgi, tai)) {
    itti_msg->mcc = cgi.mcc;
    itti_msg->mnc = cgi.mnc;
  } else {
    Logger::amf_n2().debug("Missing IE UserLocationInformationNR");
  }

  int ret = itti_inst->send_msg(itti_msg);
  if (0 != ret) {
    Logger::amf_n2().error(
        "Could not send ITTI message %s to task TASK_AMF_N1",
        itti_msg->get_msg_name());
  }
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_dl_nas_transport& dl_nas_transport) {
  Logger::amf_n2().debug("Handle DL NAS Transport ...");

  std::shared_ptr<ue_ngap_context> unc = {};

  if (!amf_n2_inst->is_ran_ue_id_2_ue_ngap_context(
          dl_nas_transport.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        dl_nas_transport.ran_ue_ngap_id);
    return;
  }

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", unc->gnb_assoc_id);
    return;
  }

  unc->amf_ue_ngap_id = dl_nas_transport.amf_ue_ngap_id;
  set_amf_ue_ngap_id_2_ue_ngap_context(unc->amf_ue_ngap_id, unc);
  unc->ng_ue_state = NGAP_UE_CONNECTED;
  std::unique_ptr<DownLinkNasTransportMsg> ngap_msg =
      std::make_unique<DownLinkNasTransportMsg>();
  ngap_msg->setAmfUeNgapId(dl_nas_transport.amf_ue_ngap_id);
  ngap_msg->setRanUeNgapId(dl_nas_transport.ran_ue_ngap_id);
  ngap_msg->setNasPdu(dl_nas_transport.nas);

  uint8_t buffer[BUFFER_SIZE_1024];
  int encoded_size = ngap_msg->encode2Buffer(buffer, BUFFER_SIZE_1024);
  bstring b        = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, unc->sctp_stream_send, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_initial_context_setup_request& itti_msg) {
  Logger::amf_n2().debug("Handle Initial Context Setup Request ...");

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!amf_n2_inst->is_ran_ue_id_2_ue_ngap_context(
          itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        itti_msg.ran_ue_ngap_id);
    return;
  }

  unc->ncc                        = 1;
  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", unc->gnb_assoc_id);
    return;
  }

  std::unique_ptr<InitialContextSetupRequestMsg> msg =
      std::make_unique<InitialContextSetupRequestMsg>();
  msg->setAmfUeNgapId(itti_msg.amf_ue_ngap_id);
  msg->setRanUeNgapId(itti_msg.ran_ue_ngap_id);
  Guami_t guami    = {};
  guami.mcc        = amf_cfg.guami.mcc;
  guami.mnc        = amf_cfg.guami.mnc;
  guami.regionID   = amf_cfg.guami.regionID;
  guami.AmfSetID   = amf_cfg.guami.AmfSetID;
  guami.AmfPointer = amf_cfg.guami.AmfPointer;
  msg->setGuami(guami);
  msg->setUESecurityCapability(
      0xe000, 0xe000, 0xe000,
      0xe000);  // TODO: remove hardcoded value
  msg->setSecurityKey((uint8_t*) bdata(itti_msg.kgnb));
  msg->setNasPdu(itti_msg.nas);

  // Get the list allowed NSSAI from the common PLMN between gNB and AMF
  std::vector<S_Nssai> list;
  /*  for (auto p : amf_cfg.plmn_list) {
      for (auto s : p.slice_list) {
        S_Nssai item;
        item.sst = s.sST;
        item.sd  = s.sD;
        list.push_back(item);
      }
    }
  */
  for (auto s : gc->s_ta_list) {
    for (auto p : s.b_plmn_list) {
      for (auto s : p.slice_list) {
        S_Nssai item;
        item.sst = s.sst;
        item.sd  = s.sd;
        list.push_back(item);
      }
    }
  }
  msg->setAllowedNssai(list);

  if (itti_msg.is_sr or itti_msg.is_pdu_exist) {
    // Set UE Radio Capability if available
    if (gc->ue_radio_cap_ind) {
      msg->setUERadioCapability(gc->ue_radio_cap_ind);
    }

    if (itti_msg.is_sr)
      Logger::amf_n2().debug("Encoding parameters for Service Request");
    else
      Logger::amf_n2().debug(
          "Encoding parameters for Initial Context Setup Request");

    if (itti_msg.is_pdu_exist) {
      // TODO: with multiple PDU Sessions
      std::vector<PDUSessionResourceSetupRequestItem_t> list;
      PDUSessionResourceSetupRequestItem_t item = {};
      item.pduSessionId                         = itti_msg.pdu_session_id;

      // Get NSSAI from PDU Session Context
      std::shared_ptr<nas_context> nc = {};
      if (!amf_n1_inst->is_amf_ue_id_2_nas_context(
              itti_msg.amf_ue_ngap_id, nc)) {
        Logger::amf_n2().warn(
            "No existed nas_context with amf_ue_ngap_id(" AMF_UE_NGAP_ID_FMT
            ")",
            itti_msg.amf_ue_ngap_id);
        // TODO:
      }
      string supi = "imsi-" + nc->imsi;
      Logger::amf_n2().debug("SUPI (%s)", supi.c_str());

      // Get S_NSSAI from PDU Session Context
      std::shared_ptr<pdu_session_context> psc = {};

      if (!amf_app_inst->find_pdu_session_context(
              supi, itti_msg.pdu_session_id, psc)) {
        Logger::amf_n2().warn(
            "Cannot get pdu_session_context with SUPI (%s)", supi.c_str());
        item.s_nssai.sst = "01";  // TODO: remove the default value
        item.s_nssai.sd  = std::to_string(SD_NO_VALUE);
      } else {
        item.s_nssai.sst = std::to_string(psc->snssai.sST);
        item.s_nssai.sd  = psc->snssai.sD;
      }

      Logger::amf_n2().debug(
          "S_NSSAI (SST, SD) %s, %s", item.s_nssai.sst.c_str(),
          item.s_nssai.sd.c_str());

      // item.pduSessionNAS_PDU = NULL;
      if (itti_msg.is_n2sm_avaliable) {
        if (blength(itti_msg.n2sm) != 0) {
          conv::bstring_2_octet_string(
              itti_msg.n2sm, item.pduSessionResourceSetupRequestTransfer);
        } else {
          Logger::amf_n2().error("n2sm empty!");
        }
      }
      list.push_back(item);
      msg->setPduSessionResourceSetupRequestList(list);

      // UEAggregateMaximumBitRate
      msg->setUEAggregateMaxBitRate(
          UE_AGGREGATE_MAXIMUM_BIT_RATE_DL, UE_AGGREGATE_MAXIMUM_BIT_RATE_UL);

      // TODO: Mobility RestrictionList
    }
  }

  uint8_t buffer[BUFFER_SIZE_2048];
  int encoded_size = msg->encode2Buffer(buffer, BUFFER_SIZE_2048);
  bstring b        = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, unc->sctp_stream_send, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(
    itti_pdu_session_resource_setup_request& itti_msg) {
  Logger::amf_n2().debug("Handle PDU Session Resource Setup Request ...");

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!amf_n2_inst->is_ran_ue_id_2_ue_ngap_context(
          itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        itti_msg.ran_ue_ngap_id);
    return;
  }

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", unc->gnb_assoc_id);
    return;
  }

  std::unique_ptr<PduSessionResourceSetupRequestMsg> psrsr =
      std::make_unique<PduSessionResourceSetupRequestMsg>();
  psrsr->setAmfUeNgapId(itti_msg.amf_ue_ngap_id);
  psrsr->setRanUeNgapId(itti_msg.ran_ue_ngap_id);

  std::vector<PDUSessionResourceSetupRequestItem_t> list;
  PDUSessionResourceSetupRequestItem_t item = {};
  item.pduSessionId                         = itti_msg.pdu_session_id;
  item.nas_pdu                              = bstrcpy(itti_msg.nas);

  // Get NSSAI from PDU Session Context
  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(itti_msg.amf_ue_ngap_id, nc)) {
    Logger::amf_n2().warn(
        "No existed nas_context with amf_ue_ngap_id(" AMF_UE_NGAP_ID_FMT ")",
        itti_msg.amf_ue_ngap_id);
    // TODO:
  }
  string supi = "imsi-" + nc->imsi;
  Logger::amf_n2().debug("SUPI (%s)", supi.c_str());

  // Get SNSSAI info from PDU Session Context
  item.s_nssai.sd                          = {};
  std::shared_ptr<pdu_session_context> psc = {};
  if (!amf_app_inst->find_pdu_session_context(
          supi, itti_msg.pdu_session_id, psc)) {
    Logger::amf_n2().warn(
        "Cannot get pdu_session_context with SUPI (%s)", supi.c_str());
    item.s_nssai.sst = "01";  // TODO: get from N1N2msgTranferMsg
    item.s_nssai.sd =
        std::to_string(SD_NO_VALUE);  // TODO: get from N1N2msgTranferMsg
  } else {
    item.s_nssai.sst = std::to_string(psc->snssai.sST);
    item.s_nssai.sd  = psc->snssai.sD;
  }

  Logger::amf_n2().debug(
      "S_NSSAI (SST, SD) %s, %s", item.s_nssai.sst.c_str(),
      item.s_nssai.sd.c_str());

  conv::bstring_2_octet_string(
      itti_msg.n2sm, item.pduSessionResourceSetupRequestTransfer);
  list.push_back(item);
  psrsr->setPduSessionResourceSetupRequestList(list);
  psrsr->setUEAggregateMaxBitRate(
      UE_AGGREGATE_MAXIMUM_BIT_RATE_DL, UE_AGGREGATE_MAXIMUM_BIT_RATE_UL);
  uint8_t* buffer  = (uint8_t*) calloc(1, BUFFER_SIZE_4096);
  int encoded_size = 0;

  psrsr->encode2NewBuffer(buffer, encoded_size);
#if DEBUG_IS_ON
  Logger::amf_n2().debug("N2 SM buffer data: ");
  for (int i = 0; i < encoded_size; i++) printf("%02x ", (char) buffer[i]);
#endif
  Logger::amf_n2().debug(" (%d bytes) \n", encoded_size);

  bstring b = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, unc->sctp_stream_send, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(
    itti_pdu_session_resource_modify_request& itti_msg) {
  Logger::amf_n2().debug("Handle PDU Session Resource Modify Request ...");

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!amf_n2_inst->is_ran_ue_id_2_ue_ngap_context(
          itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        itti_msg.ran_ue_ngap_id);
    return;
  }

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", unc->gnb_assoc_id);
    return;
  }

  std::unique_ptr<PduSessionResourceModifyRequestMsg> modify_request_msg =
      std::make_unique<PduSessionResourceModifyRequestMsg>();

  modify_request_msg->setAmfUeNgapId(itti_msg.amf_ue_ngap_id);
  modify_request_msg->setRanUeNgapId(itti_msg.ran_ue_ngap_id);

  std::vector<PDUSessionResourceModifyRequestItem_t> list;
  PDUSessionResourceModifyRequestItem_t item = {};
  item.pduSessionId                          = itti_msg.pdu_session_id;

  conv::bstring_2_octet_string(
      itti_msg.n2sm, item.pduSessionResourceModifyRequestTransfer);
  S_Nssai tmp  = {};
  tmp.sd       = itti_msg.s_NSSAI.getSd();
  tmp.sst      = itti_msg.s_NSSAI.getSst();
  item.s_nssai = std::optional<S_Nssai>(tmp);

  item.nas_pdu = bstrcpy(itti_msg.nas);
  list.push_back(item);

  modify_request_msg->setPduSessionResourceModifyRequestList(list);

  uint8_t* buffer  = (uint8_t*) calloc(1, BUFFER_SIZE_4096);
  int encoded_size = 0;
  modify_request_msg->encode2NewBuffer(buffer, encoded_size);
#if DEBUG_IS_ON
  Logger::amf_n2().debug("N2 SM buffer data: ");
  for (int i = 0; i < encoded_size; i++) printf("%02x ", (char) buffer[i]);
#endif
  Logger::amf_n2().debug(" (%d bytes) \n", encoded_size);

  bstring b = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, unc->sctp_stream_send, &b);
  // free memory
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(
    itti_pdu_session_resource_release_command& itti_msg) {
  Logger::amf_n2().debug("Handle PDU Session Resource Release Command ...");

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!amf_n2_inst->is_ran_ue_id_2_ue_ngap_context(
          itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        itti_msg.ran_ue_ngap_id);
    return;
  }

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", unc->gnb_assoc_id);
    return;
  }

  std::unique_ptr<PduSessionResourceReleaseCommandMsg> release_cmd_msg =
      std::make_unique<PduSessionResourceReleaseCommandMsg>();

  release_cmd_msg->setAmfUeNgapId(itti_msg.amf_ue_ngap_id);
  release_cmd_msg->setRanUeNgapId(itti_msg.ran_ue_ngap_id);
  release_cmd_msg->setNasPdu(itti_msg.nas);

  std::vector<PDUSessionResourceToReleaseItem_t> list;
  PDUSessionResourceToReleaseItem_t item = {};
  item.pduSessionId                      = itti_msg.pdu_session_id;

  conv::bstring_2_octet_string(
      itti_msg.n2sm, item.pduSessionResourceReleaseCommandTransfer);
  list.push_back(item);
  release_cmd_msg->setPduSessionResourceToReleaseList(list);

  uint8_t* buffer  = (uint8_t*) calloc(1, BUFFER_SIZE_4096);
  int encoded_size = 0;
  release_cmd_msg->encode2NewBuffer(buffer, encoded_size);
#if DEBUG_IS_ON
  Logger::amf_n2().debug("N2 SM buffer data: ");
  for (int i = 0; i < encoded_size; i++) printf("%02x ", (char) buffer[i]);
#endif
  Logger::amf_n2().debug(" (%d bytes) \n", encoded_size);

  bstring b = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, unc->sctp_stream_send, &b);
  // free memory
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_ue_context_release_request& itti_msg) {
  Logger::amf_n2().debug("Handle UE Context Release Request ...");

  unsigned long amf_ue_ngap_id   = itti_msg.ueCtxRel->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id        = itti_msg.ueCtxRel->getRanUeNgapId();
  e_Ngap_CauseRadioNetwork cause = {};
  itti_msg.ueCtxRel->getCauseRadioNetwork(cause);

  std::unique_ptr<UEContextReleaseCommandMsg> ueCtxRelCmd =
      std::make_unique<UEContextReleaseCommandMsg>();
  ueCtxRelCmd->setUeNgapIdPair(amf_ue_ngap_id, ran_ue_ngap_id);
  ueCtxRelCmd->setCauseRadioNetwork(cause);

  uint8_t buffer[BUFFER_SIZE_512];
  int encoded_size = ueCtxRelCmd->encode2Buffer(buffer, BUFFER_SIZE_512);
  bstring b        = blk2bstr(buffer, encoded_size);

  sctp_s_38412.sctp_send_msg(itti_msg.assoc_id, itti_msg.stream, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_ue_context_release_command& itti_msg) {
  Logger::amf_n2().debug("Handling UE Context Release Command ...");

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!amf_n2_inst->is_ran_ue_id_2_ue_ngap_context(
          itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        itti_msg.ran_ue_ngap_id);
    return;
  }

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existing gNG context with assoc_id (%d)", unc->gnb_assoc_id);
    return;
  }

  std::unique_ptr<UEContextReleaseCommandMsg> ueCtxRelCmd =
      std::make_unique<UEContextReleaseCommandMsg>();
  ueCtxRelCmd->setUeNgapIdPair(
      itti_msg.amf_ue_ngap_id, itti_msg.ran_ue_ngap_id);

  if (itti_msg.cause.getChoiceOfCause() == Ngap_Cause_PR_nas) {
    ueCtxRelCmd->setCauseNas((e_Ngap_CauseNas) itti_msg.cause.getValue());
  }

  if (itti_msg.cause.getChoiceOfCause() == Ngap_Cause_PR_radioNetwork) {
    ueCtxRelCmd->setCauseRadioNetwork(
        (e_Ngap_CauseRadioNetwork) itti_msg.cause.getValue());
  }

  uint8_t buffer[BUFFER_SIZE_256];
  int encoded_size = ueCtxRelCmd->encode2Buffer(buffer, BUFFER_SIZE_256);

  bstring b = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(gc->sctp_assoc_id, unc->sctp_stream_send, &b);
  bdestroy_wrapper(&b);

  // Send ITTI to N11 SBI, notify CommunicationFailure Report, RAN Cause
  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(itti_msg.amf_ue_ngap_id, nc)) {
    Logger::amf_n2().warn(
        "Could not notify RAN caused CommunicationFailure."
        "No existing nas_context with amf_ue_ngap_id(" AMF_UE_NGAP_ID_FMT ")",
        itti_msg.amf_ue_ngap_id);
    return;
  }
  string supi = "imsi-" + nc->imsi;

  Logger::amf_n2().debug(
      "Send request to SBI to trigger UE Communication Failure Report (SUPI "
      "%s )",
      supi.c_str());
  std::vector<std::shared_ptr<amf_subscription>> subscriptions = {};
  amf_app_inst->get_ee_subscriptions(
      amf_event_type_t::COMMUNICATION_FAILURE_REPORT, subscriptions);

  if (subscriptions.size() > 0) {
    // Send request to SBI to trigger the notification to the subscribed event
    Logger::amf_n1().debug(
        "Send ITTI msg to AMF SBI to trigger the event notification");

    std::shared_ptr<itti_sbi_notify_subscribed_event> itti_msg_ev =
        std::make_shared<itti_sbi_notify_subscribed_event>(
            TASK_AMF_N2, TASK_AMF_SBI);

    itti_msg_ev->http_version = 1;

    for (auto i : subscriptions) {
      // Avoid repeated notifications
      // TODO: use the anyUE field from the subscription request
      if (i->supi_is_set && std::strcmp(i->supi.c_str(), supi.c_str()))
        continue;

      event_notification ev_notif = {};
      ev_notif.set_notify_correlation_id(i->notify_correlation_id);
      ev_notif.set_notify_uri(i->notify_uri);  // Direct subscription
      // ev_notif.set_subs_change_notify_correlation_id(i->notify_uri);

      oai::amf::model::AmfEventReport event_report = {};
      oai::amf::model::AmfEventType amf_event_type = {};
      amf_event_type.set_value("COMMUNICATION_FAILURE_REPORT");
      event_report.setType(amf_event_type);

      oai::amf::model::AmfEventState amf_event_state = {};
      amf_event_state.setActive(true);
      event_report.setState(amf_event_state);

      oai::amf::model::CommunicationFailure comm_failure = {};

      NgApCause ngap_cause = {};
      ngap_cause.setGroup(itti_msg.cause.getChoiceOfCause());
      ngap_cause.setValue(itti_msg.cause.getValue());
      comm_failure.setRanReleaseCode(ngap_cause);

      event_report.setCommFailure(comm_failure);

      event_report.setSupi(supi);
      ev_notif.add_report(event_report);

      itti_msg_ev->event_notifs.push_back(ev_notif);
    }

    int ret = itti_inst->send_msg(itti_msg_ev);
    if (0 != ret) {
      Logger::amf_n2().error(
          "Could not send ITTI message %s to task TASK_AMF_SBI",
          itti_msg_ev->get_msg_name());
    }
  }
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_ue_context_release_complete& itti_msg) {
  Logger::amf_n2().debug("Handle UE Context Release Complete ...");
  unsigned long amf_ue_ngap_id = itti_msg.ueCtxRelCmpl->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id      = itti_msg.ueCtxRelCmpl->getRanUeNgapId();

  // Change UE status from CM-CONNECTED to CM-IDLE
  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(amf_ue_ngap_id, nc)) {
    Logger::amf_n2().warn(
        "No existed nas_context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
  }
  if (nc != nullptr) {
    amf_n1_inst->set_5gcm_state(nc, CM_IDLE);

    // Start/reset the Mobile Reachable Timer
    timer_id_t tid = itti_inst->timer_setup(
        MOBILE_REACHABLE_TIMER_NO_EMERGENCY_SERVICES_MIN * 60, 0, TASK_AMF_N1,
        TASK_AMF_MOBILE_REACHABLE_TIMER_EXPIRE, amf_ue_ngap_id);
    Logger::amf_n2().startup("Started mobile reachable timer (tid %d)", tid);

    amf_n1_inst->set_mobile_reachable_timer(nc, tid);
    amf_n1_inst->set_mobile_reachable_timer_timeout(nc, false);
  } else {
    return;
  }

  // TODO: User Location Information IE
  // TODO: Information on Recommended Cells & RAN Nodes for Paging IE

  // TODO: Process Secondary RAT Usage Information IE if available

  // Get PDU Sessions in UE Context Release Complete and send
  // Nsmf_PDUSession_UpdateSMContext to SMF
  std::vector<PDUSessionResourceCxtRelCplItem_t> pdu_sessions_to_be_released;
  itti_msg.ueCtxRelCmpl->getPduSessionResourceCxtRelCplList(
      pdu_sessions_to_be_released);

  // TODO: may consider releasing all exisiting PDU sessions
  /*
  if (pdu_sessions_to_be_released.size() == 0) {
    string supi = "imsi-" + nc->imsi;
    std::vector<std::shared_ptr<pdu_session_context>> sessions_ctx;
    if (!amf_app_inst->get_pdu_sessions_context(supi, sessions_ctx)) {
      Logger::amf_n2().debug("No PDU Session Context found");
      return;
    } else {
      for (auto pdu_session : sessions_ctx) {
        PDUSessionResourceCxtRelCplItem_t item = {};
        item.pduSessionId = pdu_session->pdu_session_id;
        pdu_sessions_to_be_released.push_back(item);
      }
    }
  }
*/
  // Send PDUSessionUpdateSMContextRequest to SMF for each PDU session
  std::map<uint32_t, boost::shared_future<std::string>> curl_responses;

  for (auto pdu_session : pdu_sessions_to_be_released) {
    // Generate a promise and associate this promise to the curl handle
    uint32_t promise_id = amf_app_inst->generate_promise_id();
    Logger::amf_n2().debug("Promise ID generated %d", promise_id);

    boost::shared_ptr<boost::promise<std::string>> p =
        boost::make_shared<boost::promise<std::string>>();
    boost::shared_future<std::string> f = p->get_future();
    amf_app_inst->add_promise(promise_id, p);

    curl_responses.emplace(pdu_session.pduSessionId, f);

    Logger::amf_n2().debug(
        "Sending ITTI to trigger PDUSessionUpdateSMContextRequest to SMF to "
        "task TASK_AMF_SBI");

    std::shared_ptr<itti_nsmf_pdusession_update_sm_context> itti_n11_msg =
        std::make_shared<itti_nsmf_pdusession_update_sm_context>(
            TASK_NGAP, TASK_AMF_SBI);

    itti_n11_msg->pdu_session_id = pdu_session.pduSessionId;

    // TODO:
    itti_n11_msg->is_n2sm_set = false;

    itti_n11_msg->amf_ue_ngap_id = amf_ue_ngap_id;
    itti_n11_msg->ran_ue_ngap_id = ran_ue_ngap_id;
    itti_n11_msg->promise_id     = promise_id;
    itti_n11_msg->up_cnx_state   = "DEACTIVATED";

    int ret = itti_inst->send_msg(itti_n11_msg);
    if (0 != ret) {
      Logger::ngap().error(
          "Could not send ITTI message %s to task TASK_AMF_SBI",
          itti_n11_msg->get_msg_name());
    }
  }

  bool result = true;
  while (!curl_responses.empty()) {
    boost::future_status status;
    // wait for timeout or ready
    status = curl_responses.begin()->second.wait_for(
        boost::chrono::milliseconds(FUTURE_STATUS_TIMEOUT_MS));
    if (status == boost::future_status::ready) {
      assert(curl_responses.begin()->second.is_ready());
      assert(curl_responses.begin()->second.has_value());
      assert(!curl_responses.begin()->second.has_exception());
      // Wait for the result from APP and send reply to AMF
      std::string pdu_session_id_str = curl_responses.begin()->second.get();
      Logger::ngap().debug(
          "Got result for PDU Session ID %d", curl_responses.begin()->first);
      if (pdu_session_id_str.size() > 0) {
        result = result && true;
      } else {
        result = false;
      }

    } else {
      result = true;
    }
    curl_responses.erase(curl_responses.begin());
  }
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(
    itti_ue_radio_capability_indication& itti_msg) {
  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "No existed gNB context with assoc_id (%d)", itti_msg.assoc_id);
    return;
  }

  unsigned long amf_ue_ngap_id = {0};
  amf_ue_ngap_id               = itti_msg.ueRadioCap->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id      = {0};
  ran_ue_ngap_id               = itti_msg.ueRadioCap->getRanUeNgapId();
  OCTET_STRING_t ue_radio_cap;
  itti_msg.ueRadioCap->getUERadioCapability(ue_radio_cap);
  gc->ue_radio_cap_ind = blk2bstr(ue_radio_cap.buf, ue_radio_cap.size);
}

//------------------------------------------------------------------------------
bool amf_n2::handle_itti_message(itti_handover_required& itti_msg) {
  Logger::amf_n2().debug("Handling Handover Required ...");
  unsigned long amf_ue_ngap_id = itti_msg.handoverReq->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id      = itti_msg.handoverReq->getRanUeNgapId();

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "gNB with assoc_id (%d) is illegal", itti_msg.assoc_id);
    return false;
  }

  Logger::amf_n2().debug(
      "Handover Required, gNB info (gNB Name %s, globalRanNodeId 0x%x)",
      gc->gnb_name.c_str(), gc->globalRanNodeId);

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!is_ran_ue_id_2_ue_ngap_context(ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        ran_ue_ngap_id);
    return false;
  }

  if (unc->amf_ue_ngap_id != amf_ue_ngap_id) {
    Logger::amf_n2().error(
        "The requested UE (amf_ue_ngap_id " AMF_UE_NGAP_ID_FMT
        ") is not valid, existed UE "
        "with  amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id, unc->amf_ue_ngap_id);
    return false;
  }

  if (itti_msg.handoverReq->getHandoverType() != Ngap_HandoverType_intra5gs) {
    Logger::amf_n2().error("Handover Type is not supported");
    return false;
  }

  Logger::amf_n2().debug(
      "Handover Required, Choice of Cause %d, Cause %ld",
      (int) itti_msg.handoverReq->getChoiceOfCause(),
      itti_msg.handoverReq->getCauseValue());
  long direct_forward_path_availability = {};
  if (itti_msg.handoverReq->getDirectForwardingPathAvailability(
          direct_forward_path_availability))
    Logger::amf_n2().debug(
        "Handover Required, DirectForwardingPathAvailability %ld",
        direct_forward_path_availability);

  unc->gnb_assoc_id = itti_msg.assoc_id;
  unc->ncc++;
  unc->ng_ue_state = NGAP_UE_HANDOVER;

  GlobalgNBId target_global_gnb_id = {};
  TAI tai                          = {};
  itti_msg.handoverReq->getTargetID(target_global_gnb_id, tai);
  ngap::PlmnId plmn = {};
  GNB_ID gnbid      = {};
  target_global_gnb_id.get(plmn, gnbid);
  std::string mcc = {};
  std::string mnc = {};
  plmn.getMcc(mcc);
  plmn.getMnc(mnc);
  uint32_t gnb_id_value = {0};
  gnbid.get(gnb_id_value);

  Logger::amf_n2().debug(
      "Handover Required, Target ID GlobalRanNodeID PLMN (MCC %s, MNC %s, "
      "gNBId 0x%x)",
      mcc.c_str(), mnc.c_str(), gnb_id_value);

  string mcc_select_tai = {};
  string mnc_select_tai = {};
  uint32_t tac          = {};

  tai.getTAI(mcc_select_tai, mnc_select_tai, tac);
  Logger::amf_n2().debug(
      "Handover Required: Target ID selected TAI PLMN (MCC %s, MNC %s, TAC %x)",
      mcc_select_tai.c_str(), mnc_select_tai.c_str(), tac);

  OCTET_STRING_t source_to_target =
      itti_msg.handoverReq->getSourceToTarget_TransparentContainer();

  // TODO: T-AMF selection, for now use the same AMF

  // Create HandoverRequest message to be sent to target gNB
  std::unique_ptr<HandoverRequest> handover_request =
      std::make_unique<HandoverRequest>();
  handover_request->setAmfUeNgapId(amf_ue_ngap_id);
  handover_request->setHandoverType(0);
  handover_request->setCause(
      Ngap_Cause_PR_radioNetwork,
      Ngap_CauseRadioNetwork_handover_desirable_for_radio_reason);
  handover_request->setUEAggregateMaximumBitRate(
      UE_AGGREGATE_MAXIMUM_BIT_RATE_DL, UE_AGGREGATE_MAXIMUM_BIT_RATE_UL);
  handover_request->setUESecurityCapabilities(
      0xe000, 0xe000, 0xe000, 0xe000);  // TODO: remove hardcoded values

  handover_request->setSourceToTarget_TransparentContainer(source_to_target);

  // Allowed NSSAI
  std::vector<S_NSSAI> allowed_nssai;
  for (int i = 0; i < amf_cfg.plmn_list.size(); i++) {
    for (int j = 0; j < amf_cfg.plmn_list[i].slice_list.size(); j++) {
      S_Nssai s_tmp;
      S_NSSAI s_nssai = {};
      s_nssai.setSst(amf_cfg.plmn_list[i].slice_list[j].sst);
      s_nssai.setSd(amf_cfg.plmn_list[i].slice_list[j].sd);
      allowed_nssai.push_back(s_nssai);
    }
  }
  handover_request->setAllowedNSSAI(allowed_nssai);

  // GUAMI, PLMN
  ngap::PlmnId plmn_id = {};
  plmn_id.set(amf_cfg.guami.mcc, amf_cfg.guami.mnc);

  handover_request->setMobilityRestrictionList(plmn_id);
  handover_request->setGUAMI(
      amf_cfg.guami.mcc, amf_cfg.guami.mnc, amf_cfg.guami.regionID,
      amf_cfg.guami.AmfSetID, amf_cfg.guami.AmfPointer);

  // Security context
  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(amf_ue_ngap_id, nc)) {
    Logger::amf_n2().error(
        "No UE NAS context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return false;
  }

  nas_secu_ctx* secu = nc->security_ctx;
  if (!secu) {
    Logger::amf_n2().error("No Security Context found");
    return false;
  }
  uint8_t* kamf = nc->kamf[secu->vector_pointer];
  uint8_t kgnb[32];
  uint32_t ulcount = secu->ul_count.seq_num | (secu->ul_count.overflow << 8);
  Logger::amf_n2().debug(
      "Handover Required, Uplink count (%d)", secu->ul_count.seq_num);
  uint8_t knh[32];
  Authentication_5gaka::handover_ncc_derive_knh(
      ulcount, 0x01, kamf, kgnb, knh, unc->ncc);
  bstring knh_bs = blk2bstr(knh, 32);
  handover_request->setSecurityContext(unc->ncc /*NCC count*/, knh_bs);

  string supi = "imsi-" + nc->imsi;
  Logger::amf_n2().debug(
      "Received Handover Required for UE (SUPI %s)", supi.c_str());

  PDUSessionResourceListHORqd pDUSessionResourceListHORqd = {};
  std::vector<PDUSessionResourceItem_t> pdu_session_resource_list;
  if (!itti_msg.handoverReq->getPDUSessionResourceList(
          pDUSessionResourceListHORqd)) {
    Logger::ngap().warn(
        "Decoding PDU Session Resource List IE error or IE missing");
  }

  std::vector<PDUSessionResourceItem> item_ho_required_list;
  pDUSessionResourceListHORqd.get(item_ho_required_list);

  std::map<uint8_t, boost::shared_future<std::string>> curl_responses;

  // Send PDUSessionUpdateSMContextRequest to SMF for all PDU sessions included
  // in HO Required message
  for (auto& item : item_ho_required_list) {
    PDUSessionID pdu_session_id               = {};
    OCTET_STRING_t handover_required_transfer = {};
    item.get(pdu_session_id, handover_required_transfer);
    uint8_t pdu_session_id_value = 0;
    pdu_session_id.get(pdu_session_id_value);

    Logger::ngap().debug("PDU Session ID %d", pdu_session_id_value);
    std::shared_ptr<pdu_session_context> psc = {};
    if (amf_app_inst->find_pdu_session_context(
            supi, pdu_session_id_value, psc)) {
      // Generate a promise and associate this promise to the curl handle
      uint32_t promise_id = amf_app_inst->generate_promise_id();
      Logger::amf_n2().debug("Promise ID generated %d", promise_id);
      boost::shared_ptr<boost::promise<std::string>> p =
          boost::make_shared<boost::promise<std::string>>();
      boost::shared_future<std::string> f = p->get_future();
      amf_app_inst->add_promise(promise_id, p);

      // Store the future to be processed later
      curl_responses.emplace(psc->pdu_session_id, f);

      Logger::amf_n2().debug(
          "Sending ITTI to trigger PDUSessionUpdateSMContextRequest to SMF to "
          "task TASK_AMF_SBI");
      std::shared_ptr<itti_nsmf_pdusession_update_sm_context> itti_msg =
          std::make_shared<itti_nsmf_pdusession_update_sm_context>(
              TASK_NGAP, TASK_AMF_SBI);

      itti_msg->pdu_session_id = pdu_session_id_value;
      itti_msg->n2sm           = blk2bstr(
          handover_required_transfer.buf, handover_required_transfer.size);
      itti_msg->is_n2sm_set    = true;
      itti_msg->n2sm_info_type = "HANDOVER_REQUIRED";
      itti_msg->ho_state       = "PREPARING";
      itti_msg->amf_ue_ngap_id = amf_ue_ngap_id;
      itti_msg->ran_ue_ngap_id = ran_ue_ngap_id;
      itti_msg->promise_id     = promise_id;

      int ret = itti_inst->send_msg(itti_msg);
      if (0 != ret) {
        Logger::ngap().error(
            "Could not send ITTI message %s to task TASK_AMF_SBI",
            itti_msg->get_msg_name());
      }
    }
  }

  // TODO: Handover Response supervision
  // Wait until receiving all responses from SMFs before sending Handover
  std::vector<PDUSessionResourceSetupRequestItem_t> list;

  bool result = true;
  while (!curl_responses.empty()) {
    boost::future_status status;
    // wait for timeout or ready
    status = curl_responses.begin()->second.wait_for(
        boost::chrono::milliseconds(FUTURE_STATUS_TIMEOUT_MS));
    if (status == boost::future_status::ready) {
      assert(curl_responses.begin()->second.is_ready());
      assert(curl_responses.begin()->second.has_value());
      assert(!curl_responses.begin()->second.has_exception());
      // Wait for the result from APP and send reply to AMF
      std::string n2_sm = curl_responses.begin()->second.get();
      Logger::ngap().debug(
          "Got result for PDU Session ID %d", curl_responses.begin()->first);
      if (n2_sm.size() > 0) {
        result = result && true;

        std::shared_ptr<pdu_session_context> psc = {};
        if (amf_app_inst->find_pdu_session_context(
                supi, curl_responses.begin()->first, psc)) {
          PDUSessionResourceSetupRequestItem_t item = {};
          item.pduSessionId                         = psc->pdu_session_id;
          item.s_nssai.sst = std::to_string(psc->snssai.sST);
          item.s_nssai.sd  = psc->snssai.sD;
          // item.pduSessionNAS_PDU = nullptr;
          unsigned int data_len = n2_sm.length();
          item.pduSessionResourceSetupRequestTransfer.buf =
              (unsigned char*) malloc(data_len + 1);
          memcpy(
              (void*) item.pduSessionResourceSetupRequestTransfer.buf,
              (void*) n2_sm.c_str(), data_len);
          item.pduSessionResourceSetupRequestTransfer.size = data_len;
          list.push_back(item);
        }
      } else {
        result = false;
      }
    } else {
      result = true;
    }
    curl_responses.erase(curl_responses.begin());
  }
  // TODO: process result

  // Request to Target RAN
  handover_request->setPduSessionResourceSetupList(list);

  uint8_t buffer[BUFFER_SIZE_4096];
  int encoded_size = handover_request->encode2Buffer(buffer, BUFFER_SIZE_4096);
  bstring b        = blk2bstr(buffer, encoded_size);
  std::shared_ptr<gnb_context> gc_target = {};
  gc_target                              = gnb_id_2_gnb_context(gnb_id_value);
  unc->target_gnb_assoc_id               = gc_target->sctp_assoc_id;
  sctp_s_38412.sctp_send_msg(gc_target->sctp_assoc_id, 0, &b);
  bdestroy_wrapper(&b);
  return true;
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_handover_request_Ack& itti_msg) {
  Logger::amf_n2().debug("Handling Handover Request Ack ...");
  unsigned long amf_ue_ngap_id = itti_msg.handoverrequestAck->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id      = itti_msg.handoverrequestAck->getRanUeNgapId();
  Logger::amf_n2().debug(
      "Handover Request Ack ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT
      ") amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
      ran_ue_ngap_id, amf_ue_ngap_id);

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "gNB with assoc_id (%d) is illegal", itti_msg.assoc_id);
    return;
  }

  Logger::amf_n2().debug(
      "Handover Request Ack, gNB info (gNB Name %s, globalRanNodeId 0x%x)",
      gc->gnb_name.c_str(), gc->globalRanNodeId);

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!is_amf_ue_id_2_ue_ngap_context(amf_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return;
  }

  unc->target_ran_ue_ngap_id = ran_ue_ngap_id;  // store target RAN ID

  std::vector<PDUSessionResourceAdmittedItem_t> list;
  if (!itti_msg.handoverrequestAck->getPDUSessionResourceAdmittedList(list)) {
    Logger::ngap().error(
        "Decoding HandoverRequestACK getPDUSessionResourceList IE error");
    return;
  }

  OCTET_STRING_t targetTosource =
      itti_msg.handoverrequestAck->getTargetToSource_TransparentContainer();

  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(amf_ue_ngap_id, nc)) {
    Logger::amf_n2().error(
        "No UE NAS context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return;
  }

  string supi = "imsi-" + nc->imsi;

  // Send PDUSessionUpdateSMContextRequest to SMF for all associated PDU
  // sessions
  std::map<uint8_t, boost::shared_future<std::string>> curl_responses;

  for (auto pdu_session_resource : list) {
    // Generate a promise and associate this promise to the curl handle
    uint32_t promise_id = amf_app_inst->generate_promise_id();
    Logger::amf_n2().debug("Promise ID generated %d", promise_id);

    boost::shared_ptr<boost::promise<std::string>> p =
        boost::make_shared<boost::promise<std::string>>();
    boost::shared_future<std::string> f = p->get_future();
    amf_app_inst->add_promise(promise_id, p);

    curl_responses.emplace(pdu_session_resource.pduSessionId, f);

    Logger::amf_n2().debug(
        "Sending ITTI to trigger PDUSessionUpdateSMContextRequest to SMF to "
        "task TASK_AMF_SBI");
    std::shared_ptr<itti_nsmf_pdusession_update_sm_context> itti_msg =
        std::make_shared<itti_nsmf_pdusession_update_sm_context>(
            TASK_NGAP, TASK_AMF_SBI);

    itti_msg->pdu_session_id = pdu_session_resource.pduSessionId;
    itti_msg->n2sm           = blk2bstr(
        pdu_session_resource.handoverRequestAcknowledgeTransfer.buf,
        pdu_session_resource.handoverRequestAcknowledgeTransfer.size);
    itti_msg->is_n2sm_set    = true;
    itti_msg->n2sm_info_type = "HANDOVER_REQ_ACK";
    itti_msg->ho_state       = "PREPARED";
    itti_msg->amf_ue_ngap_id = amf_ue_ngap_id;
    itti_msg->ran_ue_ngap_id = ran_ue_ngap_id;
    itti_msg->promise_id     = promise_id;

    int ret = itti_inst->send_msg(itti_msg);
    if (0 != ret) {
      Logger::ngap().error(
          "Could not send ITTI message %s to task TASK_AMF_SBI",
          itti_msg->get_msg_name());
    }
  }

  // Send HandoverCommandMsg to Source gNB
  std::unique_ptr<HandoverCommandMsg> handovercommand =
      std::make_unique<HandoverCommandMsg>();
  handovercommand->setAmfUeNgapId(amf_ue_ngap_id);
  handovercommand->setRanUeNgapId(unc->ran_ue_ngap_id);
  handovercommand->setHandoverType(Ngap_HandoverType_intra5gs);

  PDUSessionResourceHandoverList handoverList = {};
  std::vector<PDUSessionResourceItem> handoverItemList;
  PDUSessionResourceItem handoverItem = {};

  // TODO: wait for response from SMF and transfer T-RAN N3 information/ or
  // T-UPF to the source gNB
  bool result = true;
  while (!curl_responses.empty()) {
    boost::future_status status;
    // wait for timeout or ready
    status = curl_responses.begin()->second.wait_for(
        boost::chrono::milliseconds(FUTURE_STATUS_TIMEOUT_MS));
    if (status == boost::future_status::ready) {
      assert(curl_responses.begin()->second.is_ready());
      assert(curl_responses.begin()->second.has_value());
      assert(!curl_responses.begin()->second.has_exception());
      // Wait for the result from APP and send reply to AMF
      std::string n2_sm = curl_responses.begin()->second.get();
      Logger::ngap().debug(
          "Got result for PDU Session ID %d", curl_responses.begin()->first);
      if (n2_sm.size() > 0) {
        result                                 = result && true;
        uint8_t pdu_session_id_value           = curl_responses.begin()->first;
        unsigned int data_len                  = n2_sm.length();
        PDUSessionID pdu_session_id            = {};
        OCTET_STRING_t handoverCommandTransfer = {};
        pdu_session_id.set(pdu_session_id_value);
        OCTET_STRING_fromBuf(
            &handoverCommandTransfer, n2_sm.c_str(), n2_sm.length());
        handoverItem.set(pdu_session_id, handoverCommandTransfer);
        handoverItemList.push_back(handoverItem);
        handoverList.set(handoverItemList);

        std::shared_ptr<pdu_session_context> psc = {};
        if (amf_app_inst->find_pdu_session_context(
                supi, pdu_session_id_value, psc)) {
          psc->is_ho_accepted = true;
        }
      } else {
        result = false;
      }
    } else {
      result = true;
    }
    curl_responses.erase(curl_responses.begin());
  }

  handovercommand->setPduSessionResourceHandoverList(handoverList);
  handovercommand->setTargetToSource_TransparentContainer(targetTosource);

  uint8_t buffer[BUFFER_SIZE_1024];
  int encoded_size = handovercommand->encode2Buffer(buffer, BUFFER_SIZE_1024);
  bstring b        = blk2bstr(buffer, encoded_size);
  sctp_s_38412.sctp_send_msg(unc->gnb_assoc_id, 0, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_handover_notify& itti_msg) {
  Logger::amf_n2().info("Handle Handover Notify ...");
  unsigned long amf_ue_ngap_id = itti_msg.handovernotify->getAmfUeNgapId();
  uint32_t ran_ue_ngap_id      = itti_msg.handovernotify->getRanUeNgapId();
  Logger::amf_n2().debug(
      "Handover Notify ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT
      ") amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
      ran_ue_ngap_id, amf_ue_ngap_id);

  std::shared_ptr<gnb_context> gc = {};
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id, gc)) {
    Logger::amf_n2().error(
        "gNB with assoc_id (%d) is illegal", itti_msg.assoc_id);
    return;
  }

  Logger::amf_n2().debug(
      "Handover Notify, gNB info (gNB Name: %s, globalRanNodeId 0x%x)",
      gc->gnb_name.c_str(), gc->globalRanNodeId);

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!is_amf_ue_id_2_ue_ngap_context(amf_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return;
  }

  NrCgi_t NR_CGI = {};
  Tai_t TAI      = {};
  if (!itti_msg.handovernotify->getUserLocationInfoNR(NR_CGI, TAI)) {
    Logger::amf_n2().debug("Missing IE UserLocationInformationNR");
    return;
  }

  std::shared_ptr<nas_context> nc = {};
  if (!amf_n1_inst->is_amf_ue_id_2_nas_context(amf_ue_ngap_id, nc)) {
    Logger::amf_n2().error(
        "No UE NAS context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return;
  }

  string supi = "imsi-" + nc->imsi;

  std::vector<std::shared_ptr<pdu_session_context>> sessions_ctx;

  if (!amf_app_inst->get_pdu_sessions_context(supi, sessions_ctx)) {
    Logger::amf_n2().debug("No PDU Session Context found");
  }

  // Send PDUSessionUpdateSMContextRequest to SMF for accepted PDU sessions
  std::map<uint8_t, boost::shared_future<std::string>> curl_responses;

  for (auto pdu_session : sessions_ctx) {
    if (pdu_session->is_ho_accepted) {
      // Generate a promise and associate this promise to the curl handle
      uint32_t promise_id = amf_app_inst->generate_promise_id();
      Logger::amf_n2().debug("Promise ID generated %d", promise_id);

      boost::shared_ptr<boost::promise<std::string>> p =
          boost::make_shared<boost::promise<std::string>>();
      boost::shared_future<std::string> f = p->get_future();
      amf_app_inst->add_promise(promise_id, p);

      curl_responses.emplace(pdu_session->pdu_session_id, f);

      Logger::amf_n2().debug(
          "Sending ITTI to trigger PDUSessionUpdateSMContextRequest to SMF to "
          "task TASK_AMF_SBI");

      std::shared_ptr<itti_nsmf_pdusession_update_sm_context> itti_n11_msg =
          std::make_shared<itti_nsmf_pdusession_update_sm_context>(
              TASK_NGAP, TASK_AMF_SBI);

      itti_n11_msg->pdu_session_id = pdu_session->pdu_session_id;

      // TODO: Secondary RAT Usage
      // itti_n11_msg->n2sm           = blk2bstr("Secondary RAT Usage", 19);
      // itti_n11_msg->n2sm_info_type = "SECONDARY_RAT_USAGE";
      itti_n11_msg->is_n2sm_set = false;
      itti_n11_msg->ho_state    = "COMPLETED";

      itti_n11_msg->amf_ue_ngap_id = amf_ue_ngap_id;
      itti_n11_msg->ran_ue_ngap_id = ran_ue_ngap_id;
      itti_n11_msg->promise_id     = promise_id;

      int ret = itti_inst->send_msg(itti_n11_msg);
      if (0 != ret) {
        Logger::ngap().error(
            "Could not send ITTI message %s to task TASK_AMF_SBI",
            itti_n11_msg->get_msg_name());
      }
    }
  }

  bool result = true;
  while (!curl_responses.empty()) {
    boost::future_status status;
    // wait for timeout or ready
    status = curl_responses.begin()->second.wait_for(
        boost::chrono::milliseconds(FUTURE_STATUS_TIMEOUT_MS));
    if (status == boost::future_status::ready) {
      assert(curl_responses.begin()->second.is_ready());
      assert(curl_responses.begin()->second.has_value());
      assert(!curl_responses.begin()->second.has_exception());
      // Wait for the result from APP and send reply to AMF
      std::string pdu_session_id_str = curl_responses.begin()->second.get();
      Logger::ngap().debug(
          "Got result for PDU Session ID %d", curl_responses.begin()->first);
      if (pdu_session_id_str.size() > 0) {
        result = result && true;
      } else {
        result = false;
      }
    } else {
      result = true;
    }
    curl_responses.erase(curl_responses.begin());
  }

  // Send UE Release Command to Source gNB
  Logger::ngap().info("Send UE Release Command to source gNB");
  std::unique_ptr<UEContextReleaseCommandMsg> ueContextReleaseCommand =
      std::make_unique<UEContextReleaseCommandMsg>();
  ueContextReleaseCommand->setUeNgapIdPair(amf_ue_ngap_id, unc->ran_ue_ngap_id);
  ueContextReleaseCommand->setCauseRadioNetwork(
      Ngap_CauseRadioNetwork_successful_handover);

  uint8_t buffer[BUFFER_SIZE_1024];
  int encoded_size =
      ueContextReleaseCommand->encode2Buffer(buffer, BUFFER_SIZE_1024);
  bstring b = blk2bstr(buffer, encoded_size);

  sctp_s_38412.sctp_send_msg(unc->gnb_assoc_id, 0, &b);
  bdestroy_wrapper(&b);

  if (!is_amf_ue_id_2_ue_ngap_context(amf_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return;
  }

  unc->ran_ue_ngap_id        = ran_ue_ngap_id;  // store new RAN ID
  unc->target_ran_ue_ngap_id = 0;               // Clear target RAN ID
  unc->ng_ue_state           = NGAP_UE_CONNECTED;
  unc->gnb_assoc_id          = itti_msg.assoc_id;  // update serving gNB
  set_ran_ue_ngap_id_2_ue_ngap_context(ran_ue_ngap_id, unc);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_uplink_ran_status_transfer& itti_msg) {
  Logger::amf_n2().debug("Handling Uplink RAN Status Transfer ...");
  unsigned long amf_ue_ngap_id = itti_msg.uplinkrantransfer->getAmfUeNgapId();
  Logger::amf_n2().debug(
      "Uplink RAN Status Transfer amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
      amf_ue_ngap_id);
  if (!is_assoc_id_2_gnb_context(itti_msg.assoc_id)) {
    Logger::amf_n2().error(
        "gNB with assoc_id (%d) is illegal", itti_msg.assoc_id);
    return;
  }

  std::shared_ptr<ue_ngap_context> unc = {};
  if (!is_amf_ue_id_2_ue_ngap_context(amf_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with amf_ue_ngap_id (" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
    return;
  }

  RANStatusTransferTransparentContainer ran_status_transfer = {};
  itti_msg.uplinkrantransfer->getRANStatusTransfer_TransparentContainer(
      ran_status_transfer);
  dRBSubjectList amf_m_list = {};
  ran_status_transfer.getdRBSubject_list(amf_m_list);
  std::vector<dRBSubjectItem> drb_subject_item_list;
  amf_m_list.getdRBSubjectItem(drb_subject_item_list);
  // TODO: check size

  dRBStatusDL status_dl = {};
  dRBStatusUL status_ul = {};
  Ngap_DRB_ID_t drb_id  = {};
  drb_subject_item_list[0].getdRBSubjectItem(drb_id, status_ul, status_dl);

  dRBStatusUL18 status_ul_18 = {};
  DRBStatusDL18 status_dl_18 = {};
  status_dl.getDRBStatusDL18(status_dl_18);
  status_ul.getdRBStatusUL(status_ul_18);
  COUNTValueForPDCP_SN18 count_value_ul = {};
  COUNTValueForPDCP_SN18 count_value_dl = {};
  status_ul_18.getcountvalue(count_value_ul);
  status_dl_18.getcountvalue(count_value_dl);
  long amf_ul_pdcp     = {0};
  long amf_hfn_ul_pdcp = {0};
  count_value_ul.getvalue(amf_ul_pdcp, amf_hfn_ul_pdcp);
  long amf_dl_pdcp     = {0};
  long amf_hfn_dl_pdcp = {0};
  count_value_dl.getvalue(amf_dl_pdcp, amf_hfn_dl_pdcp);
  long amf_drb_id = {0};
  amf_drb_id      = drb_id;

  std::unique_ptr<DownlinkRANStatusTransfer> dl_ran_status_transfer =
      std::make_unique<DownlinkRANStatusTransfer>();
  dl_ran_status_transfer->setAmfUeNgapId(amf_ue_ngap_id);
  dl_ran_status_transfer->setRanUeNgapId(unc->target_ran_ue_ngap_id);
  dl_ran_status_transfer->setRANStatusTransfer_TransparentContainer(
      amf_drb_id, amf_ul_pdcp, amf_hfn_ul_pdcp, amf_dl_pdcp, amf_hfn_dl_pdcp);
  uint8_t buffer[BUFFER_SIZE_1024];
  int encode_size =
      dl_ran_status_transfer->encode2Buffer(buffer, BUFFER_SIZE_1024);
  bstring b = blk2bstr(buffer, encode_size);
  sctp_s_38412.sctp_send_msg(unc->target_gnb_assoc_id, 0, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::handle_itti_message(itti_rereoute_nas& itti_msg) {
  Logger::amf_n2().debug("Handle Reroute NAS Request message...");

  std::shared_ptr<ue_ngap_context> unc = {};

  if (!is_ran_ue_id_2_ue_ngap_context(itti_msg.ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id " GNB_UE_NGAP_ID_FMT,
        itti_msg.ran_ue_ngap_id);
    return;
  }

  if (unc->amf_ue_ngap_id != itti_msg.amf_ue_ngap_id) {
    Logger::amf_n2().error(
        "AMF UE NGAP ID does not match the expected value (requested "
        "amf_ue_ngap_id " AMF_UE_NGAP_ID_FMT
        ", existed amf_ue_ngap_id " AMF_UE_NGAP_ID_FMT ")",
        itti_msg.amf_ue_ngap_id, unc->amf_ue_ngap_id);
    return;
  }

  RerouteNASRequest reroute_nas_request = {};
  reroute_nas_request.setRanUeNgapId(itti_msg.ran_ue_ngap_id);
  reroute_nas_request.setAmfUeNgapId(itti_msg.amf_ue_ngap_id);
  if (!reroute_nas_request.setAMFSetID(itti_msg.amf_set_id)) return;
  if (unc->initialUEMsg.size > 0)
    reroute_nas_request.setNgapMessage(
        unc->initialUEMsg);  // Include InitialUEMessage

  // TODO: AllowedNSSAI (Optional)

  uint8_t buffer[BUFFER_SIZE_2048];
  int encoded_size =
      reroute_nas_request.encode2Buffer(buffer, BUFFER_SIZE_2048);
  bstring b = blk2bstr(buffer, encoded_size);

  amf_n2_inst->sctp_s_38412.sctp_send_msg(
      unc->gnb_assoc_id, unc->sctp_stream_send, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
void amf_n2::send_handover_preparation_failure(
    const unsigned long amf_ue_ngap_id, const uint32_t ran_ue_ngap_id,
    const sctp_assoc_id_t& gnb_assoc_id) {
  // Create HandoverPreparationFailure message to be sent to target gNB
  std::unique_ptr<HandoverPreparationFailure> ho_preparation_failure_msg =
      std::make_unique<HandoverPreparationFailure>();
  ho_preparation_failure_msg->setAmfUeNgapId(amf_ue_ngap_id);
  ho_preparation_failure_msg->setRanUeNgapId(amf_ue_ngap_id);
  ho_preparation_failure_msg->setCause(Ngap_Cause_PR_NOTHING);

  uint8_t buffer[BUFFER_SIZE_1024];
  int encoded_size =
      ho_preparation_failure_msg->encode2Buffer(buffer, BUFFER_SIZE_1024);
  bstring b = blk2bstr(buffer, encoded_size);

  sctp_s_38412.sctp_send_msg(gnb_assoc_id, 0, &b);
  bdestroy_wrapper(&b);
}

//------------------------------------------------------------------------------
bool amf_n2::is_ran_ue_id_2_ue_ngap_context(
    const uint32_t& ran_ue_ngap_id) const {
  std::shared_lock lock(m_ranid2uecontext);
  if (ranid2uecontext.count(ran_ue_ngap_id) > 0) {
    if (ranid2uecontext.at(ran_ue_ngap_id) != nullptr) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
bool amf_n2::is_ran_ue_id_2_ue_ngap_context(
    const uint32_t& ran_ue_ngap_id,
    std::shared_ptr<ue_ngap_context>& unc) const {
  std::shared_lock lock(m_ranid2uecontext);
  if (ranid2uecontext.count(ran_ue_ngap_id) > 0) {
    unc = ranid2uecontext.at(ran_ue_ngap_id);
    if (unc != nullptr) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
std::shared_ptr<ue_ngap_context> amf_n2::ran_ue_id_2_ue_ngap_context(
    const uint32_t& ran_ue_ngap_id) const {
  std::shared_lock lock(m_ranid2uecontext);
  return ranid2uecontext.at(ran_ue_ngap_id);
}

//------------------------------------------------------------------------------
void amf_n2::set_ran_ue_ngap_id_2_ue_ngap_context(
    const uint32_t& ran_ue_ngap_id,
    const std::shared_ptr<ue_ngap_context>& unc) {
  std::unique_lock lock(m_ranid2uecontext);
  ranid2uecontext[ran_ue_ngap_id] = unc;
}

//------------------------------------------------------------------------------
void amf_n2::remove_ran_ue_ngap_id_2_ngap_context(
    const uint32_t& ran_ue_ngap_id) {
  std::unique_lock lock(m_ranid2uecontext);
  if (ranid2uecontext.count(ran_ue_ngap_id) > 0) {
    ranid2uecontext.erase(ran_ue_ngap_id);
  }
}

//------------------------------------------------------------------------------
void amf_n2::remove_ue_context_with_ran_ue_ngap_id(
    const uint32_t& ran_ue_ngap_id) {
  // Remove NAS context if still available
  std::shared_ptr<ue_ngap_context> unc = {};

  if (!is_ran_ue_id_2_ue_ngap_context(ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        ran_ue_ngap_id);
    return;
  }

  // Remove all NAS context if still exist
  std::shared_ptr<nas_context> nc = {};
  if (amf_n1_inst->is_amf_ue_id_2_nas_context(unc->amf_ue_ngap_id, nc)) {
    // Remove all NAS context
    string supi = "imsi-" + nc->imsi;
    if (nc->is_stacs_available) {
      stacs.update_5gmm_state(nc->imsi, "5GMM-DEREGISTERED");
    }
    // Trigger UE Loss of Connectivity Status Notify
    Logger::amf_n1().debug(
        "Signal the UE Loss of Connectivity Event notification for SUPI %s",
        supi.c_str());
    amf_n1_inst->event_sub.ue_loss_of_connectivity(
        supi, DEREGISTERED, 1, ran_ue_ngap_id, unc->amf_ue_ngap_id);

    amf_n1_inst->remove_imsi_2_nas_context(supi);
    // TODO:  remove_guti_2_nas_context(guti);
    amf_n1_inst->remove_amf_ue_ngap_id_2_nas_context(unc->amf_ue_ngap_id);
    // Update UE status

  } else {
    Logger::amf_n2().warn(
        "No existed nas_context with amf_ue_ngap_id(" AMF_UE_NGAP_ID_FMT ")",
        unc->amf_ue_ngap_id);
  }

  // Remove NGAP context
  remove_amf_ue_ngap_id_2_ue_ngap_context(unc->amf_ue_ngap_id);
  remove_ran_ue_ngap_id_2_ngap_context(ran_ue_ngap_id);
}

//------------------------------------------------------------------------------
void amf_n2::get_ue_ngap_contexts(
    const sctp_assoc_id_t& gnb_assoc_id,
    std::vector<std::shared_ptr<ue_ngap_context>>& ue_contexts) {
  std::shared_lock lock(m_ranid2uecontext);
  for (auto ue : ranid2uecontext) {
    if (ue.second->gnb_assoc_id == gnb_assoc_id)
      ue_contexts.push_back(ue.second);
  }
}

//------------------------------------------------------------------------------
std::shared_ptr<ue_ngap_context> amf_n2::amf_ue_id_2_ue_ngap_context(
    const unsigned long& amf_ue_ngap_id) const {
  std::shared_lock lock(m_amfueid2uecontext);
  return amfueid2uecontext.at(amf_ue_ngap_id);
}

//------------------------------------------------------------------------------
bool amf_n2::is_amf_ue_id_2_ue_ngap_context(
    const unsigned long& amf_ue_ngap_id) const {
  std::shared_lock lock(m_amfueid2uecontext);
  if (amfueid2uecontext.count(amf_ue_ngap_id) > 0) {
    if (amfueid2uecontext.at(amf_ue_ngap_id) != nullptr) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
bool amf_n2::is_amf_ue_id_2_ue_ngap_context(
    const unsigned long& amf_ue_ngap_id,
    std::shared_ptr<ue_ngap_context>& unc) const {
  std::shared_lock lock(m_amfueid2uecontext);
  if (amfueid2uecontext.count(amf_ue_ngap_id) > 0) {
    unc = amfueid2uecontext.at(amf_ue_ngap_id);
    if (unc != nullptr) {
      return true;
    }
  }
  return false;
}

//------------------------------------------------------------------------------
void amf_n2::set_amf_ue_ngap_id_2_ue_ngap_context(
    const unsigned long& amf_ue_ngap_id, std::shared_ptr<ue_ngap_context> unc) {
  std::unique_lock lock(m_amfueid2uecontext);
  amfueid2uecontext[amf_ue_ngap_id] = unc;
}

//------------------------------------------------------------------------------
void amf_n2::remove_amf_ue_ngap_id_2_ue_ngap_context(
    const unsigned long& amf_ue_ngap_id) {
  std::unique_lock lock(m_amfueid2uecontext);
  if (amfueid2uecontext.count(amf_ue_ngap_id) > 0) {
    amfueid2uecontext.erase(amf_ue_ngap_id);
  }
}

//------------------------------------------------------------------------------
void amf_n2::remove_ue_context_with_amf_ue_ngap_id(
    const unsigned long& amf_ue_ngap_id) {
  // Remove all NAS context if still exist
  std::shared_ptr<nas_context> nc = {};
  if (amf_n1_inst->is_amf_ue_id_2_nas_context(amf_ue_ngap_id, nc)) {
    // Remove all NAS context
    string supi = "imsi-" + nc->imsi;
    // Update UE status
    if (nc->is_stacs_available) {
      stacs.update_5gmm_state(nc->imsi, "5GMM-DEREGISTERED");
    }
    // Trigger UE Loss of Connectivity Status Notify
    Logger::amf_n1().debug(
        "Signal the UE Loss of Connectivity Event notification for SUPI %s",
        supi.c_str());
    amf_n1_inst->event_sub.ue_loss_of_connectivity(
        supi, DEREGISTERED, 1, nc->ran_ue_ngap_id, amf_ue_ngap_id);

    amf_n1_inst->remove_imsi_2_nas_context(supi);
    // TODO:  remove_guti_2_nas_context(guti);
    amf_n1_inst->remove_amf_ue_ngap_id_2_nas_context(amf_ue_ngap_id);
    // Remove NGAP context related to RAN UE NGAP ID
    remove_ran_ue_ngap_id_2_ngap_context(nc->ran_ue_ngap_id);

  } else {
    Logger::amf_n2().warn(
        "No existed nas_context with amf_ue_ngap_id(" AMF_UE_NGAP_ID_FMT ")",
        amf_ue_ngap_id);
  }
  // Remove NGAP context
  remove_amf_ue_ngap_id_2_ue_ngap_context(amf_ue_ngap_id);
}

//------------------------------------------------------------------------------
bool amf_n2::get_common_plmn(
    const std::vector<SupportedTaItem_t>& list,
    std::vector<SupportedTaItem_t>& result) {
  std::vector<SupportedTaItem_t> plmn_list = {};
  bool found_common_plmn                   = false;
  for (int i = 0; i < amf_cfg.plmn_list.size(); i++) {
    for (int j = 0; j < list.size(); j++) {
      Logger::amf_n2().debug(
          "TAC configured %d, TAC received %d", amf_cfg.plmn_list[i].tac,
          list[j].tac);
      if (amf_cfg.plmn_list[i].tac != list[j].tac) {
        continue;
      }
      for (int k = 0; k < list[j].b_plmn_list.size(); k++) {
        if (!(list[j].b_plmn_list[k].mcc.compare(amf_cfg.plmn_list[i].mcc)) &&
            !(list[j].b_plmn_list[k].mnc.compare(amf_cfg.plmn_list[i].mnc))) {
          Logger::amf_n2().debug(
              "Common PLMN MCC %s, MNC %s", amf_cfg.plmn_list[i].mcc.c_str(),
              amf_cfg.plmn_list[i].mnc.c_str());
          // Get the common S-NSSAI
          SupportedTaItem_t item                     = {};
          PlmnSliceSupport_t plmn_slice_support_item = {};
          item.tac                                   = list[j].tac;
          plmn_slice_support_item.mcc = list[j].b_plmn_list[k].mcc;
          plmn_slice_support_item.mnc = list[j].b_plmn_list[k].mnc;

          for (auto s1 : list[j].b_plmn_list[k].slice_list) {
            Logger::amf_n2().debug(
                "S-NSSAI from gNB (SST %s, SD %s)", s1.sst.c_str(),
                s1.sd.c_str());
            for (auto s2 : amf_cfg.plmn_list[i].slice_list) {
              Logger::amf_n2().debug(
                  "S-NSSAI from AMF (SST %d, SD %s)", s2.sst,
                  std::to_string(s2.sd).c_str());
              if (s1.sst.compare(std::to_string(s2.sst)) == 0) {
                uint32_t s1_sd = SD_NO_VALUE;
                conv::sd_string_to_int(s1.sd, s1_sd);
                if (s1_sd == s2.sd) {
                  Logger::amf_n2().debug(
                      "Common S-NSSAI (SST %s, SD %s)", s1.sst.c_str(),
                      s1.sd.c_str());
                  plmn_slice_support_item.slice_list.push_back(s1);
                  found_common_plmn = true;
                }
              }
            }
          }

          item.b_plmn_list.push_back(plmn_slice_support_item);
          result.push_back(item);
        }
      }
    }
  }
  return found_common_plmn;
}

//------------------------------------------------------------------------------
bool amf_n2::get_common_NSSAI(
    const uint32_t& ran_ue_ngap_id, std::vector<nas::SNSSAI_t>& common_nssai) {
  Logger::amf_n2().debug("Getting common S-NSSAIs between gNB and AMF");
  bool found = false;
  // Get UE NGAP Context
  std::shared_ptr<ue_ngap_context> unc = {};

  if (!is_ran_ue_id_2_ue_ngap_context(ran_ue_ngap_id, unc)) {
    Logger::amf_n2().error(
        "No UE NGAP context with ran_ue_ngap_id (" GNB_UE_NGAP_ID_FMT ")",
        ran_ue_ngap_id);
    return false;
  }

  if (!unc) return false;

  // Get gNB Context
  std::shared_ptr<gnb_context> gc = {};
  if (!amf_n2_inst->is_assoc_id_2_gnb_context(unc->gnb_assoc_id, gc)) {
    Logger::amf_n1().error(
        "No existed gNB context with assoc_id (%d)", unc->gnb_assoc_id);
    return false;
  }

  for (const auto& ta : gc->s_ta_list) {
    for (const auto& plmn : ta.b_plmn_list) {
      for (const auto& slice : plmn.slice_list) {
        nas::SNSSAI_t snssai = {};
        uint32_t sd          = SD_NO_VALUE;
        try {
          snssai.sst = std::stoi(slice.sst);
          conv::sd_string_to_int(slice.sd, sd);
        } catch (const std::exception& err) {
          Logger::amf_app().error("Invalid SST/SD");
          break;
        }
        snssai.sd = sd;
        common_nssai.push_back(snssai);
        found = true;
      }
    }
  }
  Logger::amf_n2().debug("Getting common S-NSSAIs between gNB and AMF");

  for (auto s : common_nssai) {
    Logger::amf_n2().debug(
        "Common S-NSSAI (SST %s, SD %s)", std::to_string(s.sst).c_str(),
        std::to_string(s.sd).c_str());
  }

  return found;
}
