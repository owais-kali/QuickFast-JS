cmake_minimum_required(VERSION 3.10)

project(QuickFast-JS)

option(QUICKFAST_SRC "Set QUICKFAST_SRC variable with path to QUICKFAST Source")
if(NOT QUICKFAST_SRC)
    set(QUICKFAST_SRC ${CMAKE_SOURCE_DIR}/libs/quickfast)
endif()

set(BOOST_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/boost)

#include_directories(${BOOST_SOURCE_DIR}/libs/config/include)
#include_directories(${BOOST_SOURCE_DIR}/libs/date_time/include)
#
#include_directories(/usr/include/x86_64-linux-gnu/c++/11)

set(Boost_INCLUDE_DIR /usr/include)
find_package(Boost REQUIRED )

set(XercesC_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/libs/xerces-c/src)
add_subdirectory(libs)
add_subdirectory(tests)