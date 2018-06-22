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

typedef union		u_rgb
{
	unsigned int	c;
	unsigned char	bgra[4];
}					t_rgb;

typedef struct		s_scrn
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	t_rgb			*surf_arr;
}					t_scrn;

typedef struct		s_surf
{
	cl_float3		type;
	float			roughness;
	float			refraction;
}					t_surf;

typedef struct		s_sphere
{
	cl_float3		col;
	cl_float3		pos;
	cl_float3		emission;
	float			r;
	t_surf			surf;
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
	float			ratio;
	float			pr_pl_w;
	float			pr_pl_h;
}					t_cam;

typedef struct		s_scene
{
	int				num_obj;
	t_sphere		*obj;
	t_cam			cam;
}					t_scene;

typedef struct		s_seed
{
	uint			*seeds;
	size_t			size;
}					t_seeds;

typedef struct			s_cldata
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*source;
	size_t				source_size;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_size;
	size_t				local_size;

	cl_float3	*px_host;
	cl_float3	*pixels;

	cl_mem		px_gpu;
	cl_mem		obj_gpu;
	cl_mem		seed_gpu;

	t_scene		sc;
	t_seeds		seeds;
}						t_cldata;

#endif
