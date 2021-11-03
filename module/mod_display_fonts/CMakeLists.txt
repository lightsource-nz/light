cmake_minimum_required(VERSION 3.12)

# MODULE:       mod_display_fonts
# DESCRIPTION:  fonts to render text to a dot-matrix display

# Eventually this will be a facade over a collection of screen font modules.
# For now, it's just a monolithic module containing the English and Chinese
# screen fonts that we do have.
project(mod_display_fonts)

pico_sdk_init()
include_directories(include)

add_library(mod_display_fonts INTERFACE)

target_link_libraries(
    mod_display_fonts INTERFACE
    pico_stdlib
    )
