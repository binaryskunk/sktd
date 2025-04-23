// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#include <sktd/allocator.hh>

#include <sktd/type_aliases.hh>
#include <sktd/utility.hh>

namespace sktd {
namespace mem {

/*
namespace {

auto _create_memory_block(usize size)
  -> internal::memory_block* {
  auto block = static_cast<internal::memory_block*>(
      operator new(sizeof(internal::memory_block)));
  bool failed_to_allocate_block = !block;
  if (failed_to_allocate_block) {
    // TODO: bad alloc
  }

  block->ptr = operator new(size);

  bool failed_to_allocate_actual_data = !block->ptr;
  if (failed_to_allocate_actual_data) {
    operator delete(block);

    // TODO: bad alloc
  }

  block->size = size;
  block->next = nullptr;

  return block;
}

}

auto heap_allocator::_track_block(internal::memory_block* block) -> void {
  bool blocks_tracking_list_unintialized = !this->_blocks_head;
  if (blocks_tracking_list_unintialized) {
    this->_blocks_head = block;
  } else {
    block->next = this->_blocks_head;
    this->_blocks_head = block;
  }

  this->_total_allocated += block->size;
  this->_allocation_count++;
}

auto heap_allocator::_untrack_block(void* ptr) -> bool {
  bool blocks_tracking_list_unintialized = !this->_blocks_head;
  if (blocks_tracking_list_unintialized) {
    return false;
  }

  // binaryskunk: this is a special case and must be handled different
  bool is_head_of_the_list = this->_blocks_head->ptr == ptr;
  if (is_head_of_the_list) {
    internal::memory_block* found_block = this->_blocks_head;
    this->_blocks_head = this->_blocks_head->next;

    this->_total_allocated -= found_block->size;
    this->_allocation_count--;

    operator delete(found_block);

    return true;
  }

  // binaryskunk: standard linked list traversing
  internal::memory_block* current = this->_blocks_head;
  while (current->next) {
    bool next_block_is_the_one_we_are_looking_for = current->next->ptr == ptr;
    if (next_block_is_the_one_we_are_looking_for) {
      internal::memory_block* found_block = current->next;
      current->next = found_block->next;

      this->_total_allocated -= found_block->size;
      this->_allocation_count--;

      operator delete(found_block);

      return true;
    }
  }

  return false;
}

heap_allocator::~heap_allocator() {
  while (this->_blocks_head) {
    internal::memory_block* current_block = this->_blocks_head;
    this->_blocks_head = this->_blocks_head->next;

    operator delete(current_block->ptr);
    operator delete(current_block);
  }
}

auto heap_allocator::alloc(usize n) noexcept -> void* {
  if (n == 0) {
    return nullptr;
  }

  internal::memory_block* block = _create_memory_block(false);
}

auto heap_allocator::free(void* ptr) noexcept -> void {
}*/

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
    ptr = nullptr;
  } catch (...) {
    // purposelly no-op
  }
}

}
}

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
