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

/*! \file launch.hpp
\brief
\author  Stefan Spettel
\company OpenAirInterface Software Alliance
\date 2022
\email: stefan.spettel@eurecom.fr
 */

#pragma once

#include <cstdint>
#include <string>

namespace oai::utils {

class nf_launch {
 public:
  /**
   * Checks if a process of this NF is already running
   * @return True when a process is already running
   */
  static bool already_running();

 private:
  /**
   * Executes the given command and returns the output
   * WARNING: This function does not sanitize user input, do not call it on
   * any un-sanitized user input due to security reasons
   * @param command Command to execute
   * @return Output
   */
  static std::string command_output(const std::string& command);
};

}  // namespace oai::utils
