// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_ERROR_HH
#define SKTD_ERROR_HH

#include <sktd/type_aliases.hh>
#include <sktd/utility.hh>
#include <sktd/type_traits.hh>

namespace sktd {

class base_error {
 public:
  constexpr base_error() = default;

  virtual auto what() const -> const char8* = 0;
};

template <class T>
concept valid_error = derived_from<base_error, T>;

class assertion_error final : public base_error {
 private:
  const char8* _msg;

 public:
  assertion_error() = delete;

  constexpr explicit assertion_error(const char8* msg) : _msg{msg} {}

  auto what() const -> const char8* { return this->_msg; }
};

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
