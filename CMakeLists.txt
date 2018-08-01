cmake_minimum_required(VERSION 3.9)
project(RT C)

FILE(GLOB_RECURSE LIBFT_DIR "libft/src/*.c")
add_library(libft STATIC ${LIBFT_DIR})

FILE(GLOB_RECURSE LIBVEC_DIR "libvec/src/*.c")
add_library(libvec STATIC ${LIBVEC_DIR} libvec/src/clvec_sub.c)

FILE(GLOB_RECURSE JSON_DIR "libJSON/*.c")
add_library(lib_json STATIC ${JSON_DIR})

include_directories(${PROJECT_SOURCE_DIR}/frameworks/SDL2.framework/Headers includes
        ${PROJECT_SOURCE_DIR}/frameworks/SDL2_image.framework/Headers
        libft/includes libvec/includes libJSON/include ${PROJECT_SOURCE_DIR}/frameworks/SDL2_ttf.framework/Headers/)

find_library(OPENCL OpenCL)

add_executable(RT includes/rt_types.h includes/rt.h src/server_main.c src/sdl_utils.c
        src/parser/scene_init.c src/cl_initialization.c src/cl_exec.c includes/parser.h
        src/events/keyboard_events.c includes/keys.h src/events/movement_events.c src/events/rotate.c
        src/events/write_png.c src/events/write_ppm.c src/events/window_event.c src/scene_utils.c
        src/events/rot_obj.c src/events/mv_obj.c src/textures/load_texture.c
        includes/rt_textures.h src/textures/compress_texture.c
        src/parser/check_params1.c src/parser/check_params2.c src/parser/default_objs.c src/parser/fill_each_obj.c
        src/parser/init_cam.c src/parser/parse.c src/server-client/thread_pool.c
        src/parser/ftoa.c src/parser/init_cam2.c src/parser/write_to_file.c
        src/parser/write_to_file2.c
        src/parser/write_to_file3.c
        src/parser/write_to_file4.c
        src/parser/write_to_file5.c
        src/parser/default_objs2.c
        src/parser/fill_each_obj2.c
        src/parser/fill_each_obj3.c
        src/parser/fill_each_obj4.c
        src/parser/fill_each_obj5.c
        src/parser/scene_init2.c
        src/parser/scene_init3.c
        src/parser/scene_init4.c
        src/gui/button.c
        src/gui/common_staff.c
        src/gui/controller.c
        src/gui/label.c
        src/gui/menu.c
        src/gui/radio.c
        src/gui/gui.c
        src/handle_events.c
        src/message.c
        includes/gui.h
        src/gui/menu1.c
        src/gui/menu2.c
        src/gui/menu3.c
        src/gui/menu4.c
        src/gui/gui1.c
        includes/server_client.h src/server-client/run_server.c src/main_loop.c src/events/mouse_event.c src/server-client/socket_utils.c src/server-client/tpool_new_msg.c src/server-client/tpool_read_send_msg.c src/server-client/tpool_cleanup.c src/server-client/tpool_client.c src/server-client/tpool_threads.c src/server-client/tpool_client_logic.c src/client_read_data.c src/events/rot_obj2.c src/events/mv_obj2.c includes/gui.h src/message.c src/cl_init_utils.c)

add_executable(client src/client_main.c src/server-client/thread_pool.c src/server-client/run_server.c src/main_loop.c src/server-client/socket_utils.c src/server-client/tpool_new_msg.c src/server-client/tpool_read_send_msg.c src/server-client/tpool_cleanup.c src/server-client/tpool_client.c src/server-client/tpool_threads.c src/server-client/tpool_client_logic.c src/client_read_data.c src/events/rot_obj2.c src/events/mv_obj2.c src/message.c src/cl_init_utils.c)

target_link_libraries(RT ${OPENCL} libft libvec lib_json
        ${SDL} "-F ${PROJECT_SOURCE_DIR}/frameworks -framework SDL2"
        ${SDL2_IMG} "-rpath ${PROJECT_SOURCE_DIR}/frameworks -framework SDL2_image")

target_link_libraries(client libft)

target_compile_definitions(RT PUBLIC CLION_BUILD)