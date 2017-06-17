cmake_minimum_required(VERSION 3.1)

# NAME
project(megavoxel)

# VERSION
set(MEGAVOXEL_VERSION "0.1.0")

set(MEGAVOXEL_VERSION_MAJOR 0)
set(MEGAVOXEL_VERSION_MINOR 1)
set(MEGAVOXEL_VERSION_PATCH 0)

# REQUIRED LIBRARIES

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)
pkg_search_module(GLEW REQUIRED glew)

include_directories(${GLM_INCLUDE_DIRS})

# Boost
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost 1.40
  COMPONENTS
  filesystem
  REQUIRED)

# and here we go

set(CMAKE_BUILD_TYPE "Release")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wno-reorder")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

configure_file(
  "${PROJECT_SOURCE_DIR}/include/megavoxel_config.hpp.in"
  "${PROJECT_BINARY_DIR}/include/megavoxel_config.hpp"
  )

include_directories(${PROJECT_SOURCE_DIR}/include/)
include_directories(${PROJECT_BINARY_DIR}/include/)
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIRS})

add_subdirectory("${PROJECT_SOURCE_DIR}/src/")

install(FILES data/system_config DESTINATION share/megavoxel RENAME config)
install(DIRECTORY data/shaders DESTINATION share/megavoxel)
