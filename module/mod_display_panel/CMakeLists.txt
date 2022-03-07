cmake_minimum_required(VERSION 3.12)

# MODULE:       mod_display_panel
# DESCRIPTION:  Module defining a generic API for passive OLED display panels

project(mod_display_panel)

pico_sdk_init()

add_library(mod_display_panel INTERFACE)

target_sources(
    mod_display_panel INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/module.c
    ${CMAKE_CURRENT_LIST_DIR}/src/panel.c
    )

target_include_directories(
    mod_display_panel INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    mod_display_panel INTERFACE
    mod_display_ic
    mod_light_core
    pico_stdlib
    )

    add_executable(
        display_panel_demo
    )
    
    target_include_directories(
        display_panel_demo INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/demo
    )
    
    target_sources(
        display_panel_demo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/demo/main.c
    )
    
    target_link_libraries(
        display_panel_demo
        mod_display_panel
        mod_light_core
        light_bsp
        pico_stdlib
    )
    