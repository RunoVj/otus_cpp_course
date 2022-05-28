cmake_minimum_required(VERSION 3.5)

if(DEFINED CACHE{PATCH_VERSION})
    math(EXPR PATCH_VERSION "${PATCH_VERSION}+1")
    set(PATCH_VERSION ${PATCH_VERSION} CACHE INTERNAL "Patch version")
else()
    set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
endif()

set(PROJECT_VERSION 0.0.${PATCH_VERSION})

# for running on windows
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

project(allocator VERSION ${PROJECT_VERSION})

option(WITH_TEST "Whether to build test" ON)

add_executable(allocator src/allocator.cpp src/main.cpp src/factorial.h)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator PUBLIC
    "${CMAKE_BINARY_DIR}"
)


if(WITH_TEST)
    add_subdirectory(dep/googletest)
    include_directories(${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)

    add_executable(allocator_test
            src/allocator.cpp
            test/allocator_test.cpp)

    set_target_properties(allocator_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(allocator_test
        gtest
        gtest_main
    )
endif()

if(MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(allocator PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(allocator_test PRIVATE
            /W4
        )
    endif()
else()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(allocator_test PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ilya.litik@gmail.com)
include(CPack)

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(allocator_test allocator_test)
endif()