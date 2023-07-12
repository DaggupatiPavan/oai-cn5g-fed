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

/*! \file policy_storage.cpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#include "policy_storage.hpp"
#include "logger.hpp"
#include <string>
#include <sstream>

using namespace oai::pcf::app::sm_policy;
using namespace oai::pcf::model;
using namespace oai::model::common;

void policy_storage::set_default_decision(const SmPolicyDecision& decision) {
  std::shared_ptr<policy_decision> desc =
      std::make_shared<policy_decision>(decision);

  default_decision = desc;
  notify_subscribers(desc);
}

void policy_storage::insert_supi_decision(
    const std::string& supi, const SmPolicyDecision& decision) {
  std::unique_lock supi_decision_lock(m_supi_policy_decisions_mutex);

  std::shared_ptr<supi_policy_decision> desc =
      std::make_shared<supi_policy_decision>(supi, decision);

  m_supi_policy_decisions.insert(std::make_pair(supi, desc));
  supi_decision_lock.unlock();
  notify_subscribers(desc);
}

void policy_storage::insert_dnn_decision(
    const std::string& dnn, const SmPolicyDecision& decision) {
  std::unique_lock dnn_decision_lock(m_dnn_policy_decisions_mutex);

  std::shared_ptr<dnn_policy_decision> desc =
      std::make_shared<dnn_policy_decision>(dnn, decision);

  m_dnn_policy_decisions.insert(std::make_pair(dnn, desc));
  dnn_decision_lock.unlock();
  notify_subscribers(desc);
}

void policy_storage::insert_slice_decision(
    const Snssai& slice, const SmPolicyDecision& decision) {
  std::unique_lock slice_decision_lock(m_slice_policy_decisions_mutex);

  std::shared_ptr<slice_policy_decision> desc =
      std::make_shared<slice_policy_decision>(slice, decision);

  m_slice_policy_decisions.insert(std::make_pair(slice, desc));
  slice_decision_lock.unlock();
  notify_subscribers(desc);
}
/**
 * @brief Finds a policy based on the existing supi, dnn, slice and default
 * policies in that order.
 *
 * @param context  The policy context containing supi or dnn or snssai
 * @param chosen_decision
 * decision base class
 * @return pointer to the object implementing the chosen, null in case no
 * decision can be found
 */
std::shared_ptr<policy_decision> policy_storage::find_policy(
    const oai::pcf::model::SmPolicyContextData& context) {
  std::string msg_base = "SM Policy request from SUPI:";
  std::string supi     = context.getSupi();

  std::shared_ptr<policy_decision> res_ptr;

  // First, check based on SUPI, then DNN, then Slice, then global default rule.
  std::shared_lock lock_supi(m_supi_policy_decisions_mutex);
  auto got_supi = m_supi_policy_decisions.find(context.getSupi());

  if (got_supi == m_supi_policy_decisions.end()) {
    Logger::pcf_app().debug(
        "%s %s - Did not find SUPI policy", msg_base.c_str(), supi.c_str());
    std::shared_lock lock_dnn(m_dnn_policy_decisions_mutex);
    auto got_dnn = m_dnn_policy_decisions.find(context.getDnn());

    if (got_dnn == m_dnn_policy_decisions.end()) {
      Logger::pcf_app().debug(
          "%s %s - Did not find DNN policy", msg_base.c_str(), supi.c_str());
      std::shared_lock lock_slice(m_slice_policy_decisions_mutex);
      auto got_slice = m_slice_policy_decisions.find(context.getSliceInfo());

      if (got_slice == m_slice_policy_decisions.end()) {
        Logger::pcf_app().debug(
            "%s %s - Did not find slice policy", msg_base.c_str(),
            supi.c_str());

        if (!default_decision) {
          Logger::pcf_app().debug(
              "%s %s - Did not find default policy", msg_base.c_str(),
              supi.c_str());

          return res_ptr;  // null
        } else {
          Logger::pcf_app().debug(
              "%s %s - Decide based on default policy", msg_base.c_str(),
              supi.c_str());
          return default_decision;
        }
      } else {
        Logger::pcf_app().debug("%s Decide based on slice", msg_base.c_str());
        return got_slice->second;
      }
    } else {
      Logger::pcf_app().debug("%s Decide based on DNN", msg_base.c_str());
      return got_dnn->second;
    }
  } else {
    Logger::pcf_app().debug("%s Decide based on SUPI", msg_base.c_str());
    return got_supi->second;
  }
}

void policy_storage::notify_subscribers(
    const std::shared_ptr<policy_decision>& /* decision */) {
  // TODO
}

void policy_storage::subscribe_to_decision_change(
    std::function<void(std::shared_ptr<policy_decision>&)> /* callback */) {
  // TODO implement me
}

std::string policy_storage::to_string() const {
  std::shared_lock supi_lock(m_supi_policy_decisions_mutex);
  std::shared_lock dnn_lock(m_dnn_policy_decisions_mutex);
  std::shared_lock slice_lock(m_slice_policy_decisions_mutex);

  std::stringstream ss;

  std::string output;

  ss << "Policy Storage: \n";
  ss << " - Default Decision: \n";
  if (default_decision) {
    ss << " -- " << *default_decision << "\n";
  } else {
    ss << " -- No Default Decision\n";
  }
  ss << " - Slice Decisions: \n";
  if (!m_slice_policy_decisions.empty()) {
    for (const auto& slice_desc : m_slice_policy_decisions) {
      ss << " -- " << *slice_desc.second << "\n";
    }
  } else {
    ss << " -- No Slice Decisions\n";
  }
  ss << " - DNN Decisions: \n";
  if (!m_dnn_policy_decisions.empty()) {
    for (const auto& dnn_desc : m_dnn_policy_decisions) {
      ss << " -- " << *dnn_desc.second << "\n";
    }
  } else {
    ss << " -- No DNN Decisions\n";
  }

  if (!m_supi_policy_decisions.empty()) {
    ss << " - SUPI Decisions: \n";
    for (const auto& supi_desc : m_supi_policy_decisions) {
      ss << " -- " << *supi_desc.second << "\n";
    }
  } else {
    ss << " - No SUPI Decisions\n";
  }

  return ss.str();
}

std::ostream& operator<<(
    std::ostream& os, const oai::pcf::app::sm_policy::policy_storage& storage) {
  return os << storage.to_string();
}
