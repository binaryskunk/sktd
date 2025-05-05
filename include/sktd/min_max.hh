// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef INCLUDE_SKTD_MIN_MAX_HH_
#define INCLUDE_SKTD_MIN_MAX_HH_

#include <sktd/attributes.hh>

namespace sktd {

/**
 * Gets the minimum of two values.
 * @param a First value
 * @param b Second value
 * @return Which one is lower
 */
template <class T>
SK_ALWAYS_INLINE inline constexpr auto min(T a, T b) noexcept -> T {
  bool a_is_less_than_or_equal_to_b = a <= b;

  return a_is_less_than_or_equal_to_b ? a : b;
}

/**
 * Gets the maximum of two values.
 * @param a First value
 * @param b Second value
 * @return Which one is greater
 */
template <class T>
SK_ALWAYS_INLINE inline constexpr auto max(T a, T b) noexcept -> T {
  bool a_is_less_than_or_equal_to_b = a <= b;

  return a_is_less_than_or_equal_to_b ? b : a;
}

}  // namespace sktd

#endif  // INCLUDE_SKTD_MIN_MAX_HH_

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
