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

#ifndef FILE_CONVERSIONS_HPP_SEEN
#define FILE_CONVERSIONS_HPP_SEEN

#include <netinet/in.h>
#include <stdint.h>

#include <iostream>
#include <string>

#include "bstrlib.h"

extern "C" {
#include "OCTET_STRING.h"
#include "BIT_STRING.h"
#include "dynamic_memory_check.h"
}

/* Used to format an uint32_t containing an ipv4 address */
#define IN_ADDR_FMT "%u.%u.%u.%u"
#define PRI_IN_ADDR(aDDRESS)                                                   \
  (uint8_t)((aDDRESS.s_addr) & 0x000000ff),                                    \
      (uint8_t)(((aDDRESS.s_addr) & 0x0000ff00) >> 8),                         \
      (uint8_t)(((aDDRESS.s_addr) & 0x00ff0000) >> 16),                        \
      (uint8_t)(((aDDRESS.s_addr) & 0xff000000) >> 24)

#define IPV4_ADDR_DISPLAY_8(aDDRESS)                                           \
  (aDDRESS)[0], (aDDRESS)[1], (aDDRESS)[2], (aDDRESS)[3]

class conv {
 public:
  static int ascii_to_hex(uint8_t* dst, const char* h);
  static struct in_addr fromString(const std::string addr4);
  static std::string toString(const struct in_addr& inaddr);
  static std::string toString(const struct in6_addr& in6addr);
  static std::string mccToString(
      const uint8_t digit1, const uint8_t digit2, const uint8_t digit3);
  static std::string mncToString(
      const uint8_t digit1, const uint8_t digit2, const uint8_t digit3);
  static std::string tmsi_to_string(const uint32_t tmsi);

  static void msg_str_2_msg_hex(std::string msg, bstring& b);
  static char* bstring2charString(bstring b);
  static unsigned char* format_string_as_hex(std::string str);
  static void convert_string_2_hex(
      std::string& input_str, std::string& output_str);
  static bool octet_string_2_bstring(
      const OCTET_STRING_t& octet_str, bstring& b_str);
  static bool bstring_2_octet_string(
      const bstring& b_str, OCTET_STRING_t& octet_str);
  static bool octet_string_2_bit_string(
      const OCTET_STRING_t& octet_str, BIT_STRING_t& bit_str,
      const uint8_t& bits_unused);
  static bool bstring_2_bit_string(const bstring& b_str, BIT_STRING_t& bit_str);
  static bool sd_string_to_int(const std::string& sd_str, uint32_t& sd);
  static bool string_to_int(
      const std::string& str, uint32_t& value, const uint8_t& base);
  static bool string_to_int8(const std::string& str, uint8_t& value);
  static bool string_to_int32(const std::string& str, uint32_t& value);
  static void bstring_2_string(const bstring& b_str, std::string& str);
  static void string_2_bstring(const std::string& str, bstring& b_str);
  static void octet_string_2_string(
      const OCTET_STRING_t& octet_str, std::string& str);
  static void string_2_octet_string(
      const std::string& str, OCTET_STRING_t& o_str);
  static bool int8_2_octet_string(const uint8_t& value, OCTET_STRING_t& o_str);
  static bool octet_string_2_int8(const OCTET_STRING_t& o_str, uint8_t& value);
  // TODO: bitstring_2_int32
  static bool octet_string_copy(
      OCTET_STRING_t& destination, const OCTET_STRING_t& source);

  static bool check_bstring(const bstring& b_str);
  static bool check_octet_string(const OCTET_STRING_t& octet_str);
};
#endif /* FILE_CONVERSIONS_HPP_SEEN */
