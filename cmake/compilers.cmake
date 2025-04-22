# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
# See end of file for extended copyright information.

include_guard()

if (CMAKE_C_COMPILER_ID STREQUAL "Clang"
    OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(USING_CLANG TRUE)
elseif (CMAKE_C_COMPILER_ID STREQUAL "GNU"
    OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(USING_GCC TRUE)
elseif (CMAKE_C_COMPILER_ID STREQUAL "MSVC"
    OR CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  set(USING_MSVC TRUE)
else()
  message(STATUS "Building with unsupported compiler ! :c")
endif()

# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
#
# This file is part of cpp-boilerplate and is licensed under the
# BinarySkunk's Public License (BSPL), version 1, as published by
# Lavínia "BinarySkunk" Rodrigues.
#
# You should have received a copy of the BSPL along with this program.
# If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
