cmake_minimum_required(VERSION 3.12)

project(light_bsp C ASM)

add_library(light_bsp INTERFACE)

target_link_libraries(light_bsp INTERFACE pico_stdlib)
