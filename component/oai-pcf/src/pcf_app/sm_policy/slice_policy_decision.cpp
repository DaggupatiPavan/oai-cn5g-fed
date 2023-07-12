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

/*! \file slice_policy_decision.cpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#include "slice_policy_decision.hpp"
#include <sstream>

using namespace oai::pcf::model;
using namespace oai::pcf::app::sm_policy;
using namespace oai::pcf::app;
using namespace oai::model::common;

status_code slice_policy_decision::decide(
    const SmPolicyContextData& context,
    oai::pcf::model::SmPolicyDecision& decision) const {
  if (context.getSliceInfo() != m_snssai) {
    return status_code::CONTEXT_DENIED;
  }

  decision = m_decision;
  return status_code::CREATED;
}

Snssai slice_policy_decision::get_snssai() const {
  return m_snssai;
}

std::string slice_policy_decision::to_string() const {
  std::stringstream ss;
  ss << "Slice: Sd: " << m_snssai.getSd()
     << " Sst: " << std::to_string(m_snssai.getSst()) << "\n";
  ss << " -- " << m_decision;
  return ss.str();
}

std::ostream& operator<<(
    std::ostream& os,
    const oai::pcf::app::sm_policy::slice_policy_decision& storage) {
  return (os << storage.to_string());
}
