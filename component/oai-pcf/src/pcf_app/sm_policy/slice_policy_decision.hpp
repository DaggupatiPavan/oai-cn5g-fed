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

/*! \file slice_policy_decision.hpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#ifndef FILE_SLICE_POLICY_DECISION_SEEN
#define FILE_SLICE_POLICY_DECISION_SEEN

#include "policy_decision.hpp"
#include "SmPolicyContextData.h"
#include "SmPolicyDecision.h"
#include "pcf_smpc_status_code.hpp"
#include "Snssai.h"

namespace oai::pcf::app::sm_policy {
/**
 * @brief Policy Decision based on slice.
 *
 */
class slice_policy_decision : public oai::pcf::app::sm_policy::policy_decision {
 public:
  explicit slice_policy_decision(
      const oai::model::common::Snssai& snssai,
      const oai::pcf::model::SmPolicyDecision& decision)
      : policy_decision(decision) {
    m_snssai = snssai;
  }

  ~slice_policy_decision() override = default;

  /**
   * @brief Decides based on context on a policy and the snssai information. In
   * case the return code is != CREATED, the decision reference may be undefined
   *
   * @param context input: The context of the individual sm policy association
   * @param decision output: The decision based on the context
   * @return oai::pcf::app::sm_policy::status_code   CREATED in case of
   * success
   */
  [[nodiscard]] oai::pcf::app::sm_policy::status_code decide(
      const oai::pcf::model::SmPolicyContextData& context,
      oai::pcf::model::SmPolicyDecision& decision) const override;

  /**
   * @brief Get the snssai object
   *
   * @return oai::pcf::model::Snssai
   */
  [[nodiscard]] oai::model::common::Snssai get_snssai() const;

  [[nodiscard]] std::string to_string() const override;

 private:
  oai::model::common::Snssai m_snssai;
};
}  // namespace oai::pcf::app::sm_policy

std::ostream& operator<<(
    std::ostream& os,
    const oai::pcf::app::sm_policy::slice_policy_decision& storage);

#endif
