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

# include <OpenCL/opencl.h>
#include <SDL.h>
# include "libvec.h"

typedef union		u_rgb
{
	unsigned int	c;
	unsigned char	argb[4];
}					t_rgb;

typedef struct		s_scrn
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	t_rgb			*surf_arr;
}					t_scrn;

typedef struct			s_cldata
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				**source;
	size_t				source_size;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_size;
	size_t				local_size;
}						t_cldata;

typedef struct		s_sphere
{
	cl_float3		col;
	cl_float3		pos;
	cl_float3		emission;
	float			r;
}					t_sphere;

typedef struct		s_ray
{
	cl_float3		pos;
	cl_float3		dir;
}					t_ray;

typedef struct		s_cam
{
	cl_float3		pos;
	cl_float3		dir;
	cl_float3		updir;
	cl_float3		ldir;
	float			f_length;
	float			aperture;
	int				pr_pl_w;
	int				pr_pl_h;
}					t_cam;

typedef struct		s_scene
{
	int				num_obj;
	t_sphere		*obj;
	t_cam			cam;
}					t_scene;

#endif
