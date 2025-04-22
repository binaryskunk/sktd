# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
# See end of file for extended copyright information.

include_guard()

option(WARNINGS_AS_ERRORS "Treat compiler warnings as errors." ON)

include(cmake/compilers.cmake)

set(
  GCC_CLANG_BASE_WARNINGS
  -Wall
  -Wextra
  -Wpedantic
)
set(
  MSVC_BASE_WARNINGS
  /W4
)

function(set_target_warnings target)
  cmake_parse_arguments(
    PARSE_ARGV
    1
    WARNINGS
    ""
    "TARGET"
    "MSVC;CLANG;GCC"
  )

  if (USING_MSVC)
    set(warnings ${WARNINGS_MSVC})
  elseif (USING_CLANG)
    set(warnings ${WARNINGS_CLANG})
  elseif (USING_GCC)
    set(warnings ${WARNINGS_GCC})
  endif()

  target_compile_options(
    ${target} PRIVATE
    $<$<COMPILE_LANGUAGE:C,CXX>:${warnings}>
  )
endfunction()

function(set_default_warnings target)
  set_target_warnings(
    ${target}
    MSVC ${MSVC_BASE_WARNINGS}
    CLANG ${GCC_CLANG_BASE_WARNINGS}
    GCC ${GCC_CLANG_BASE_WARNINGS}
  )

  if (WARNINGS_AS_ERRORS)
    set_target_warnings(
      ${target}
      MSVC "/WX"
      CLANG "-Werror"
      GCC "-Werror"
    )
  endif()
endfunction()

# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
#
# This file is part of cpp-boilerplate and is licensed under the
# BinarySkunk's Public License (BSPL), version 1, as published by
# Lavínia "BinarySkunk" Rodrigues.
#
# You should have received a copy of the BSPL along with this program.
# If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
