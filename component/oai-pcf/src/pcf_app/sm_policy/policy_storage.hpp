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

/*! \file policy_storage.hpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#ifndef FILE_POLICY_STORAGE_SEEN
#define FILE_POLICY_STORAGE_SEEN

#include <string>
#include <memory>
#include <shared_mutex>
#include <unordered_map>

#include "SmPolicyDecision.h"
#include "SmPolicyContextData.h"
#include "Snssai.h"
#include "policy_decision.hpp"
#include "slice_policy_decision.hpp"
#include "dnn_policy_decision.hpp"
#include "supi_policy_decision.hpp"
#include "snssai_hasher.hpp"

namespace oai::pcf::app::sm_policy {
/**
 * @brief Class to store policies, either pre-configured using files and/or AF
 * or provisioning requests
 *
 */

class policy_storage {
 private:
  void notify_subscribers(const std::shared_ptr<policy_decision>& decision);

  std::unordered_map<
      oai::model::common::Snssai,
      std::shared_ptr<oai::pcf::app::sm_policy::slice_policy_decision>,
      oai::pcf::app::sm_policy::snssai_hasher>
      m_slice_policy_decisions;

  std::unordered_map<
      std::string,
      std::shared_ptr<oai::pcf::app::sm_policy::dnn_policy_decision>>
      m_dnn_policy_decisions;

  std::unordered_map<
      std::string,
      std::shared_ptr<oai::pcf::app::sm_policy::supi_policy_decision>>
      m_supi_policy_decisions;

  std::shared_ptr<oai::pcf::app::sm_policy::policy_decision> default_decision;

  mutable std::shared_mutex m_slice_policy_decisions_mutex;
  mutable std::shared_mutex m_dnn_policy_decisions_mutex;
  mutable std::shared_mutex m_supi_policy_decisions_mutex;

 public:
  explicit policy_storage()             = default;
  policy_storage(policy_storage const&) = delete;
  void operator=(policy_storage const&) = delete;

  // TODO methods to update and delete policies
  void insert_supi_decision(
      const std::string& supi,
      const oai::pcf::model::SmPolicyDecision& decision);

  void insert_dnn_decision(
      const std::string& dnn,
      const oai::pcf::model::SmPolicyDecision& decision);

  void insert_slice_decision(
      const oai::model::common::Snssai&,
      const oai::pcf::model::SmPolicyDecision& decision);

  void set_default_decision(const oai::pcf::model::SmPolicyDecision& decision);

  std::shared_ptr<policy_decision> find_policy(
      const oai::pcf::model::SmPolicyContextData& context);

  /**
   * @brief Calls the callback when any of the policies have been updated
   *
   * @param callback
   */
  void subscribe_to_decision_change(
      std::function<void(std::shared_ptr<policy_decision>&)> callback);

  std::string to_string() const;
};
}  // namespace oai::pcf::app::sm_policy

std::ostream& operator<<(
    std::ostream& os, const oai::pcf::app::sm_policy::policy_storage& storage);

#endif
