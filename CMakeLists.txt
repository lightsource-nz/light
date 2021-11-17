cmake_minimum_required(VERSION 3.12)
include(pico_sdk_import.cmake)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

project(light C ASM)

if(NOT DEFINED LIGHT_BOARD_ID)
    message(FATAL_ERROR "LIGHT_BOARD_ID must be defined")
endif()

add_library(light INTERFACE)

add_subdirectory(board/${LIGHT_BOARD_ID})

# add all local modules unconditionally
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_LIST_DIR}/module)
FOREACH(subdir ${SUBDIRS})
  ADD_SUBDIRECTORY(module/${subdir})
ENDFOREACH()

target_link_libraries(light INTERFACE light_bsp)
