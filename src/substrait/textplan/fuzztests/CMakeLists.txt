# SPDX-License-Identifier: Apache-2.0

option(SUBSTRAIT_CPP_FUZZTEST_TESTING
       "Enable substrait-cpp textplan fuzztest tests." ON)

if(${SUBSTRAIT_CPP_FUZZTEST_TESTING})
  cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH TEXTPLAN_SOURCE_DIR)
  cmake_path(GET TEXTPLAN_SOURCE_DIR PARENT_PATH SUBSTRAIT_SOURCE_DIR)
  cmake_path(GET SUBSTRAIT_SOURCE_DIR PARENT_PATH SRC_SOURCE_DIR)
  cmake_path(GET SRC_SOURCE_DIR PARENT_PATH TOPLEVEL_SOURCE_DIR)

  include(${TOPLEVEL_SOURCE_DIR}/third_party/fuzztest.cmake)

  fuzztest_setup_fuzzing_flags()

  # MEGAHACK -- These are probably unnecessary as they were requested in fuzztest.cmake.
  add_compile_options(-fsanitize-ignorelist=${TOPLEVEL_SOURCE_DIR}/sanitize-ignore-list.txt)
  add_link_options(-fsanitize-ignorelist=${TOPLEVEL_SOURCE_DIR}/sanitize-ignore-list.txt)

  add_test_case(
          substrait_textplan_fuzz_test
          SOURCES
          FuzzTest.cpp
          EXTRA_LINK_LIBS
          substrait_textplan_converter
          substrait_textplan_loader
          substrait_textplan_normalizer
          substrait_common
          substrait_proto
          parse_result_matchers
          protobuf-matchers
          fmt::fmt-header-only
  )

  link_fuzztest(substrait_textplan_fuzz_test)
  gtest_discover_tests(substrait_textplan_fuzz_test)
else()

  message(
    STATUS
      "Fuzz testing is turned off.  Add SUBSTRAIT_CPP_FUZZTEST_TESTING=on to enable."
  )

endif()
