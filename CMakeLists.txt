# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
# See end of file for extended copyright information.

cmake_minimum_required(VERSION 3.21)
project(
  sktd
  VERSION 1.0.0
  LANGUAGES CXX
)

option(BUILD_TESTS "Whether to build unit tests." ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/base.cmake)
include(cmake/utils.cmake)
include(cmake/warnings.cmake)

set(PROJECT_SOURCES
  source/allocator.cc
  source/atomic_counter.cc
  source/result.cc
  source/string.cc
)

set(TESTS_SOURCES
)

add_library(${PROJECT_NAME} STATIC
  ${PROJECT_SOURCES}
)

target_compile_features(
  ${PROJECT_NAME} PRIVATE
  cxx_std_20
)

target_include_directories(
  ${PROJECT_NAME} PRIVATE
  ${CMAKE_SOURCE_DIR}/include
)

setup_libraries(${PROJECT_NAME})
set_default_warnings(${PROJECT_NAME})

#if (BUILD_TESTS)
  #setup_tests(${PROJECT_SOURCES} ${TESTS_SOURCES})
#endif()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  find_program(CCACHE_PROGRAM ccache)
  if (CCACHE_PROGRAM)
    message(STATUS "CCache found !")

    set_target_properties(
      ${PROJECT_NAME} PROPERTIES
      CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
      CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}"
    )
  endif()

  message(STATUS "Enabling sanitizers ...")
  set(SANITIZER_FLAGS -fno-omit-frame-pointer -fsanitize=address,undefined)
  if (NOT APPLE)
    set(SANITIZER_FLAGS ${SANITIZER_FLAGS},leak)
  endif()

endif()

# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
#
# This file is part of sktd and is licensed under the
# BinarySkunk's Public License (BSPL), version 1, as published by
# Lavínia "BinarySkunk" Rodrigues.
#
# You should have received a copy of the BSPL along with this program.
# If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
