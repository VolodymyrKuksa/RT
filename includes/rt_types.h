/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_types.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:12:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/23 19:12:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TYPES_H
# define RT_TYPES_H

# define WIN_WIDTH 1080
# define WIN_HEIGHT 720

# include <OpenCL/opencl.h>
#include <SDL.h>
# include "libvec.h"

typedef struct		s_scrn
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	unsigned int	*surf_arr;
}					t_scrn;

typedef struct			s_cldata
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				**source;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_size;
	size_t				local_size;
	cl_mem				clin;
	cl_mem				clout;
}						t_cldata;

/* some stupid shit:
typedef struct		s_sphere
{
	t_vec			col;
	t_vec			pos;
	t_vec			emission;
	double			r;
}					t_sphere;

typedef struct		s_ray
{
	t_vec			pos;
	t_vec			dir;
}					t_ray;

typedef struct		s_cam
{
	t_vec			pos;
	t_vec			dir;
	t_vec			updir;
	t_vec			ldir;
	double			f_length;
	double			aperture;
}					t_cam;

typedef struct		s_env
{
	SDL_Window		*wnd;
	SDL_Renderer	*rend;
}					t_env;
*/

#endif
