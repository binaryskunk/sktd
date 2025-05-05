// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_MEM_UTILS_HH
#define SKTD_MEM_UTILS_HH

#include <sktd/type_aliases.hh>
#include <sktd/min_max.hh>

namespace sktd {
namespace mem {

/*inline auto copy(const u8* from, u8* to, usize n) -> void {
  bool user_requested_zero_bytes_copy = n <= 0;
  if (user_requested_zero_bytes_copy) {
    return;
  }

  bool user_supplied_any_null_pointer = from == nullptr || to == nullptr;
  if (user_supplied_any_null_pointer) {
    return;
  }

  for (usize i = 0; i < n; ++i) {
    to[i] = from[i];
  }
}*/

inline auto copy(const void* from, void* to, usize n) -> void* {
  bool user_requested_zero_bytes_copy = n == 0;
  if (user_requested_zero_bytes_copy) {
    return to;
  }

  bool user_supplied_any_null_pointer = from == nullptr || to == nullptr;
  if (user_supplied_any_null_pointer) {
    return nullptr;
  }

  u8* dst = static_cast<u8*>(to);
  const u8* src = static_cast<const u8*>(from);

  for (usize i = 0; i < n; ++i) {
    dst[i] = src[i];
  }

  return to;
}

/*inline auto copy(const i8* from, i8* to, usize n) -> void {
  copy(reinterpret_cast<const u8*>(from),
       reinterpret_cast<u8*>(to),
       n);
}*/

inline auto string_size(const char8* str) -> usize {
  bool user_supplied_invalid_string = str == nullptr;
  if (user_supplied_invalid_string) {
    return 0;
  }

  usize size = 0;
  while (str[size] != '\0') {
    size++;
  }

  return size;
}

inline auto string_copy(const char8* from, char8* to) noexcept -> void {
  const usize from_size = string_size(from);
  const usize to_size = string_size(to);

  const usize size = min(from_size, to_size);

  copy(reinterpret_cast<const u8*>(from), reinterpret_cast<u8*>(to), size);
  to[size] = '\0';
}

}  // namespace mem
}  // namespace sktd

#endif

/*
 * Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
 *
 * This file is part of sktd and is licensed under the
 * BinarySkunk's Public License (BSPL), version 1, as published by
 * Lavínia "BinarySkunk" Rodrigues.
 *
 * You should have received a copy of the BSPL along with this program.
 * If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
 */
