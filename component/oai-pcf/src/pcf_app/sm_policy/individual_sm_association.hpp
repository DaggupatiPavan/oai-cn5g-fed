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

/*! \file individual_sm_association.hpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#ifndef FILE_INDIVIDUAL_SM_ASSOCIATION_SEEN
#define FILE_INDIVIDUAL_SM_ASSOCIATION_SEEN

#include "SmPolicyContextData.h"
#include "SmPolicyDecision.h"
#include "policy_decision.hpp"

#include <memory.h>

namespace oai::pcf::app::sm_policy {

class individual_sm_association {
 public:
  explicit individual_sm_association(
      const oai::pcf::model::SmPolicyContextData& context,
      const oai::pcf::app::sm_policy::policy_decision& decision,
      const std::string& id)
      : m_decision(decision) {
    m_context = context;
    m_id      = id;
  }

  virtual ~individual_sm_association() = default;

  [[nodiscard]] virtual const oai::pcf::model::SmPolicyContextData&
  get_sm_policy_context_data() const;

  [[nodiscard]] virtual const oai::pcf::model::SmPolicyDecision&
  get_sm_policy_decision_dto() const;

  [[nodiscard]] virtual oai::pcf::app::sm_policy::status_code redecide_policy(
      const oai::pcf::model::SmPolicyUpdateContextData& update_data,
      oai::pcf::model::SmPolicyDecision& new_decision,
      std::string& problem_details);

  [[nodiscard]] virtual oai::pcf::app::sm_policy::status_code decide_policy(
      oai::pcf::model::SmPolicyDecision& decision);

  [[nodiscard]] virtual std::string get_id() const;

 private:
  oai::pcf::model::SmPolicyContextData m_context;
  oai::pcf::app::sm_policy::policy_decision m_decision;
  std::string m_id;
};
}  // namespace oai::pcf::app::sm_policy
#endif
