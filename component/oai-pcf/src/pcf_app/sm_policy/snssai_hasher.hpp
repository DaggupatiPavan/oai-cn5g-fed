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

/*! \file snssai_hasher.hpp
 \brief
 \author  Stefan Spettel
 \company Openairinterface Software Allianse
 \date 2022
 \email: stefan.spettel@eurecom.fr
 */

#ifndef FILE_SNSSAI_HASHER_SEEN
#define FILE_SNSSAI_HASHER_SEEN

#include "Snssai.h"

/**
 * @brief Hash function to use Snssai objects as keys in (unordered) maps
 *
 */
namespace oai::pcf::app::sm_policy {
class snssai_hasher {
  const int HASH_SEED   = 17;
  const int HASH_FACTOR = 31;

 public:
  /**
   * @brief Calculates the hash for a snssai
   *
   * @param snssai calculate hash based on this value
   * @return size_t hash value
   */
  size_t operator()(const oai::model::common::Snssai& snssai) const {
    size_t res = HASH_SEED;
    res        = res * HASH_FACTOR + std::hash<std::string>()(snssai.getSd());
    res        = res * HASH_FACTOR + std::hash<int>()(snssai.getSst());
    return res;
  }
};
}  // namespace oai::pcf::app::sm_policy
#endif