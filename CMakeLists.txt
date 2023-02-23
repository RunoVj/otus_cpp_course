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

add_subdirectory(src)

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
