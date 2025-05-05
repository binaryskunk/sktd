// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#include <sktd/result.hh>

namespace sktd {

template <class T, class E>
auto result<T, E>::_destroy() -> void {
  if (this->_has_value) {
    this->_value.~T();
  } else {
    this->_error.~E();
  }
}

template <class T, class E>
result<T, E>::~result() {
  this->_destroy();
}

template <class T, class E>
constexpr auto result<T, E>::operator=(const result& other) -> result& {
  bool this_and_other_are_the_same = this == &other;
  if (this_and_other_are_the_same) {
    return *this;
  }

  bool both_have_value = this->_has_value && other._has_value;
  bool both_have_error = !this->_has_value && !other._has_value;
  bool only_other_has_error = this->_has_value && !other->_has_value;

  if (both_have_value) {
    this->_value = other._value;
  } else if (both_have_error) {
    this->_error = other._error;
  } else if (only_other_has_error) {
    this->_destroy();

    new (&this->_error) E(other._error);
    this->_has_value = false;
  } else {
    this->_destroy();

    new (&this->_value) T(other._value);
    this->_has_value = true;
  }

  return *this;
}

template <class T, class E>
constexpr auto result<T, E>::operator=(result&& other) -> result& {
  bool this_and_other_are_the_same = this == &other;
  if (this_and_other_are_the_same) {
    return *this;
  }

  bool both_have_value = this->_has_value && other._has_value;
  bool both_have_error = !this->_has_value && !other._has_value;
  bool only_other_has_error = this->_has_value && !other->_has_value;

  if (both_have_value) {
    this->_value = move(other._value);
  } else if (both_have_error) {
    this->_error = move(other._error);
  } else if (only_other_has_error) {
    this->_destroy();

    new (&this->_error) E(move(other._error));
    this->_has_value = false;
  } else {
    this->_destroy();

    new (&this->_value) T(move(other._value));
    this->_has_value = true;
  }

  return *this;
}

template <class T, class E>
constexpr auto result<T, E>::is_ok() const noexcept -> bool {
  return this->_has_value;
}

template <class T, class E>
constexpr auto result<T, E>::is_err() const noexcept -> bool {
  return !this->_has_value;
}

template <class T, class E>
constexpr auto result<T, E>::unwrap() const -> const T& {
  if (!this->_has_value) {
    throw bad_result_access<E>(this->_error);
  }

  return this->_value;
}

template <class T, class E>
constexpr auto result<T, E>::unwrap() -> T& {
  if (!this->_has_value) {
    throw bad_result_access<E>(this->_error);
  }

  return this->_value;
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
