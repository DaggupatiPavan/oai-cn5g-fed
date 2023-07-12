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

/*! \file launch.cpp
\brief
\author  Stefan Spettel
\company OpenAirInterface Software Alliance
\date 2022
\email: stefan.spettel@eurecom.fr
*/

#include "nf_launch.hpp"

#include <boost/filesystem.hpp>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <stdexcept>

using namespace oai::utils;
namespace fs = boost::filesystem;

//------------------------------------------------------------------------------
bool nf_launch::already_running() {
  // Strip the exec name from the path

  auto process_name = fs::canonical("/proc/self/exe").filename().string();

  std::string cmd    = "pgrep -c " + process_name;
  std::string output = command_output(cmd);

  int running_processes;

  try {
    running_processes = std::stoi(output);
  } catch (std::invalid_argument& ex) {
    std::cout << "ERROR: Could not read how many processes are running"
              << std::endl;
    return true;
  }

  if (running_processes > 1) {
    std::cout << "ERROR: There are " << running_processes << " instances of "
              << process_name << " running" << std::endl;
    return true;
  }
  return false;
}

//------------------------------------------------------------------------------
std::string nf_launch::command_output(const std::string& command) {
  static uint64_t index = 0;
  auto filename         = std::ostringstream{};
  filename << getpid() << "_" << index++;
  auto const tmp_path = fs::temp_directory_path() / filename.str();
  if (fs::exists(tmp_path) && !fs::remove(tmp_path)) {
    return "failed to open temporary file " + tmp_path.string();
  }

  int ret =
      std::system((command + " > " + tmp_path.string() + " 2>&1 ").c_str());
  if (ret != 0) {
    return "Command return non-zero exit code";
  }

  auto content = std::ostringstream{};
  {
    auto const istream = std::ifstream{tmp_path.string()};
    content << istream.rdbuf();
  }

  fs::remove(tmp_path);
  return content.str();
}
