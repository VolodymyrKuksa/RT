cmake_minimum_required(VERSION 3.9)
project(rt C)

FILE(GLOB_RECURSE LIBFT_DIR "libft/src/*.c")
add_library(libft STATIC ${LIBFT_DIR})

FILE(GLOB_RECURSE LIBVEC_DIR "libvec/src/*.c")
add_library(libvec STATIC ${LIBVEC_DIR} libvec/src/clvec_add.c)

include_directories(${PROJECT_SOURCE_DIR}/frameworks/SDL2.framework/Headers includes
        ${PROJECT_SOURCE_DIR}/frameworks/SDL2_image.framework/Headers
        libft/includes libvec/includes)

find_library(OPENCL OpenCL)

add_executable(rt includes/rt_types.h includes/rt.h src/main.c src/read_file.c
        src/sdl_utils.c src/scene_init.c src/cl_initialization.c src/cl_exec.c src/keyboard_events.c includes/keys.h src/movement_events.c src/rotate.c)

target_link_libraries(rt ${SDL2_LIBRARY} ${OPENCL} libft libvec
        ${SDL} "-F ${PROJECT_SOURCE_DIR}/frameworks -framework SDL2"
        ${SDL2_IMG} "-rpath ${PROJECT_SOURCE_DIR}/frameworks -framework SDL2_image")

target_compile_definitions(rt PUBLIC CLION_BUILD)