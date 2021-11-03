cmake_minimum_required(VERSION 3.12)

# MODULE:       mod_display_driver_oled
# DESCRIPTION:  root module for LED driver IC support modules
#               

project(mod_display_driver_oled)

pico_sdk_init()

add_library(mod_display_driver_oled INTERFACE)

target_include_directories(mod_display_driver_oled INTERFACE include)

target_sources(
    mod_display_driver_oled INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/oled_1in3.c
    ${CMAKE_CURRENT_LIST_DIR}/src/oled_2in23.c
    )

target_link_libraries(
    mod_display_driver_oled INTERFACE
    mod_display_board
    pico_stdlib
    )
