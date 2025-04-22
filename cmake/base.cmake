# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
# See end of file for extended copyright information.

include_guard()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

if (NOT CMAKE_BUILD_TYPE)
  message(STATUS "No build type specified ! Defaulting to Debug ...")
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type." FORCE)
endif()

set_property(
  CACHE
    CMAKE_BUILD_TYPE
  PROPERTY
    STRINGS
      "Debug"
      "Release"
      "RelWithDebInfo"
      "MinSizeRel"
)

# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
#
# This file is part of cpp-boilerplate and is licensed under the
# BinarySkunk's Public License (BSPL), version 1, as published by
# Lavínia "BinarySkunk" Rodrigues.
#
# You should have received a copy of the BSPL along with this program.
# If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
