cmake_minimum_required(VERSION 3.10)

project(QuickFast-JS)

set(QUICKFAST_SRC ${CMAKE_SOURCE_DIR}/libs/quickfast)
set(XercesC_SRC_DIR ${CMAKE_SOURCE_DIR}/libs/xerces-c)
set(XercesC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/xerces-c/src)

add_subdirectory(libs)
add_subdirectory(tests)