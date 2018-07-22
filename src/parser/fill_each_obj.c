/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_each_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:02:34 by afedun            #+#    #+#             */
/*   Updated: 2018/07/18 13:02:35 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "rt.h"

void			fill_cylinder_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "radius") == 0)
		tmp->primitive.cylinder.r = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "h") == 0)
		tmp->primitive.cylinder.h = (cl_float)v.u.dbl;
}

void			fillthecylind(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_cylinder();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.cylinder.pos));
		fill_cylinder_params(value->u.object.values[i].name, v, &tmp);
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	init_rotate(&(tmp.basis), rot);
	tmp.type = cylinder;
	minus_camera(&(tmp.primitive.cylinder.pos), scene->cam.pos, -1);
	if (SUKA(tmp.primitive.sphere.r, 0) == 0)
		error_fedun("radius of cylinder is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_cylinder(tmp);
}

void			fill_cone_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "tng") == 0)
		tmp->primitive.cone.tng = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "m1") == 0)
		tmp->primitive.cone.m1 = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "m2") == 0)
		tmp->primitive.cone.m2 = (cl_float)v.u.dbl;
}

void			fillthecone(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_cone();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.cone.pos));
		fill_cone_params(value->u.object.values[i].name, v, &tmp);
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.cone.pos), scene->cam.pos, -1);
	tmp.type = cone;
	if (tmp.primitive.cone.m2 <= tmp.primitive.cone.m1 ||
			tmp.primitive.cone.m1 <= 0 || tmp.primitive.cone.m2 <= 0)
		error_fedun("m1 and m2 must be greater 0; m2 > m1");
	scene->obj[scene->cur_obj++] = tmp;
	print_cone(tmp);
}

void			filltheplane(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_plane();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.plane.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.plane.pos), scene->cam.pos, -1);
	tmp.type = plane;
	scene->obj[scene->cur_obj++] = tmp;
	print_plane(tmp);
}

void			fillthesphere(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_sphere();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.sphere.pos));
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.sphere.r = (cl_float)v.u.dbl;
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	tmp.type = sphere;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.sphere.pos), scene->cam.pos, -1);
	if (SUKA(tmp.primitive.sphere.r, 0) == 0)
		error_fedun("radius of sphere is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_sphere(tmp);
}

void			fill_torus_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "radius small") == 0)
		tmp->primitive.torus.r = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "radius big") == 0)
		tmp->primitive.torus.R = (cl_float)v.u.dbl;
}

void			filltorus(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_torus();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.torus.pos));
		fill_torus_params(value->u.object.values[i].name, v, &tmp);
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	tmp.type = torus;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.torus.pos), scene->cam.pos, -1);
	if ((tmp.primitive.torus.R <= 0) || (tmp.primitive.torus.r <= 0))
		error_fedun("radius of torus is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_torus(tmp);
}

void			help_rectangle(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "w") == 0)
		tmp->primitive.rectangle.w = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "h") == 0)
		tmp->primitive.rectangle.h = (cl_float)v.u.dbl;
}

void			fillrectangle(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_rectangle();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.rectangle.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		help_rectangle(value->u.object.values[i].name, v, &tmp);
		i++;
	}
	tmp.rot = rot;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.rectangle.pos), scene->cam.pos, -1);
	tmp.type = rectangle;
	if (tmp.primitive.rectangle.h <= 0 || tmp.primitive.rectangle.w <= 0)
		error_fedun("w and h in rectangle must be > 0");
	scene->obj[scene->cur_obj++] = tmp;
	print_rectangle(tmp);
}

void			filldisk(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_disk();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.disk.pos));
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.disk.r = (cl_float)v.u.dbl;
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	tmp.type = disk;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.disk.pos), scene->cam.pos, -1);
	if (SUKA(tmp.primitive.disk.r, 0) == 0)
		error_fedun("radius of sphere is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_disk(tmp);
}

void			fill_ellipse_centers(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "c1 x") == 0)
		tmp->primitive.ellipse.c1.x = (float)v.u.dbl;
	if (ft_strcmp(name, "c1 y") == 0)
		tmp->primitive.ellipse.c1.y = (float)v.u.dbl;
	if (ft_strcmp(name, "c1 z") == 0)
		tmp->primitive.ellipse.c1.z = (float)v.u.dbl;
	if (ft_strcmp(name, "c2 x") == 0)
		tmp->primitive.ellipse.c2.x = (float)v.u.dbl;
	if (ft_strcmp(name, "c2 y") == 0)
		tmp->primitive.ellipse.c2.y = (float)v.u.dbl;
	if (ft_strcmp(name, "c2 z") == 0)
		tmp->primitive.ellipse.c2.z = (float)v.u.dbl;
}

void			fillellipse(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_ellipse();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_ellipse_centers(value->u.object.values[i].name, v, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.ellipse.r = (cl_float)v.u.dbl;
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	tmp.type = ellipse;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.ellipse.c1), scene->cam.pos, -1);
	minus_camera(&(tmp.primitive.ellipse.c2), scene->cam.pos, -1);
	if (SUKA(tmp.primitive.ellipse.r, 0) == 0)
		error_fedun("radius of ellipse is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_ellipse(tmp);
}

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
}

void			filltriangle(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_triangle();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_triangle_points(value->u.object.values[i].name, v, &tmp);
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	tmp.type = triangle;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.triangle.d1), scene->cam.pos, -1);
	minus_camera(&(tmp.primitive.triangle.d2), scene->cam.pos, -1);
	minus_camera(&(tmp.primitive.triangle.d3), scene->cam.pos, -1);
	scene->obj[scene->cur_obj++] = tmp;
	print_triangle(tmp);
}

void			fill_parallelogram_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "h") == 0)
		tmp->primitive.parallelogram.h = (float)v.u.dbl;
	if (ft_strcmp(name, "w") == 0)
		tmp->primitive.parallelogram.w = (float)v.u.dbl;
	if (ft_strcmp(name, "l") == 0)
		tmp->primitive.parallelogram.l = (float)v.u.dbl;
}

void			fillparallelogram(json_value *value, t_scene *scene)
{
	int			i;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = -1;
	tmp = default_parallelogram();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i++ < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
					(cl_float)v.u.dbl, &(tmp.primitive.rectangle.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		fill_parallelogram_params(value->u.object.values[i].name, v, &tmp);
	}
	tmp.rot = rot;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.parallelogram.pos), scene->cam.pos, -1);
	tmp.type = parallelogram;
	if (tmp.primitive.parallelogram.h <= 0 || tmp.primitive.parallelogram.w <= 0
			|| tmp.primitive.parallelogram.l <= 0)
		error_fedun("l, w and h in parallelogram must be > 0");
	scene->obj[scene->cur_obj++] = tmp;
	print_parallelogram(tmp);
}
