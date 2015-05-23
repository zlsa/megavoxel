cmake_minimum_required(VERSION 3.1)

# NAME
project(pFlight)

# VERSION
set(PFLIGHT_VERSION "0.1.0")

set(PFLIGHT_VERSION_MAJOR 0)
set(PFLIGHT_VERSION_MINOR 1)
set(PFLIGHT_VERSION_PATCH 0)

# REQUIRED LIBRARIES

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.40
  COMPONENTS
  filesystem
  REQUIRED)

# and here we go

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

configure_file(
  "${PROJECT_SOURCE_DIR}/include/pflight_config.hpp.in"
  "${PROJECT_BINARY_DIR}/include/pflight_config.hpp"
  )

include_directories("${PROJECT_SOURCE_DIR}/include/")
include_directories("${PROJECT_BINARY_DIR}/include/")
include_directories("${GLFW_INCLUDE_DIRS}")

if(Boost_FOUND)
  include_directories("${Boost_INCLUDE_DIRS}")
endif()

add_subdirectory("${PROJECT_SOURCE_DIR}/src/")

install(FILES data/system_config DESTINATION share/pflight RENAME config)
