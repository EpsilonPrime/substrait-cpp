# SPDX-License-Identifier: Apache-2.0

if(NOT BUILD_SUBDIR_NAME EQUAL "release")
  message(
    SEND_ERROR,
    "The planloader library does not work in Debug mode due to its dependencies."
  )
endif()

add_library(planloader SHARED planloader.cpp)

add_dependencies(planloader substrait_io)
target_link_libraries(planloader substrait_io)

install(
  TARGETS planloader
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCDIR})

add_library(planloader_jni SHARED planloader_jni.cpp)

add_dependencies(planloader_jni planloader)
target_link_libraries(planloader_jni planloader jni_hpp)

install(
  TARGETS planloader_jni
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_INCDIR})
# MEGAHACK -- Are there any headers we need this declaration for?

if(${SUBSTRAIT_CPP_BUILD_TESTING})
  add_subdirectory(tests)
endif()
