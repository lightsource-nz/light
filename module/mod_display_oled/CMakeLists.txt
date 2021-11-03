cmake_minimum_required(VERSION 3.12)

project(mod_display_oled)

add_library(mod_display_oled INTERFACE)
target_include_directories(mod_display_oled INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_sources(
    mod_display_oled INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/config.c
    ${CMAKE_CURRENT_LIST_DIR}/src/paint.c
    ${CMAKE_CURRENT_LIST_DIR}/src/oled_1in3.c
    ${CMAKE_CURRENT_LIST_DIR}/src/oled_2in23.c
)

target_link_libraries(
    mod_display_oled INTERFACE
    pico_stdlib
    hardware_spi
    hardware_i2c
    hardware_pwm
    )
