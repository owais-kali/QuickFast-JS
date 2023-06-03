cmake_minimum_required(VERSION 3.10)

project(QuickFast-JS)

option(QUICKFAST_SRC "Set QUICKFAST_SRC variable with path to QUICKFAST Source")
if(NOT QUICKFAST_SRC)
    set(QUICKFAST_SRC ${CMAKE_SOURCE_DIR}/libs/quickfast)
endif()

add_subdirectory(libs)