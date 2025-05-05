// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_UTILITY_HH
#define SKTD_UTILITY_HH

#include <sktd/type_traits.hh>

namespace sktd {

template <class T>
constexpr auto forward(remove_reference_t<T>& t) noexcept -> T&& {
  return static_cast<T&&>(t);
}

template <class T>
constexpr auto move(T&& t) noexcept -> remove_reference_t<T>&& {
  return static_cast<remove_reference_t<T>&&>(t);
}

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
