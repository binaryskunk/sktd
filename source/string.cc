// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#include <sktd/string.hh>

#include <sktd/mem_utils.hh>

namespace sktd {

template <mem::valid_allocator Alloc>
auto string<Alloc>::_preallocate(usize capacity) -> void {
  this->_data = this->_allocator.alloc(capacity);
  this->_data[0] = '\0';

  this->_capacity = capacity;
}

template <mem::valid_allocator Alloc>
string<Alloc>::string() {
  this->_preallocate(15);
}

template <mem::valid_allocator Alloc>
string<Alloc>::string(const char8* str) {
  usize len = 0;
  while (str[len]) {
    len++;
  }

  this->_preallocate(len);
  mem::string_copy(str, this->_data);

  this->_size = len;
}

template <mem::valid_allocator Alloc>
string<Alloc>::string(const string& other) {
  this->_preallocate(other._size);
  mem::string_copy(other._data, this->_data);

  this->_size = other._size;
}

template <mem::valid_allocator Alloc>
string<Alloc>::~string() {
  this->_allocator.free(this->_data);
}

template <mem::valid_allocator Alloc>
auto string<Alloc>::operator=(const string& other) -> string& {
  bool this_and_other_are_the_same = this == &other;
  if (this_and_other_are_the_same) {
    return *this;
  }

  this->_allocator.free(this->_data);

  this->_preallocate(other._size);
  mem::string_copy(other._data, this->_data);

  this->_size = other._size;

  return *this;
}

template <mem::valid_allocator Alloc>
auto string<Alloc>::operator=(string&& other) noexcept -> string& {
  bool this_and_other_are_the_same = this == &other;
  if (this_and_other_are_the_same) {
    return *this;
  }

  this->_allocator.free(this->_data);

  this->_data = other._data;
  this->_size = other._size;
  this->_capacity = other._capacity;

  other._data = nullptr;
  other._size = 0;
  other._capacity = 0;

  return *this;
}

template <mem::valid_allocator Alloc>
auto string<Alloc>::operator+=(const string& other) -> string& {
  const usize new_size = this->_size + other._size;
  const usize diff = new_size - this->_size;

  bool we_are_out_of_capacity = new_size > this->_capacity;
  if (we_are_out_of_capacity) {
    char8* new_data = this->_allocator.alloc(new_size + 1);

    mem::string_copy(this->_data, new_data);
    this->_allocator.free(this->_data);

    this->_data = new_data;
    this->_capacity = new_size;
  }

  mem::copy(other._data, this->_data + this->_size, diff);
  this->_size = new_size;

  return *this;
}

template <mem::valid_allocator Alloc>
auto string<Alloc>::data() const -> const char8* {
  return this->_data;
}

template <mem::valid_allocator Alloc>
auto string<Alloc>::size() const -> usize {
  return this->_size;
}

}  // namespace sktd

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
