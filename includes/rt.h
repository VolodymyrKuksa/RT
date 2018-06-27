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
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "libvec.h"
# include "get_next_line.h"
# include "rt_types.h"
# include "keys.h"

# define KERNEL_PATH "src/kernel_source.cl"

# ifdef CLION_BUILD
# define KERNEL_PATH "../src/kernel_source.cl"
# else
# define KERNEL_PATH "src/kernel_source.cl"
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
**	cl_initialization.c
*/

void		init_opencl(t_cldata *cl);
void		cl_setup(t_cldata *cl);
void		get_work_group_size(t_cldata *cl);
void		init_defaults(t_cldata *cl);

/*
** cl_exec.c
*/

void		cl_exec(t_cldata *cl);

/*
**	keyboard_event.c
*/

void		keyboard_event(SDL_Event e, t_cldata *cl);
void		key_up_event(SDL_Event e, t_cldata *cl);
void		key_down_event(SDL_Event e, t_cldata *cl);

/*
**	movement_events.c
*/

void		movement_events(t_cldata *cl);

/*
**	rotate.c
*/

cl_float3	rotate_x(float dir, cl_float3 v, t_mvdata mv);
cl_float3	rotate_y(float dir, cl_float3 v, t_mvdata mv);
cl_float3	rotate_z(float dir, cl_float3 v, t_mvdata mv);

#endif
