cmake_minimum_required(VERSION 3.12)

# MODULE:       mod_display_fonts
# DESCRIPTION:  fonts to render text to a dot-matrix display

# Eventually this will be a facade over a collection of screen font modules.
# For now, it's just a monolithic module containing the English and Chinese
# screen fonts that we do have.
project(mod_display_fonts)

pico_sdk_init()

add_library(mod_display_fonts INTERFACE)

target_sources(
    mod_display_fonts INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/font8.c
    ${CMAKE_CURRENT_LIST_DIR}/src/font12.c
    ${CMAKE_CURRENT_LIST_DIR}/src/font12CN.c
    ${CMAKE_CURRENT_LIST_DIR}/src/font16.c
    ${CMAKE_CURRENT_LIST_DIR}/src/font20.c
    ${CMAKE_CURRENT_LIST_DIR}/src/font24.c
    ${CMAKE_CURRENT_LIST_DIR}/src/font24CN.c
)

target_include_directories(
    mod_display_fonts INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

target_link_libraries(
    mod_display_fonts INTERFACE
    pico_stdlib
    )

add_executable(
        display_fonts_demo
    )
    
target_include_directories(
        display_fonts_demo INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/demo
    )
    
target_sources(
        display_fonts_demo PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/demo/main.c
    )
    
target_link_libraries(
        display_fonts_demo
        mod_display_fonts
        mod_display_ic
        mod_light_core
        light_bsp
        pico_stdlib
    )
