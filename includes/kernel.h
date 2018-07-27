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

typedef struct		s_texture
{
	__global t_rgb		*tx;
	__global t_txdata	*txdata;
	int					tx_count;
}					t_texture;

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
	sphere,
	plane,
	cylinder,
	cone,
	torus,
	disk,
	rectangle,
	paralellogram,
	triangle,
	elipsoid
}					t_obj_type;

typedef struct		s_sphere
{
	__float3	pos;
	float		r;
}					t_sphere;

typedef struct		s_cylinder
{
	__float3	pos;
	float		r;
	float		h;
}					t_cylinder;

typedef struct		s_plane
{
	__float3	pos;
}					t_plane;

typedef struct		s_cone
{
	__float3	pos;
	float		tng;
	float 		m1;
	float 		m2;
}					t_cone;

typedef struct		s_torus
{
	__float3	pos;
	float		R;
	float		r;
}					t_torus;

typedef struct		s_disk
{
	__float3	pos;
	float	r;
}					t_disk;

typedef struct		s_rectangle
{
    __float3	pos;
    float		h;
    float		w;
}					t_rectangle;

typedef struct		s_paralellogram
{
	__float3	pos;
	float		h;
	float		w;
	float		l;
}					t_paralellogram;

typedef struct		s_triangle
{
	__float3	d1;
	__float3	d2;
	__float3	d3;

}					t_triangle;

typedef struct		s_elipsoid
{
	__float3	pos;
	__float3	C1;
	__float3	C2;
	float 		r;
}					t_elipsoid;

typedef	union		u_primitive
{
	t_plane			plane;
	t_sphere		sphere;
	t_cylinder		cylinder;
	t_cone			cone;
	t_torus			torus;
	t_disk			disk;
    t_rectangle 	rectangle;
	t_paralellogram	paralellogram;
	t_triangle		triangle;
	t_elipsoid		elipsoid;
}					t_primitive;

typedef struct		s_basis
{
	__float3		u;
	__float3		v;
	__float3		w;
}					t_basis;

typedef struct		s_object
{
	t_obj_type	type;
	t_primitive	primitive;
	t_basis		basis;
	float		diffuse;
	float		specular;
	float		refraction;
	float		roughness;
	__float3	color;
	__float3	emission;
	int			tex_id;
	int			mater_tex_id;
}					t_obj;

typedef struct		s_material
{
	float		diffuse;
	float		specular;
	float		refraction;
	float		roughness;
	float3		color;
	float3		emission;
	float3		normal;
	bool		enter;
}					t_material;

#endif
