// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef INCLUDE_SKTD_STRING_HH_
#define INCLUDE_SKTD_STRING_HH_

#include <sktd/type_aliases.hh>
#include <sktd/allocator.hh>

namespace sktd {

template <mem::valid_allocator Alloc>
class string {
 private:
  Alloc _allocator{};

  char8* _data{nullptr};
  usize _size{0};
  usize _capacity{0};

  auto _preallocate(usize capacity) -> void;

 public:
  string();

  explicit string(const char8* str);

  string(const string& other);

  string(string&& other) noexcept
      : _data{other._data}, _size{other._size}, _capacity{other._capacity} {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }

  ~string();

  auto operator=(const string& other) -> string&;

  auto operator=(string&& other) noexcept -> string&;

  auto operator+=(const string& other) -> string&;

  auto data() const -> const char8*;

  auto size() const -> usize;
};

using heap_string = string<mem::heap_allocator>;

}  // namespace sktd

#endif  // INCLUDE_SKTD_STRING_HH_

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
