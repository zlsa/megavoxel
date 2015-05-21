cmake_minimum_required(VERSION 3.0)

# NAME
project(pFlight)

# VERSION
set(PFLIGHT_VERSION "0.1.0")

set(PFLIGHT_VERSION_MAJOR 0)
set(PFLIGHT_VERSION_MINOR 1)
set(PFLIGHT_VERSION_PATCH 0)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

configure_file(
  "${PROJECT_SOURCE_DIR}/include/pflight_config.hpp.in"
  "${PROJECT_BINARY_DIR}/include/pflight_config.hpp"
  )

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_BINARY_DIR}/include/")

add_executable(pflight main.cpp)

install(TARGETS pflight DESTINATION bin)
