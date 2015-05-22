cmake_minimum_required(VERSION 3.1)

# NAME
project(pFlight)

# VERSION
set(PFLIGHT_VERSION "0.1.0")

set(PFLIGHT_VERSION_MAJOR 0)
set(PFLIGHT_VERSION_MINOR 1)
set(PFLIGHT_VERSION_PATCH 0)

# REQUIRED LIBRARIES
FIND_PACKAGE(OpenSceneGraph)

# and here we go

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

configure_file(
  "${PROJECT_SOURCE_DIR}/include/pflight_config.hpp.in"
  "${PROJECT_BINARY_DIR}/include/pflight_config.hpp"
  )

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_BINARY_DIR}/include/")

add_subdirectory(${PROJECT_SOURCE_DIR}/src/)

