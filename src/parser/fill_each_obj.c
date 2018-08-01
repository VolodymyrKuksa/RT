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

#include "rt.h"

void			fillthesphere(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_sphere();
	rot = (cl_float3){{0.0, 0.0, 0.0}};
	while ((unsigned int)i < value->u.object.length)
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
	check_basis(&tmp);
	if (SUKA(tmp.primitive.sphere.r, 0) == 0)
		error_fedun("radius of sphere is bad");
	scene->obj[scene->cur_obj++] = tmp;
}

void			fill_torus_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "radius small") == 0)
		tmp->primitive.torus.r = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "radius big") == 0)
		tmp->primitive.torus.big_r = (cl_float)v.u.dbl;
	if (tmp->primitive.torus.big_r < 0.5f)
		error_fedun("torus big radius must be bigger 0.5");
}

void			filltorus(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_torus();
	rot = (cl_float3){{0.0, 0.0, 0.0}};
	while ((unsigned int)i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.torus.pos));
		fill_torus_params(value->u.object.values[i].name, v, &tmp);
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}
	tmp.type = torus;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.torus.pos), scene->cam.pos);
	check_basis(&tmp);
	if ((tmp.primitive.torus.big_r <= 0) || (tmp.primitive.torus.r <= 0))
		error_fedun("radius of torus is bad");
	scene->obj[scene->cur_obj++] = tmp;
}

void			help_rectangle(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "w") == 0)
		tmp->primitive.rectangle.w = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "h") == 0)
		tmp->primitive.rectangle.h = (cl_float)v.u.dbl;
	if (tmp->primitive.rectangle.h <= 0 || tmp->primitive.rectangle.w <= 0)
		error_fedun("w and h in rectangle must be > 0");
}

void			fillrectangle(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_rectangle();
	rot = (cl_float3){{0.0, 0.0, 0.0}};
	while ((unsigned int)i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.rectangle.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		help_rectangle(value->u.object.values[i].name, v, &tmp);
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.rectangle.pos), scene->cam.pos);
	tmp.type = rectangle;
	check_basis(&tmp);
	scene->obj[scene->cur_obj++] = tmp;
}
