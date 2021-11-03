cmake_minimum_required(VERSION 3.12)

project(mod_display_gui)

add_library(mod_display_gui INTERFACE)
include_directories(include INTERFACE)
target_sources(
    mod_display_gui INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/paint.c
    )

target_link_libraries(
    mod_display_gui INTERFACE
    mod_display_fonts
    )
