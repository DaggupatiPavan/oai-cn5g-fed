
################################################################################
# Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The OpenAirInterface Software Alliance licenses this file to You under
# the OAI Public License, Version 1.1  (the "License"); you may not use this file
# except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.openairinterface.org/?page_id=698
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------------------------------------
# For more information about the OpenAirInterface (OAI) Software Alliance:
#      contact@openairinterface.org
################################################################################

## This file is used to specify the common models and utils this library is using
## DO NOT JUST COPY THIS FILE FROM OTHER NFs. The reasoning behind this is to only compile used files to optimize
## build speed

SET(COMMON_MODELS_DIR ${SRC_TOP_DIR}/common/model/common)

if (TARGET PCF AND TARGET PCF_API)
target_include_directories(PCF PUBLIC ${COMMON_MODELS_DIR})
target_include_directories(PCF_API PUBLIC ${COMMON_MODELS_DIR})

target_sources(PCF PRIVATE
        ${COMMON_MODELS_DIR}/Ecgi.cpp
        ${COMMON_MODELS_DIR}/EutraLocation.cpp
        ${COMMON_MODELS_DIR}/GlobalRanNodeId.cpp
        ${COMMON_MODELS_DIR}/GNbId.cpp
        ${COMMON_MODELS_DIR}/HfcNodeId.cpp
        ${COMMON_MODELS_DIR}/InvalidParam.cpp
        ${COMMON_MODELS_DIR}/N3gaLocation.cpp
        ${COMMON_MODELS_DIR}/Ncgi.cpp
        ${COMMON_MODELS_DIR}/NrLocation.cpp
        ${COMMON_MODELS_DIR}/PlmnId.cpp
        ${COMMON_MODELS_DIR}/PreemptionCapability_anyOf.cpp
        ${COMMON_MODELS_DIR}/PreemptionCapability.cpp
        ${COMMON_MODELS_DIR}/PreemptionVulnerability_anyOf.cpp
        ${COMMON_MODELS_DIR}/PreemptionVulnerability.cpp
        ${COMMON_MODELS_DIR}/PresenceState_anyOf.cpp
        ${COMMON_MODELS_DIR}/PresenceState.cpp
        ${COMMON_MODELS_DIR}/QosResourceType_anyOf.cpp
        ${COMMON_MODELS_DIR}/RatType_anyOf.cpp
        ${COMMON_MODELS_DIR}/RouteInformation.cpp
        ${COMMON_MODELS_DIR}/Tai.cpp
        ${COMMON_MODELS_DIR}/TnapId.cpp
        ${COMMON_MODELS_DIR}/TraceDepth_anyOf.cpp
        ${COMMON_MODELS_DIR}/TraceDepth.cpp
        ${COMMON_MODELS_DIR}/TwapId.cpp
        ${COMMON_MODELS_DIR}/AccessType.cpp
        ${COMMON_MODELS_DIR}/Ambr.cpp
        ${COMMON_MODELS_DIR}/Arp.cpp
        ${COMMON_MODELS_DIR}/Arp.cpp
        ${COMMON_MODELS_DIR}/AtsssCapability.cpp
        ${COMMON_MODELS_DIR}/DnaiChangeType_anyOf.cpp
        ${COMMON_MODELS_DIR}/DnaiChangeType.cpp
        ${COMMON_MODELS_DIR}/Guami.cpp
        ${COMMON_MODELS_DIR}/Ipv6Addr.cpp
        ${COMMON_MODELS_DIR}/Ipv6Prefix.cpp
        ${COMMON_MODELS_DIR}/LineType_anyOf.cpp
        ${COMMON_MODELS_DIR}/LineType.cpp
        ${COMMON_MODELS_DIR}/NgApCause.cpp
        ${COMMON_MODELS_DIR}/PatchItem.cpp
        ${COMMON_MODELS_DIR}/PatchOperation_anyOf.cpp
        ${COMMON_MODELS_DIR}/PatchOperation.cpp
        ${COMMON_MODELS_DIR}/PduSessionType_anyOf.cpp
        ${COMMON_MODELS_DIR}/PduSessionType.cpp
        ${COMMON_MODELS_DIR}/PlmnIdNid.cpp
        ${COMMON_MODELS_DIR}/PresenceInfo.cpp
        ${COMMON_MODELS_DIR}/PresenceInfoRm.cpp
        ${COMMON_MODELS_DIR}/ProblemDetails.cpp
        ${COMMON_MODELS_DIR}/QosResourceType.cpp
        ${COMMON_MODELS_DIR}/RatType.cpp
        ${COMMON_MODELS_DIR}/RouteToLocation.cpp
        ${COMMON_MODELS_DIR}/Snssai.cpp
        ${COMMON_MODELS_DIR}/Snssai.cpp
        ${COMMON_MODELS_DIR}/SubscribedDefaultQos.cpp
        ${COMMON_MODELS_DIR}/TraceData.cpp
        ${COMMON_MODELS_DIR}/UserLocation.cpp
        )

endif()

SET(UTILS_COMMON_DIR ${SRC_TOP_DIR}/common/utils)

## UTILS used in PCF
target_include_directories(pcf PUBLIC ${UTILS_COMMON_DIR})
target_sources(pcf PRIVATE
        ${UTILS_COMMON_DIR}/options.cpp
        ${UTILS_COMMON_DIR}/nf_launch.cpp
        )

