// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_ALLOCATOR_HH
#define SKTD_ALLOCATOR_HH

#include <sktd/type_aliases.hh>
#include <sktd/type_traits.hh>

namespace sktd {
namespace mem {

class base_allocator {
 public:
  virtual auto alloc(usize n) noexcept -> void* = 0;

  virtual auto free(void* ptr) noexcept -> void = 0;
};

template <class T>
concept valid_allocator = derived_from<remove_cvref_t<T>, base_allocator>;

/*namespace internal {

struct memory_block final {
  void* ptr;
  usize size;
  bool is_array;

  memory_block* next;
};

}

class heap_allocator final : public base_allocator {
private:
  internal::memory_block* _blocks_head{nullptr};
  usize _total_allocated{0};
  usize _allocation_count{0};

  auto _track_block(internal::memory_block* block) -> void;

  auto _untrack_block(void* ptr) -> bool;

public:
  // binaryskunk: copy semantics are undesired in a memory allocator, i
  // think the reason is pretty obvious...
  heap_allocator(const heap_allocator&) = delete;
  auto operator=(const heap_allocator&) -> heap_allocator& = delete;

  // binaryskunk: move semantics
  heap_allocator(heap_allocator&& other) noexcept
    : _blocks_head{other._blocks_head},
      _total_allocated{other._total_allocated},
      _allocation_count{other._allocation_count} {
    other._blocks_head = nullptr;
    other._total_allocated = 0;
    other._allocation_count = 0;
  }
  auto operator=(heap_allocator&& other) noexcept -> heap_allocator& {
    bool assigning_an_allocator_object_to_itself = this == &other;
    if (assigning_an_allocator_object_to_itself) {
      // binaryskunk: it would not make sense to move an object's data to
      // itself
      return *this;
    }

    this->_blocks_head = other._blocks_head;
    this->_total_allocated = other._total_allocated;
    this->_allocation_count = other._allocation_count;

    other._blocks_head = nullptr;
    other._total_allocated = 0;
    other._allocation_count = 0;

    return *this;
  }

  ~heap_allocator();

  auto alloc(usize n) noexcept -> void*;

  auto free(void* ptr) noexcept -> void;
};
*/

class heap_allocator final : public base_allocator {
 public:
  auto alloc(usize n) noexcept -> void*;

  auto free(void* ptr) noexcept -> void;
};

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
