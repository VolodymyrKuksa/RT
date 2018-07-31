/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_each_obj5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:13:04 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:13:06 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fill_paraboloid_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "k") == 0)
		tmp->primitive.paraboloid.k = (cl_float)fabs(v.u.dbl);
	if (ft_strcmp(name, "m") == 0)
		tmp->primitive.paraboloid.m = (cl_float)fabs(v.u.dbl);
}

void			fillparaboloid(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_paraboloid();
	rot = (cl_float3){{0.0, 0.0, 0.0}};
	while ((unsigned int)i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_paraboloid_params(value->u.object.values[i].name, v, &tmp);
		fill_position(value->u.object.values[i].name,
					(cl_float)v.u.dbl, &(tmp.primitive.paraboloid.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.type = paraboloid;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.paraboloid.pos), scene->cam.pos);
	check_basis(&tmp);
	scene->obj[scene->cur_obj++] = tmp;
}

void			filltriangle(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_triangle();
	rot = (cl_float3){{0.0, 0.0, 0.0}};
	while ((unsigned int)i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_triangle_points(value->u.object.values[i].name, v, &tmp);
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.type = triangle;
	help_triangle(&tmp, scene, rot);
	get_basis(&tmp);
	init_rotate(&(tmp.basis), rot);
	check_basis(&tmp);
	scene->obj[scene->cur_obj++] = tmp;
}

void			fill_parallelogram_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "h") == 0)
		tmp->primitive.parallelogram.h = (float)v.u.dbl;
	if (ft_strcmp(name, "w") == 0)
		tmp->primitive.parallelogram.w = (float)v.u.dbl;
	if (ft_strcmp(name, "l") == 0)
		tmp->primitive.parallelogram.l = (float)v.u.dbl;
	if (ft_strcmp(name, "tex_scale") == 0)
		tmp->primitive.parallelogram.tex_scale = (int)v.u.dbl;
	if (tmp->primitive.parallelogram.tex_scale < 1 ||
		tmp->primitive.parallelogram.tex_scale > 100)
		error_fedun("check tex_scale of parallelogram. 1 < x < 100");
}

void			fillparallelogram(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_parallelogram();
	rot = (cl_float3){{0.0, 0.0, 0.0}};
	while ((unsigned int)i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
					(cl_float)v.u.dbl, &(tmp.primitive.rectangle.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		fill_parallelogram_params(value->u.object.values[i].name, v, &tmp);
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.parallelogram.pos), scene->cam.pos);
	tmp.type = parallelogram;
	check_basis(&tmp);
	if (tmp.primitive.parallelogram.h <= 0 || tmp.primitive.parallelogram.w <= 0
		|| tmp.primitive.parallelogram.l <= 0)
		error_fedun("l, w and h in parallelogram must be > 0");
	scene->obj[scene->cur_obj++] = tmp;
}
