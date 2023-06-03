cmake_minimum_required(VERSION 3.10)

project(QuickFast-JS)

option(QUICKFAST_SRC "Set QUICKFAST_SRC variable with path to QUICKFAST Source")
if(NOT QUICKFAST_SRC)
    set(QUICKFAST_SRC ${CMAKE_SOURCE_DIR}/libs/quickfast)
endif()

set(XercesC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/xerces-c/src)
add_subdirectory(libs)
add_subdirectory(tests)