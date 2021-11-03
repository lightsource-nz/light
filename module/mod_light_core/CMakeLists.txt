cmake_minimum_required(VERSION 3.12)

project(mod_light_core C CXX ASM)
pico_sdk_init()

add_library(mod_light_core INTERFACE)

target_include_directories(
    mod_light_core INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

target_sources(
    mod_light_core INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/module.c
    )

add_executable(
    light_core_demo
)

target_include_directories(
    light_core_demo INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(
    light_core_demo PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/demo/main.c
)

target_link_libraries(
    light_core_demo
    mod_light_core
    pico_stdlib
)
