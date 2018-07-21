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
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	tmp.type = cylinder;
	minus_camera(&(tmp.primitive.cylinder.pos), scene->cam.pos);
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
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.cone.pos), scene->cam.pos);
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
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.plane.pos), scene->cam.pos);
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
	tmp.type = sphere;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.sphere.pos), scene->cam.pos);
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
	tmp.type = torus;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.torus.pos), scene->cam.pos);
	if (!((tmp.primitive.torus.R > tmp.primitive.torus.r) && (tmp.primitive.torus.r > 0)))
		error_fedun("radius of sphere is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_sphere(tmp);
}