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

/*! \file individual_sm_association.cpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#include "individual_sm_association.hpp"

using namespace oai::pcf::model;
using namespace oai::pcf::app::sm_policy;

const SmPolicyContextData&
individual_sm_association::get_sm_policy_context_data() const {
  return m_context;
}

const SmPolicyDecision& individual_sm_association::get_sm_policy_decision_dto()
    const {
  return m_decision.get_sm_policy_decision();
}

std::string individual_sm_association::get_id() const {
  return m_id;
}

oai::pcf::app::sm_policy::status_code
individual_sm_association::redecide_policy(
    const SmPolicyUpdateContextData& update_data,
    SmPolicyDecision& new_decision, std::string& problem_details) {
  return m_decision.redecide(
      m_context, update_data, new_decision, problem_details);
}

oai::pcf::app::sm_policy::status_code individual_sm_association::decide_policy(
    oai::pcf::model::SmPolicyDecision& decision) {
  return m_decision.decide(m_context, decision);
}
