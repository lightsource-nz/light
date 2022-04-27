cmake_minimum_required(VERSION 3.12)

# MODULE:       mod_display_ic
# DESCRIPTION:  Module defining a generic API for display driver ICs

project(mod_display_ic)

pico_sdk_init()

add_library(mod_display_ic INTERFACE)

target_sources(
    mod_display_ic INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/module.c
    ${CMAKE_CURRENT_LIST_DIR}/src/sh1107.c
    )

target_include_directories(
    mod_display_ic INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries(
    mod_display_ic INTERFACE
    mod_light_core
    light_bsp
    pico_stdlib
    )

    add_executable(
        display_ic_demo
    )
    
    target_include_directories(
        display_ic_demo INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/demo
    )
    
    target_sources(
        display_ic_demo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/demo/main.c
    )
    
    target_link_libraries(
        display_ic_demo
        mod_display_ic
        mod_light_core
        light_bsp
        pico_stdlib
    )
    