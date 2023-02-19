cmake_minimum_required(VERSION 3.5)

add_library(mvc_graphic_editor STATIC
        controller/logic.cpp
        controller/button.cpp
        model/db.cpp
        view/ui.cpp
        )

target_include_directories(mvc_graphic_editor PRIVATE
        controller/
        model/
        view/
        )

target_link_libraries(mvc_graphic_editor PUBLIC
        gof_patterns
        )
