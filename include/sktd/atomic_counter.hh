// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef INCLUDE_SKTD_ATOMIC_COUNTER_HH_
#define INCLUDE_SKTD_ATOMIC_COUNTER_HH_

namespace sktd {
namespace sync {

template <class T>
class atomic_counter final {
 private:
  T _value;

 public:
  atomic_counter() : _value{T{}} {}

  explicit atomic_counter(T initial) : _value{initial} {}

  auto increment() -> T;

  auto decrement() -> T;

  auto load() const -> T;
};

}  // namespace sync
}  // namespace sktd

#endif  // INCLUDE_SKTD_ATOMIC_COUNTER_HH_

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
