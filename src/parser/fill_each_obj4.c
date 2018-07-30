/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_each_obj4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:12:42 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:12:43 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fill_triangle_points(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "d1 x") == 0)
		tmp->primitive.triangle.d1.x = (float)v.u.dbl;
	if (ft_strcmp(name, "d1 y") == 0)
		tmp->primitive.triangle.d1.y = (float)v.u.dbl;
	if (ft_strcmp(name, "d1 z") == 0)
		tmp->primitive.triangle.d1.z = (float)v.u.dbl;
	if (ft_strcmp(name, "d2 x") == 0)
		tmp->primitive.triangle.d2.x = (float)v.u.dbl;
	if (ft_strcmp(name, "d2 y") == 0)
		tmp->primitive.triangle.d2.y = (float)v.u.dbl;
	if (ft_strcmp(name, "d2 z") == 0)
		tmp->primitive.triangle.d2.z = (float)v.u.dbl;
	if (ft_strcmp(name, "d3 x") == 0)
		tmp->primitive.triangle.d3.x = (float)v.u.dbl;
	if (ft_strcmp(name, "d3 y") == 0)
		tmp->primitive.triangle.d3.y = (float)v.u.dbl;
	if (ft_strcmp(name, "d3 z") == 0)
		tmp->primitive.triangle.d3.z = (float)v.u.dbl;
	if (ft_strcmp(name, "tex_scale") == 0)
		tmp->primitive.triangle.tex_scale = (int)v.u.dbl;
	if (tmp->primitive.triangle.tex_scale < 1 ||
		tmp->primitive.triangle.tex_scale > 100)
		error_fedun("check tex_scale of triangle. 1 < x < 100");
}

cl_float3		normalize(cl_float3 vec)
{
	float length;

	length = (float)sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	return ((cl_float3){vec.x / length, vec.y / length, vec.z / length});
}

cl_float3		cross(cl_float3 u, cl_float3 v)
{
	return ((cl_float3){u.y * v.z - u.z * v.y,
						u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x});
}

void			get_basis(t_obj *obj)
{
	cl_float3	v1;
	cl_float3	v2;
	cl_float3	normal;

	v1.x = obj->primitive.triangle.d2.x - obj->primitive.triangle.d1.x;
	v1.y = obj->primitive.triangle.d2.y - obj->primitive.triangle.d1.y;
	v1.z = obj->primitive.triangle.d2.z - obj->primitive.triangle.d1.z;
	v2.x = obj->primitive.triangle.d3.x - obj->primitive.triangle.d2.x;
	v2.y = obj->primitive.triangle.d3.y - obj->primitive.triangle.d2.y;
	v2.z = obj->primitive.triangle.d3.z - obj->primitive.triangle.d2.z;
	normal = normalize(cross(v1, v2));
	obj->basis.u = normal;
	obj->basis.w = v1;
	obj->basis.v = cross(obj->basis.u, obj->basis.w);
}

void			help_triangle(t_obj *tmp, t_scene *scene, cl_float3 rot)
{
	minus_camera(&(tmp->primitive.triangle.d1), scene->cam.pos);
	minus_camera(&(tmp->primitive.triangle.d2), scene->cam.pos);
	minus_camera(&(tmp->primitive.triangle.d3), scene->cam.pos);
	rot_pos_cam(&(tmp->primitive.triangle.d1), rot);
	rot_pos_cam(&(tmp->primitive.triangle.d2), rot);
	rot_pos_cam(&(tmp->primitive.triangle.d3), rot);
}
