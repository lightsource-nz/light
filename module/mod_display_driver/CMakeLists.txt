cmake_minimum_required(VERSION 3.12)

# MODULE:       mod_display_driver
# DESCRIPTION:  Module defining a generic API for display driver ICs

project(mod_display_driver)

pico_sdk_init()
include_directories(include)

add_library(mod_display_driver INTERFACE)

target_sources(
    mod_display_driver INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/module.c
    )

target_link_libraries(
    mod_display_driver INTERFACE
    pico_stdlib
    )
