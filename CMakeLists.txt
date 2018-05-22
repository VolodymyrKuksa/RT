cmake_minimum_required(VERSION 3.9)
project(rt C)

FILE(GLOB_RECURSE LIBFT_DIR "libft/src/*.c")
add_library(libft STATIC ${LIBFT_DIR})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} libft/includes)

find_library(OPENCL OpenCL)

add_executable(rt src/main.c)
target_link_libraries(rt ${SDL2_LIBRARY} ${OPENCL} libft)