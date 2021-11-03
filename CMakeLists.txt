cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

project(light C ASM)

if(NOT DEFINED LIGHT_BOARD_ID)
    message(FATAL_ERROR "LIGHT_BOARD_ID must be defined")
endif()

add_library(light INTERFACE)

add_subdirectory(board/${LIGHT_BOARD_ID})

add_subdirectory(module/mod_light_core)
add_subdirectory(module/mod_display_board)
add_subdirectory(module/mod_display_driver)
add_subdirectory(module/mod_display_oled)

target_link_libraries(light INTERFACE light_bsp)
