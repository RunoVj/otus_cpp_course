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

add_executable(allocator
        src/main.cpp)

set_target_properties(allocator PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator PUBLIC
    "${CMAKE_BINARY_DIR}"
    src/include
)


if(MSVC)
    target_compile_options(allocator PRIVATE
        /W4
    )
    target_compile_options(allocator PRIVATE
        /W4
    )
else()
    target_compile_options(allocator PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ilya.litik@gmail.com)
include(CPack)