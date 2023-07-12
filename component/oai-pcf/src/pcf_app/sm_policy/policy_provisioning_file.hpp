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

/*! \file policy_provisioning_file.hpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#ifndef FILE_POLICY_PROVISIONING_FILE_SEEN
#define FILE_POLICY_PROVISIONING_FILE_SEEN

#include <yaml-cpp/yaml.h>
#include "nlohmann/json.hpp"
#include <vector>
#include "SmPolicyDecision.h"
#include "PccRule.h"
#include "TrafficControlData.h"
#include "policy_storage.hpp"

namespace oai::pcf::app::sm_policy {

class policy_provisioning_file {
 public:
  bool read_all_policy_files();
  explicit policy_provisioning_file(
      const std::shared_ptr<oai::pcf::app::sm_policy::policy_storage>&
          policy_storage) {
    m_policy_storage = policy_storage;
  }

 private:
  static bool read_all_files_in_dir(
      const std::string& dir_path, std::vector<YAML::Node>& yaml_output);

  static oai::pcf::model::SmPolicyDecision decision_from_rules(
      const YAML::Node& node,
      const std::map<std::string, oai::pcf::model::PccRule>& pcc_rules,
      const std::map<std::string, oai::pcf::model::TrafficControlData>&
          traffic_control);

  template<class T>
  static std::map<std::string, T> convert_yaml_to_model(
      const std::vector<YAML::Node>& nodes);

  static void replace_json_string_with_int(nlohmann::json& j);

  std::shared_ptr<oai::pcf::app::sm_policy::policy_storage> m_policy_storage;
};
}  // namespace oai::pcf::app::sm_policy
#endif
