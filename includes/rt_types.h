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
	float			dust;
}					t_cam;

typedef struct		s_seed
{
	uint			*seeds;
	size_t			size;
}					t_seeds;

typedef struct		s_mvdata
{
	float			move_spd;
	double			turn_a;
	double			cosine_a;
	double			sine_a;
}					t_mvdata;

typedef struct		s_ray
{
	cl_float3		pos;
	cl_float3		dir;
	int				refractions;
	float			dust;
}					t_ray;

typedef struct		s_quad
{
	float a;
	float b;
	float c;
	float d;
	float res;
}					t_quad;

typedef enum	e_obj_type
{
	sphere, plane, cylinder, cone
}				t_obj_type;

typedef struct	s_sphere
{
	cl_float3 	pos;
	cl_float3	rot;
	cl_float	r;
}				t_sphere;

typedef struct	s_cylinder
{
	cl_float3 	pos;
	cl_float3 	rot;
	float	r;
	//float	height;
}				t_cylinder;

typedef struct	s_plane
{
	cl_float3 	pos;
	cl_float3 	rot;
}				t_plane;

typedef struct	s_cone
{
	cl_float3 	pos;
	cl_float3 	rot;
	float	tng;
//	float	m1;
//	float	m2;
}				t_cone;

typedef	union	u_primitive
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
}				t_primitive;

typedef struct	s_object
{
	t_obj_type	type;
	t_primitive	primitive;
	cl_float	diffuse;
	cl_float	specular;
	cl_float	refraction;
	cl_float	roughness;
	cl_float	ior;
	cl_float3 	color;
	cl_float3 	emission;
//	float (*intersection)(t_ray*, struct s_object);
//	cl_float3 (*normal)(cl_float3  , cl_float3 , struct s_object);
	//cl_uchar4	texture;
}				t_obj;

typedef struct		s_scene
{
	int				num_obj;
	t_obj			*obj;
	t_cam			cam;
}					t_scene;

typedef struct		s_cldata
{
	cl_device_id		dev_id;
	cl_context			context;
	cl_command_queue	command_queue;
	char				*source[2];
	size_t				source_size;
	cl_program			program;
	cl_kernel			kernel;
	size_t				global_size;
	size_t				local_size;

	cl_float3			*px_host;
	cl_float3			*pixels;
	unsigned int		num_samples;

	cl_mem				px_gpu;
	cl_mem				obj_gpu;
	cl_mem				seed_gpu;

	t_scrn				screen;
	t_scene				sc;
	t_seeds				seeds;

	unsigned int		move_keys;
	t_mvdata			mv_data;
}					t_cldata;

#endif
