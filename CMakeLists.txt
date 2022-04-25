cmake_minimum_required(VERSION 3.5)

if (DEFINED CACHE{PATCH_VERSION})
    math(EXPR PATCH_VERSION "${PATCH_VERSION}+1")
    set(PATCH_VERSION ${PATCH_VERSION} CACHE INTERNAL "Patch version")
else()
    set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
endif()

set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(ip_filter VERSION ${PROJECT_VESRION})

option(WITH_TEST "Whether to build test" ON)

configure_file(src/version.h.in version.h)

add_executable(ip_filter_cli src/ip_filter.cpp)

set_target_properties(ip_filter_cli PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(ip_filter_cli PUBLIC
    "${CMAKE_BINARY_DIR}"
)


if(WITH_TEST)
    add_subdirectory(dep/googletest)
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    add_executable(g_test_version test/g_test_version.cpp)

    set_target_properties(g_test_version PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(g_test_version
        gtest
        gtest_main
        ip_filter
    )
endif()

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
            /W4
        )
    endif()
    if(WITH_GOOGLE_TEST)
        target_compile_options(g_test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic #-Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(g_test_version PRIVATE
            -Wall -Wextra -pedantic #-Werror
        )
    endif()
endif()

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(boost_test_version boost_test_version)
endif()

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(g_test_version g_test_version)
endif()