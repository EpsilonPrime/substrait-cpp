# SPDX-License-Identifier: Apache-2.0

include(FetchContent)

set(FUZZTEST_REPO_BRANCH "origin/main" CACHE STRING "FuzzTest repository branch.")
message("Building fuzztest at branch " ${FUZZTEST_REPO_BRANCH})

FetchContent_Declare(
        fuzztest
        GIT_REPOSITORY  https://github.com/google/fuzztest.git
        GIT_TAG         ${FUZZTEST_REPO_BRANCH}
)
FetchContent_MakeAvailable(fuzztest)

enable_testing()
include(GoogleTest)


option(SUBSTRAIT_CPP_FUZZTEST_TESTING
       "Enable substrait-cpp textplan fuzztest tests." OFF)

if(${SUBSTRAIT_CPP_FUZZTEST_TESTING})
  fuzztest_setup_fuzzing_flags()

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
          #gmock
          #gtest
          #gtest_main
  )

  link_fuzztest(substrait_textplan_fuzz_test)
  gtest_discover_tests(substrait_textplan_fuzz_test)
else()

  message(
    STATUS
      "Fuzz testing is turned off.  Add SUBSTRAIT_CPP_FUZZTEST_TESTING=on to enable."
  )

endif()
