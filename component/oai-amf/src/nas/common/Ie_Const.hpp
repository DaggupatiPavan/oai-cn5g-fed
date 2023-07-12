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

#pragma once

constexpr uint8_t kIeIsOptional    = true;
constexpr uint8_t kIeIsNotOptional = false;

constexpr uint8_t kIei5gmmCause                              = 0x58;
constexpr uint8_t kIei5gsmCapability                         = 0x28;
constexpr uint8_t kIei5gsDrxParameters                       = 0x51;
constexpr uint8_t kIei5gsmCongestionReAttemptIndicator       = 0x61;
constexpr uint8_t kIei5gsmNetworkFeatureSupport              = 0x17;
constexpr uint8_t kIei5gsMobileIdentityImeiSv                = 0x77;
constexpr uint8_t kIei5gsMobileIdentityNonImeiSvPei          = 0x78;
constexpr uint8_t kIei5gsRegistrationResult                  = 0x44;
constexpr uint8_t kIei5gsTrackingAreaIdentity                = 0x52;
constexpr uint8_t kIei5gsTrackingAreaIdentityList            = 0x54;
constexpr uint8_t kIei5gsUpdateType                          = 0x53;
constexpr uint8_t kIeiAdditionalInformation                  = 0x24;
constexpr uint8_t kIeiAllowedSscMode                         = 0x0f;
constexpr uint8_t kIeiAlwaysOnPduSessionIndication           = 0x08;
constexpr uint8_t kIeiAlwaysOnPduSessionRequested            = 0x0b;
constexpr uint8_t kIeiAtsssContainer                         = 0x77;
constexpr uint8_t kIeiAuthorizedQosFlowDescriptions          = 0x79;
constexpr uint8_t kIeiAuthorizedQosRules                     = 0x7a;
constexpr uint8_t kIeiBackOffTimerValue                      = 0x37;
constexpr uint8_t kIeiControlPlaneOnlyIndication             = 0x0c;
constexpr uint8_t kIeiDnn                                    = 0x25;
constexpr uint8_t kIeiDsTtEthernetPortMacAddress             = 0x6e;
constexpr uint8_t kIeiEapMessage                             = 0x78;
constexpr uint8_t kIeiEthernetHeaderCompressionConfiguration = 0x1f;
constexpr uint8_t kIeiExtendedDrxParameters                  = 0x6e;
constexpr uint8_t kIeiExtendedProtocolConfigurationOptions   = 0x7b;
constexpr uint8_t kIeiIntegrityProtectionMaximumDataRate     = 0x13;
constexpr uint8_t kIeiIpHeaderCompressionConfiguration       = 0x66;
constexpr uint8_t kIeiMaPduSessionInformation                = 0xa0;
constexpr uint8_t kIeiMappedEpsBearerContexts                = 0x75;
constexpr uint8_t kIeiMaximumNumberOfSupportedPacketFilters  = 0x55;
constexpr uint8_t kIeiNbN1ModeDrxParameters                  = 0x29;
constexpr uint8_t kIeiNSSAIAllowed                           = 0x15;
constexpr uint8_t kIeiNSSAIConfigured                        = 0x31;
constexpr uint8_t kIeiNSSAIPending                           = 0x39;
constexpr uint8_t kIeiOldPduSessionId                        = 0x59;
constexpr uint8_t kIeiPduAddress                             = 0x29;
constexpr uint8_t kIeiPduSessionId                           = 0x12;
constexpr uint8_t kIeiPduSessionType                         = 0x09;
constexpr uint8_t kIeiPortManagementInformationContainer     = 0x74;
constexpr uint8_t kIeiReAttemptIndicator                     = 0x1d;
constexpr uint8_t kIeiRejectedNssaiRa                        = 0x11;
constexpr uint8_t kIeiRejectedNssaiRr                        = 0x69;
constexpr uint8_t kIeiRejectedNssaiDr                        = 0x6D;
constexpr uint8_t kIeiRejectedNssaiCuc                       = 0x11;
constexpr uint8_t kIeiReleaseAssistanceIndication            = 0xf0;
constexpr uint8_t kIeiRequestedQosFlowDescriptions           = 0x79;
constexpr uint8_t kIeiRequestedQosRules                      = 0x7a;
constexpr uint8_t kIeiRequestType                            = 0x80;
constexpr uint8_t kIeiRqTimerValue                           = 0x56;
constexpr uint8_t kIeiServingPlmnRateControlPsea             = 0x18;
constexpr uint8_t kIeiServingPlmnRateControlPsmc             = 0x1e;
constexpr uint8_t kIeiSessionAmbr                            = 0x2a;
constexpr uint8_t kIeiSmPduDnRequestContainer                = 0x39;
constexpr uint8_t kIeiSNssai                                 = 0x22;
constexpr uint8_t kIeiSscMode                                = 0x0a;
constexpr uint8_t kIeiSuggestedInterfaceIdentifier           = 0x29;
constexpr uint8_t kIeiUeDsTtResidenceTime                    = 0x6f;
constexpr uint8_t kIeiFullNameForNetwork                     = 0x43;
constexpr uint8_t kIeiShortNameForNetwork                    = 0x45;
