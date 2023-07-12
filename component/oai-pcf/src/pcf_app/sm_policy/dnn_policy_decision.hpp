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

/*! \file dnn_policy_decision.hpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#ifndef FILE_DNN_POLICY_DECISION_SEEN
#define FILE_DNN_POLICY_DECISION_SEEN

#include "policy_decision.hpp"
#include "SmPolicyContextData.h"
#include "SmPolicyDecision.h"
#include "pcf_smpc_status_code.hpp"

#include <string>

namespace oai::pcf::app::sm_policy {
/**
 * @brief Policy Decision based on DNN.
 *
 */
class dnn_policy_decision : public oai::pcf::app::sm_policy::policy_decision {
 public:
  explicit dnn_policy_decision(
      const std::string& dnn, const oai::pcf::model::SmPolicyDecision& decision)
      : policy_decision(decision) {
    m_dnn = dnn;
  }

  ~dnn_policy_decision() override = default;

  /**
   * @brief Decides based on context on a policy and the DNN information. In
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
   * @brief Get the dnn object
   *
   * @return std::string
   */
  [[nodiscard]] std::string get_dnn() const;

  [[nodiscard]] std::string to_string() const override;

 private:
  std::string m_dnn;
};
}  // namespace oai::pcf::app::sm_policy

std::ostream& operator<<(
    std::ostream& os,
    const oai::pcf::app::sm_policy::dnn_policy_decision& storage);

#endif
