// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_RESULT_HH
#define SKTD_RESULT_HH

#include <sktd/type_aliases.hh>
#include <sktd/error.hh>
#include <sktd/type_traits.hh>
#include <sktd/utility.hh>

namespace sktd {

template <class T, class E>
class result;

struct error_result_t {
  explicit constexpr error_result_t() = default;
};
inline constexpr error_result_t error_result;

template <valid_error E>
class bad_result_access final : public base_error {
private:
  E _error;

public:
  explicit bad_result_access(E error)
    : _error{move(error)}
  {}

  auto msg() const noexcept -> const char8* {
    return "tried to unwrap an error result";
  }

  auto error() const noexcept -> const E& {
    return this->_error;
  }

  auto error() noexcept -> E& {
    return this->_error;
  }
};

template <class T, class E>
class result final {
public:
  using value_type = T;
  using error_type = E;

private:
  bool _has_value;

  union {
    T _value;
    E _error;
  };

  auto _destroy() -> void;

public:
  constexpr result()
    requires (is_default_constructible_v<T>)
    : _has_value{true},
      _value{}
  {}

  constexpr result(const result& other)
    requires (is_copy_constructible_v<T> && is_copy_constructible_v<E>)
    : _has_value{other._has_value} {
    if (other._has_value) {
      new (&this->_value) T(other._value);
    } else {
      new (&this->_error) E(other._error);
    }
  }

  constexpr result(result&& other)
    requires (is_move_constructible_v<T> && is_move_constructible_v<E>)
    : _has_value{other._has_value} {
    if (other._has_value) {
      new (&this->_value) T(move(other._value));
    } else {
      new (&this->_error) E(move(other._error));
    }
  }

  template <class U = T>
  constexpr explicit result(U&& value)
    requires (!is_same_v<remove_cvref_t<U>, result<T, E>>
      && !is_same_v<remove_cvref_t<U>, error_result_t>)
    : _has_value{true},
      _value{forward<U>(value)}
  {}

  template <class... Args>
  constexpr explicit result(error_result_t, Args&&... args)
    : _has_value{false},
      _error{forward<Args>(args)...}
  {}

  ~result();


  constexpr auto operator=(const result& other) -> result&;

  constexpr auto operator=(result&& other) -> result&;

  constexpr auto is_ok() const noexcept -> bool;

  constexpr auto is_err() const noexcept -> bool;

  constexpr explicit operator bool() const noexcept {
    return this->_has_value;
  }

  constexpr auto unwrap() const -> const T&;

  constexpr auto unwrap() -> T&;

  template <class U>
  constexpr auto unwrap_or(U&& fallback) const -> T {
    if (this->_has_value) {
      return this->_value;
    }

    return static_cast<T>(forward<U>(fallback));
  }

  template <class U>
  constexpr auto unwrap_or(U&& fallback) -> T {
    if (this->_has_value) {
      return move(this->_value);
    }

    return static_cast<T>(forward<U>(fallback));
  }

  template <class U>
  struct is_result : false_type {};

  template <class V, class G>
  struct is_result<result<V, G>> : true_type {};
};

template <class T, class E>
inline constexpr auto make_ok(T&& value) {
  return result<decay_t<T>, decay_t<E>>(forward<T>(value));
}

template <class T, class E>
inline constexpr auto make_err(E&& error) {
  return result<decay_t<T>, decay_t<E>>(error_result, forward<E>(error));
}

template <class T>
result(T) -> result<T, base_error>;

}

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
