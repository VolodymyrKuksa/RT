/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 18:47:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/22 18:47:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <OpenCL/opencl.h>
# include <SDL.h>
# include <SDL_image.h>
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "libvec.h"
# include "get_next_line.h"
# include "rt_textures.h"
# include <netinet/in.h>
# include "server_client.h"
# include "rt_types.h"
# include "keys.h"
# include "parser.h"
# include "json.h"

# ifdef CLION_BUILD
# define KERNEL_PATH0 "../src/cl_files/kernel_source.cl"
# define KERNEL_PATH1 "../src/cl_files/intersections_and_normals.cl"
# define KERNEL_PATH2 "../src/cl_files/texture_mapping.cl"
# define KERNEL_PATH3 "../src/cl_files/material.cl"
# define KERNEL_INC_DIR "-I ../includes"
# else
# define KERNEL_PATH0 "src/cl_files/kernel_source.cl"
# define KERNEL_PATH1 "src/cl_files/intersections_and_normals.cl"
# define KERNEL_PATH2 "src/cl_files/texture_mapping.cl"
# define KERNEL_PATH3 "src/cl_files/material.cl"
# define KERNEL_INC_DIR "-I includes"
# endif

# define DEVICE_TYPE CL_DEVICE_TYPE_GPU
# define CLIENT_WORK_SIZE 100

# define MIN_WIN_WIDTH 500
# define MIN_WIN_HEIGHT 500

/*
**	returns a string with file content and writes it`s in the size variable
**	returns NULL and writes 0 to size in case of an error
*/

int			init_win(t_scrn *screen, int server, int shown);
void		close_sdl(t_scrn *screen);
void		init_scene(t_scene *scene, int argc, char **argv);

/*
**	server_main.c
*/

void		init_seeds(t_seeds *s);

/*
**	main_loop.c
*/

void		main_loop_server(t_env *env);
void		main_loop_client(t_env *env);
void		clamp(cl_float3 *px);
void		handle_events(t_env *env);
void		handle_events_client(t_env *env);
int			get_mouse_intersection(t_env *env, SDL_Event e);
void		send_pixels(t_env *env);
void		handle_message(t_env *env);
void		send_connection_msg(t_env *env, time_t *t);
void		send_quit_msg(t_env *env);

/*
**	cl_initialization.c
*/

void		init_opencl(t_cldata *cl);
void		cl_setup(t_env *e);
void		get_work_group_size(t_cldata *cl);
void		init_defaults(t_env *env);
void		init_seeds(t_seeds *s);
void		print_log(t_cldata *cl);

/*
** cl_exec.c
*/

void		cl_exec(t_cldata *cl);

/*
**	keyboard_event.c
*/

void		keyboard_event(SDL_Event e, t_env *env);
int			movement_key_event(SDL_Event e, t_env *env);
int			key_down_event(SDL_Event e, t_env *env);

/*
**	movement_events.c
*/

void		clear_pixels(t_cldata *cl);
void		movement_events(t_env *env);
void		write_scene_to_kernel(t_env *env);

/*
**	window_event.c
*/

void		window_event(SDL_Event e, t_env *env);

/*
**	mouse_event.c
*/

void		mouse_wheel_event(SDL_Event e, t_env *env);

/*
**	scene_init.c
*/

float		calculate_ppd(double fov);

/*
**	rotate.c
*/

cl_float3	rotate_x(float dir, cl_float3 v, t_mvdata mv);
cl_float3	rotate_y(float dir, cl_float3 v, t_mvdata mv);
cl_float3	rotate_z(float dir, cl_float3 v, t_mvdata mv);

/*
**	rot_obj.c
*/

void		rot_sphere(float d, t_obj *s, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_plane(float d, t_obj *p, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_cylinder(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_cone(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_torus(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_disk(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_rectangle(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_parallelogram(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_triangle(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
void		rot_paraboloid(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata));
/*
**	mv_obj.c
*/

void		mv_sphere(cl_float3 d, t_obj *s, t_mvdata mvdata);
void		mv_plane(cl_float3 d, t_obj *p, t_mvdata mvdata);
void		mv_cylinder(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_cone(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_torus(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_disk(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_rectangle(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_parallelogram(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_triangle(cl_float3 d, t_obj *c, t_mvdata mvdata);
void		mv_paraboloid(cl_float3 d, t_obj *c, t_mvdata mvdata);

/*
**	run_server.c
*/

void		run_server(t_env *env);
void		quit_server(t_server *server);

/*
**	socket_utils.c
*/

void		put_error(char *str);
void		set_nonblock(int fd);
void		set_block(int fd);

/*
**	client_read_data.c
*/

void	read_obj(t_env *env, void *msg, unsigned int size);
void	read_scene(t_env *env);

/*
**	write_ppm.c
*/

int			write_ppm(char *filename, cl_float3 *pixels);

/*
**	write_png.c
*/

void		write_png(t_env *env);

t_obj	*find_mouse_intersect(int x, int y, t_env *env);

#endif
