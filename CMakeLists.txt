cmake_minimum_required(VERSION 3.5)

if(DEFINED CACHE{PATCH_VERSION})
    math(EXPR PATCH_VERSION "${PATCH_VERSION}+1")
    set(PATCH_VERSION ${PATCH_VERSION} CACHE INTERNAL "Patch version")
else()
    set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
endif()

set(PROJECT_VERSION 1.1.${PATCH_VERSION})

# for running on windows
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

project(bite_byte_swapper VERSION ${PROJECT_VERSION})

option(WITH_TEST "Whether to build test" ON)

find_package(fmt REQUIRED)
add_executable(bite_byte_swapper src/main.cpp)

set_target_properties(bite_byte_swapper PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(bite_byte_swapper PUBLIC
    "${CMAKE_BINARY_DIR}"
)

target_link_libraries(bite_byte_swapper
        fmt::fmt)

if(MSVC)
    target_compile_options(bite_byte_swapper PRIVATE
        /W4
    )
    target_compile_options(bite_byte_swapper PRIVATE
        /W4
    )
else()
    target_compile_options(bite_byte_swapper PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bite_byte_swapper RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT ilya.litik@gmail.com)
include(CPack)