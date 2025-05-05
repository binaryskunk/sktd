// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_ASSERT_HH
#define SKTD_ASSERT_HH

#include <sktd/build_config.hh>
#include <sktd/attributes.hh>
#include <sktd/utility.hh>
#include <sktd/error.hh>
#include <sktd/exception.hh>

namespace sktd {

SK_ALWAYS_INLINE inline auto panic([[maybe_unused]] const base_error& error)
    -> void {
#ifdef SK_DEBUG
  __asm volatile("int3");
#else
  throw program_exception{error};
#endif
}

template <class T>
SK_ALWAYS_INLINE inline auto panic(
    [[maybe_unused]] const program_exception<T>& exception) -> void {
#ifdef SK_DEBUG
  __asm volatile("int3");
#else
  throw exception;
#endif
}

}  // namespace sktd

#define sk_assert(cond, msg)           \
  if constexpr (!(cond)) {             \
    sktd::panic(assertion_error{msg}); \
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
