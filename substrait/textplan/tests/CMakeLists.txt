find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

INCLUDE_DIRECTORIES(${PROTO_INCLUDE_DIR} ${substrait_textplan_INCLUDE_DIRS})
add_executable(
        textplan_conversion_test
        BinaryToTextPlanConversionTest.cpp)


add_dependencies(textplan_conversion_test substrait_textplan)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH TEXTPLAN_SOURCE_DIR)

add_test(
        NAME textplan_conversion_test
        COMMAND textplan_conversion_test
        WORKING_DIRECTORY ${TEXTPLAN_SOURCE_DIR})

target_link_libraries(
        textplan_conversion_test
        substrait_common
        substrait_textplan
        ${PROTOBUF_LIBRARIES}
        proto
        gtest
        gtest_main)
