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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(matrix VERSION ${PROJECT_VERSION})

option(WITH_TEST "Whether to build test" ON)

include(FetchContent)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

add_executable(matrix src/main.cpp)
target_link_libraries(matrix fmt::fmt)

if(WITH_TEST)
    FetchContent_Declare(googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG main
    )
    FetchContent_MakeAvailable(googletest)
    include_directories(${gtest_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)

    add_executable(matrix_test test/matrix_test.cpp)

    set_target_properties(matrix_test PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(matrix_test
        gtest
        gtest_main
    )

    enable_testing()
    add_test(matrix_test matrix_test)
endif()

if(MSVC)
    target_compile_options(matrix PRIVATE
            /W4)
    target_compile_options(matrix PRIVATE
            /W4)
    if(WITH_GOOGLE_TEST)
        target_compile_options(matrix_test PRIVATE
            /W4)
    endif()
else()
    target_compile_options(matrix PRIVATE
        -Wall -Wextra -pedantic -Werror)
    if(WITH_GOOGLE_TEST)
        target_compile_options(matrix_test PRIVATE
            -Wall -Wextra -pedantic -Werror)
    endif()
endif()

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ilya.litik@gmail.com)
include(CPack)
