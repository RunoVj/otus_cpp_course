cmake_minimum_required(VERSION 3.5)

add_subdirectory(gof_patterns)
add_subdirectory(mvc_graphic_editor)

add_executable(vector_graphic_editor
        main.cpp
        )

target_link_libraries(vector_graphic_editor PRIVATE mvc_graphic_editor)