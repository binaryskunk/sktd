// Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
// See end of file for extended copyright information.

#ifndef SKTD_EXCEPTION_HH
#define SKTD_EXCEPTION_HH

#include <sktd/type_aliases.hh>
#include <sktd/error.hh>

namespace sktd {

template <valid_error E>
struct program_exception final {
  const char8* msg{nullptr};

  program_exception() = delete;

  constexpr program_exception(const E& error)
    : msg{error.msg()}
  {}
};

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
