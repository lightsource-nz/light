cmake_minimum_required(VERSION 3.12)

project(mod_display_board)

pico_sdk_init()
include_directories(include)

add_library(mod_display_board INTERFACE)

target_include_directories(
    mod_display_board INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src
)

target_sources(
    mod_display_board INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/board.c
    )

target_link_libraries(
    mod_display_board INTERFACE
    pico_stdlib
    hardware_pwm
    )
