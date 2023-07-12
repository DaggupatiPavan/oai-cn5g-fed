################################################################################
# Licensed to the OpenAirInterface (OAI) Software Alliance under one or more
# contributor license agreements.  See the NOTICE file distributed with
# this work for additional information regarding copyright ownership.
# The OpenAirInterface Software Alliance licenses this file to You under
# the OAI Public License, Version 1.1  (the "License"); you may not use this file
# except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.openairinterface.org/?page_id=698
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------------------------------------
# For more information about the OpenAirInterface (OAI) Software Alliance:
#      contact@openairinterface.org
################################################################################
include_directories(${SRC_TOP_DIR}/common)
include_directories(${SRC_TOP_DIR}/common/msg)
include_directories(${SRC_TOP_DIR}/common/utils)
include_directories(${SRC_TOP_DIR}/itti)
include_directories(${SRC_TOP_DIR}/pcf)
include_directories(${SRC_TOP_DIR}/api-server/api)
include_directories(${SRC_TOP_DIR}/api-server/impl)
include_directories(${SRC_TOP_DIR}/api-server/model)
include_directories(${SRC_TOP_DIR}/api-server/)
include_directories(${SRC_TOP_DIR}/pcf_app/sm_policy/)

add_library (PCF STATIC
  pcf_app.cpp
  pcf_nrf.cpp
  pcf_client.cpp
  pcf_config.cpp
  pcf_profile.cpp
  pcf_event.cpp
  pcf_sm_policy_control.cpp
  task_manager.cpp
  sm_policy/individual_sm_association.cpp
  sm_policy/policy_decision.cpp
  sm_policy/slice_policy_decision.cpp
  sm_policy/supi_policy_decision.cpp
  sm_policy/dnn_policy_decision.cpp
  sm_policy/policy_storage.cpp
  sm_policy/policy_provisioning_file.cpp
  )

## Common modules
include(${SRC_TOP_DIR}/oai-cn5g-common-src/logger/logger.cmake)
include(${SRC_TOP_DIR}/common/utils/utils.cmake)

include(${BUILD_TOP_DIR}/pcf/used_common_files.cmake)
