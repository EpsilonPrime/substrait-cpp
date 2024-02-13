# SPDX-License-Identifier: Apache-2.0

if(NOT ${ABSL_INCLUDED_WITH_PROTOBUF})
  set(ABSL_PROPAGATE_CXX_STD ON)
  add_subdirectory(abseil-cpp)
endif()

include(datetime.cmake)

add_subdirectory(fmt)
add_subdirectory(googletest)


file(GLOB jni_hpp_includes LIST_DIRECTORIES false jni.hpp/include/jni/*.hpp)
add_library(jni_hpp INTERFACE ${jni_hpp_includes})
target_include_directories(jni_hpp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/jni.hpp/include")
find_package(JNI REQUIRED)
if (JNI_FOUND)
  target_include_directories(jni_hpp INTERFACE ${JNI_INCLUDE_DIRS})
else()
  message(
          SEND_ERROR,
          "Could not find Java SDK for the JNI headers."
  )
endif()

add_subdirectory(protobuf-matchers)

set(YAML_CPP_BUILD_TESTS
    OFF
    CACHE BOOL "Enable testing")
include_directories(yaml-cpp/include)
add_subdirectory(yaml-cpp)
