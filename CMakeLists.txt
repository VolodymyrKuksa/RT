cmake_minimum_required(VERSION 3.9)
project(rt C)

FILE(GLOB_RECURSE LIBFT_DIR "libft/src/*.c")
add_library(libft STATIC ${LIBFT_DIR})

FILE(GLOB_RECURSE LIBVEC_DIR "libvec/src/*.c")
add_library(libvec STATIC ${LIBVEC_DIR} libvec/src/vec_print.c)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")
find_package(SDL2 REQUIRED)

include_directories(/Library/Frameworks/SDL2.framework/Headers/ includes libft/includes libvec/includes)

find_library(OPENCL OpenCL)

add_executable(rt includes/rt_types.h includes/rt.h src/main.c src/read_file.c)
target_link_libraries(rt ${SDL2_LIBRARY} ${OPENCL} libft libvec)