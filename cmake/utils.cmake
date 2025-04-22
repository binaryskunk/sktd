# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
# See end of file for extended copyright information.

include_guard()

set(_LIBS_DIR ${CMAKE_SOURCE_DIR}/3rd-party)

function(setup_libraries target)
  if (UNIX)
    target_link_libraries(${target} PRIVATE m ${CMAKE_DL_LIBS})
  endif()
endfunction()

function(setup_tests sources tests)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  add_executable(
    unit_test
    ${tests}
    ${sources}
  )
  target_include_directories(unit_test PRIVATE ${CMAKE_SOURCE_DIR}/include)
  target_link_libraries(
    unit_test
    GTest::gtest_main
  )

  include(GoogleTest)
  gtest_discover_tests(unit_test)
endfunction()

# Copyright (c) 2025 Lavínia "BinarySkunk" Rodrigues
#
# This file is part of cpp-boilerplate and is licensed under the
# BinarySkunk's Public License (BSPL), version 1, as published by
# Lavínia "BinarySkunk" Rodrigues.
#
# You should have received a copy of the BSPL along with this program.
# If not, see <https://kernel32.xyz/licenses/bspl/v1/>.
