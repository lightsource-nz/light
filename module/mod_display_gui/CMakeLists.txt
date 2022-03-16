cmake_minimum_required(VERSION 3.12)

project(mod_display_gui)

add_library(mod_display_gui INTERFACE)

target_include_directories(
    mod_display_gui INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

target_sources(
    mod_display_gui INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/paint.c
    ${CMAKE_CURRENT_LIST_DIR}/src/module.c
    )

target_link_libraries(
    mod_display_gui INTERFACE
    mod_display_panel
    mod_display_ic
    mod_display_fonts
    )

    add_executable(
        display_gui_demo
    )
    
target_include_directories(
        display_gui_demo INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/demo
    )
    
target_sources(
        display_gui_demo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/demo/main.c
    )
    
target_link_libraries(
        display_gui_demo
        mod_display_gui
        mod_light_core
        light_bsp
        pico_stdlib
    )
