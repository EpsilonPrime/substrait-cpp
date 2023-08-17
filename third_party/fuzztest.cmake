if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    include(FetchContent)

    FetchContent_Declare(
            fuzztest
            SOURCE_DIR "${TOPLEVEL_SOURCE_DIR}/third_party/fuzztest/"
    )

    if(NOT fuzztest_POPULATD)
        add_compile_options(-fsanitize=undefined)
        add_link_options(-fsanitize=undefined)

        add_compile_options(-fsanitize-undefined-strip-path-components=-4)
        set(ENV{UBSAN_OPTIONS} suppressions=${TOPLEVEL_SOURCE_DIR}/ubsan.supp)
        set(ENV{ASAN_OPTIONS} suppressions=${TOPLEVEL_SOURCE_DIR}/asan.supp)

        add_compile_options(-fsanitize=address)
        add_link_options(-fsanitize=address)

        add_compile_options(-fsanitize-ignorelist=${TOPLEVEL_SOURCE_DIR}/sanitize-ignore-list.txt)
        add_link_options(-fsanitize-ignorelist=${TOPLEVEL_SOURCE_DIR}/sanitize-ignore-list.txt)


        FetchContent_MakeAvailable(fuzztest)

        enable_testing()
    endif()
endif ()
