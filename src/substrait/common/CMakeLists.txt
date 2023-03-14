# SPDX-License-Identifier: Apache-2.0

find_package(fmt)

add_library(substrait_common Exceptions.cpp)

target_link_libraries(substrait_common fmt::fmt-header-only)

add_library(
        substrait_convert
        Convert.cpp)

add_dependencies(
        substrait_convert
        substrait_proto
        substrait_textplan_converter)

target_link_libraries(
        substrait_convert
        substrait_proto)

if(${SUBSTRAIT_CPP_BUILD_TESTING})
    add_subdirectory(tests)
endif ()
