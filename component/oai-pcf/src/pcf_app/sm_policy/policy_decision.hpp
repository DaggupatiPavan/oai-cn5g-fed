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

#ifndef FILE_POLICY_DECISION_SEEN
#define FILE_POLICY_DECISION_SEEN

#include "SmPolicyContextData.h"
#include "SmPolicyDecision.h"
#include "SmPolicyUpdateContextData.h"
#include "pcf_smpc_status_code.hpp"

namespace oai::pcf::app::sm_policy {

/**
 * @brief Base class for policy decisions, also acts as default policy
 *
 */
class policy_decision {
 public:
  explicit policy_decision(const oai::pcf::model::SmPolicyDecision& decision) {
    m_decision = decision;
  }

  policy_decision(const policy_decision& other) {
    m_decision = other.m_decision;
  }

  /**
   * @brief Decides based on context on a policy. In case the return code is !=
   * CREATED, the decision reference may be undefined
   *
   * @param context input: The context of the individual sm policy association
   * @param decision output: The decision based on the context
   * @return oai::pcf::app::sm_policy::status_code   CREATED in case of
   * success
   */
  [[nodiscard]] virtual oai::pcf::app::sm_policy::status_code decide(
      const oai::pcf::model::SmPolicyContextData& context,
      oai::pcf::model::SmPolicyDecision& decision) const;

  /**
   * @brief Redecides based on the original context, original decision and
   * creates a new decision. The new_decision contains a complete new policy
   * decision
   *
   * @param original_context The context of the create request and/or
   * previous update requests, is changed according to updated values in
   * update_data
   * @param update_data input: The data from the update
   * @param new_decision output: the diff to the old decision (TODO currently no
   * diff, but whole object)
   * @param problem_details output: Error information
   * @return oai::pcf::app::sm_policy::status_code OK in case of successful
   * update
   */
  [[nodiscard]] virtual oai::pcf::app::sm_policy::status_code redecide(
      oai::pcf::model::SmPolicyContextData& original_context,
      const oai::pcf::model::SmPolicyUpdateContextData& update_data,
      oai::pcf::model::SmPolicyDecision& new_decision,
      std::string& problem_details);

  virtual ~policy_decision() = default;

  [[nodiscard]] virtual const oai::pcf::model::SmPolicyDecision&
  get_sm_policy_decision() const;

  [[nodiscard]] virtual std::string to_string() const;

 protected:
  oai::pcf::app::sm_policy::status_code handle_plmn_change(
      oai::pcf::model::SmPolicyContextData& orig_context,
      const oai::pcf::model::SmPolicyUpdateContextData& update,
      std::string& problem_details);

  oai::pcf::app::sm_policy::status_code handle_access_type_change(
      oai::pcf::model::SmPolicyContextData& orig_context,
      const oai::pcf::model::SmPolicyUpdateContextData& update,
      std::string& problem_details);

  oai::pcf::app::sm_policy::status_code handle_ip_address_change(
      oai::pcf::model::SmPolicyContextData& orig_context,
      const oai::pcf::model::SmPolicyUpdateContextData& update,
      std::string& problem_details);

  oai::pcf::app::sm_policy::status_code handle_rat_type_change(
      oai::pcf::model::SmPolicyContextData& orig_context,
      const oai::pcf::model::SmPolicyUpdateContextData& update,
      std::string& problem_details);

  oai::pcf::model::SmPolicyDecision m_decision;
};
}  // namespace oai::pcf::app::sm_policy

std::ostream& operator<<(
    std::ostream& os, const oai::pcf::app::sm_policy::policy_decision& storage);

#endif
