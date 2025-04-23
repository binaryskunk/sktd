// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#include <sktd/atomic_counter.hh>

namespace sktd {
namespace sync {

template <class T>
auto atomic_counter<T>::increment() -> T {
#if defined(__GNUC__) || defined(__clang__)
  return __atomic_add_fetch(&this->_value, 1, __ATOMIC_SEQ_CST);
#elif defined(_MSC_VER)
  return _InterlockedIncrement(
      reinterpret_cast<volatile long*>(&this->_value));
#else
  #error "unsupported compiler for atomic operations"
#endif
}

template <class T>
auto atomic_counter<T>::decrement() -> T {
#if defined(__GNUC__) || defined(__clang__)
  return __atomic_sub_fetch(&this->_value, 1, __ATOMIC_SEQ_CST);
#elif defined(_MSC_VER)
  return _InterlockedDecrement(
      reinterpret_cast<volatile long*>(&this->_value));
#else
  #error "unsupported compiler for atomic operations"
#endif
}

template <class T>
auto atomic_counter<T>::load() const -> T {
#if defined(__GNUC__) || defined(__clang__)
  T result;
  __atomic_load(&this->_value, &result, __ATOMIC_SEQ_CST);

  return result;
#elif defined(_MSC_VER)
  _ReadBarrier();
  T result = this->_value;

  _ReadBarrier();

  return result;
#else
  #error "unsupported compiler for atomic operations"
#endif
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
