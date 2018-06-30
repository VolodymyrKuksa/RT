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
# include "rt_types.h"
# include "keys.h"

# ifdef CLION_BUILD
# define KERNEL_PATH0 "../src/kernel_source.cl"
# define KERNEL_PATH1 "../src/intersections_and_normals.cl"
# define KERNEL_INC_DIR "-I ../includes"
# else
# define KERNEL_PATH0 "src/kernel_source.cl"
# define KERNEL_PATH1 "src/intersections_and_normals.cl"
# define KERNEL_INC_DIR "-I includes"
# endif

# define DEVICE_TYPE CL_DEVICE_TYPE_GPU

/*
**	returns a string with file content and writes it`s in the size variable
**	returns NULL and writes 0 to size in case of an error
*/

char		*read_file(int fd, size_t *size);
int			init_win(t_scrn *screen);
void		close_sdl(t_scrn *screen);
void		init_scene(t_scene *scene);

/*
**	main.c
*/

void		init_seeds(t_seeds *s);
float		calculate_ppd(double fov);

/*
**	cl_initialization.c
*/

void		init_opencl(t_cldata *cl);
void		cl_setup(t_env *e);
void		get_work_group_size(t_cldata *cl);
void		init_defaults(t_env *env);

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

void		movement_events(t_env *env);

/*
**	window_event.c
*/

void		window_event(SDL_Event e, t_env *env);

/*
**	rotate.c
*/

cl_float3	rotate_x(float dir, cl_float3 v, t_mvdata mv);
cl_float3	rotate_y(float dir, cl_float3 v, t_mvdata mv);

cl_float3	rotate_z(float dir, cl_float3 v, t_mvdata mv);

/*
**	write_ppm.c
*/

int			write_ppm(char *filename, cl_float3 *pixels);

/*
**	write_png.c
*/

void		write_png(t_env *env);

#endif
