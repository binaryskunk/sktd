// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#include <sktd/allocator.hh>

#include <sktd/type_aliases.hh>
#include <sktd/utility.hh>

namespace sktd {
namespace mem {

auto heap_allocator::alloc(usize n) noexcept -> void* {
  bool user_requested_to_allocate_zero_bytes = n == 0;
  if (user_requested_to_allocate_zero_bytes) {
    return nullptr;
  }

  // binaryskunk: `operator new` can throw an exception in case of bad
  // allocation, which is undesired here... i am thinking of building my own
  // `operator new`/`malloc` replacement soon
  void* ptr = nullptr;
  try {
    ptr = ::operator new(n);
  } catch (...) {
    return nullptr;
  }

  return ptr;
}

auto heap_allocator::free(void* ptr) noexcept -> void {
  bool user_tried_to_free_invalid_pointer = ptr == nullptr;
  if (user_tried_to_free_invalid_pointer) {
    return;
  }

  // binaryskunk: see above comment
  // binaryskunk: also, this code must be refactored soon TwT
  try {
    ::operator delete(ptr);
  } catch (...) {
    // purposelly no-op
  }
}

auto pool_allocator_error::what() const -> const char8* { return this->_msg; }

template <valid_allocator Allocator, class T>
auto pool_allocator<Allocator, T>::alloc() noexcept
    -> sktd::result<T*, pool_allocator_error> {
  const bool no_capacity_left = this->_counter >= this->_capacity;
  if (no_capacity_left) {
    return make_err<T*, pool_allocator_error>("pool has no free space left");
  }

  auto* ptr = this->_pool[this->_counter++];

  return make_ok(ptr);
}

template <valid_allocator Allocator, class T>
auto pool_allocator<Allocator, T>::free(const T* ptr) noexcept -> void {
  const bool all_capacity_is_free = this->_counter == 0;
  if (!all_capacity_is_free) {
    this->_counter--;
  }
}

}  // namespace mem
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
