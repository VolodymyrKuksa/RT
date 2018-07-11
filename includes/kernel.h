/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 20:04:48 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/29 20:04:52 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KERNEL_H
# define KERNEL_H

typedef union		u_rgb
{
	unsigned int	c;
	unsigned char	bgra[4];
}					t_rgb;

typedef struct		s_txdata
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	start;
}					t_txdata;

typedef struct		s_cam
{
	__float3		pos;
	__float3		dir;
	__float3		updir;
	__float3		ldir;
	double			fov;
	float			f_length;
	float			aperture;
	float			ratio;
	float			pr_pl_w;
	float			pr_pl_h;
	float			dust;
}					t_cam;

typedef struct		s_ray
{
	__float3		pos;
	__float3		dir;
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

typedef enum		e_obj_type
{
	sphere, plane, cylinder, cone
}					t_obj_type;

typedef struct		s_sphere
{
	__float3	pos;
	float3		rot;
	float		r;
}					t_sphere;

typedef struct		s_cylinder
{
	__float3	pos;
	__float3	rot;
	float		r;
}					t_cylinder;

typedef struct		s_plane
{
	__float3	pos;
	__float3	rot;
}					t_plane;

typedef struct		s_cone
{
	__float3	pos;
	__float3	rot;
	float		tng;
}					t_cone;

typedef	union		u_primitive
{
	t_plane		plane;
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_cone		cone;
}					t_primitive;

typedef struct		s_object
{
	t_obj_type	type;
	t_primitive	primitive;
	float		diffuse;
	float		specular;
	float		refraction;
	float		roughness;
	float		ior;
	__float3	color;
	__float3	emission;
	int			tex_id;
}					t_obj;

#endif
