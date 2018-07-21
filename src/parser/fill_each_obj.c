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
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.cylinder.r = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "h") == 0)
			tmp.primitive.cylinder.h = (cl_float)v.u.dbl;
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
		if (ft_strcmp(value->u.object.values[i].name, "tng") == 0)
			tmp.primitive.cone.tng = (cl_float)v.u.dbl;
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.rot = rot;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.cone.pos), scene->cam.pos, -1);
	tmp.type = cone;
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

void        filltorus(json_value *value, t_scene *scene)
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
		if (ft_strcmp(value->u.object.values[i].name, "radius small") == 0)
			tmp.primitive.torus.r = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "radius big") == 0)
			tmp.primitive.torus.R = (cl_float)v.u.dbl;
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

