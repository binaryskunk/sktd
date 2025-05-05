// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_ALLOCATOR_HH
#define SKTD_ALLOCATOR_HH

#include <sktd/type_aliases.hh>
#include <sktd/type_traits.hh>
#include <sktd/error.hh>
#include <sktd/result.hh>

namespace sktd {
namespace mem {

class base_allocator {
 public:
  virtual auto alloc(usize n) noexcept -> void* = 0;

  virtual auto free(void* ptr) noexcept -> void = 0;
};

template <class T>
concept valid_allocator = derived_from<remove_cvref_t<T>, base_allocator>;

class heap_allocator final : public base_allocator {
 public:
  auto alloc(usize n) noexcept -> void*;

  auto free(void* ptr) noexcept -> void;
};

// TODO(binaryskunk): refactor the below class and make it a base class
// for other pool allocator's error classes
class pool_allocator_error final : public base_error {
 private:
  const char8* _msg;

 public:
  explicit pool_allocator_error(const char8* msg) : _msg{msg} {}

  auto what() const -> const char8*;
};

template <valid_allocator Allocator, class T>
class pool_allocator final {
 private:
  T* _pool{nullptr};
  u64 _capacity{};
  u64 _counter{};
  Allocator _allocator{};

 public:
  explicit pool_allocator(u64 n) : _capacity{n} {
    this->_pool = this->_allocator.alloc(sizeof(T) * n);
  }

  ~pool_allocator() { this->_allocator.free(this->_pool); }

  auto alloc() noexcept -> sktd::result<T*, pool_allocator_error>;

  auto free(const T* ptr) noexcept -> void;
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
