cmake_minimum_required(VERSION 3.9)
project(rt C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_library(OPENCL OpenCL)

add_executable(rt main.c)
target_link_libraries(rt ${SDL2_LIBRARY} ${OPENCL})