cmake_minimum_required(VERSION 3.12)

project(light_bsp C ASM)

add_library(light_bsp INTERFACE)

target_include_directories(
    light_bsp INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

target_sources(
    light_bsp INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/board.c
    )

target_link_libraries(
    light_bsp INTERFACE
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    )
