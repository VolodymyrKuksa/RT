/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_each_obj3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:11:59 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:12:00 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			filldisk(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

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
	tmp.type = disk;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.disk.pos), scene->cam.pos);
	check_basis(&tmp);
	if (SUKA(tmp.primitive.disk.r, 0) == 0)
		error_fedun("radius of disk is bad");
	scene->obj[scene->cur_obj++] = tmp;
}

void			get_common_hat_cone(t_obj *obj1, t_obj tmp, t_scene *scene)
{
	obj1->basis = tmp.basis;
	obj1->type = disk;
	obj1->tex_id = tmp.tex_id;
	obj1->mater_tex_id = tmp.mater_tex_id;
	obj1->color = tmp.color;
	obj1->emission = tmp.emission;
	obj1->diffuse = tmp.diffuse;
	obj1->refraction = tmp.refraction;
	obj1->roughness = tmp.roughness;
	obj1->specular = tmp.specular;
	obj1->primitive.disk.pos = tmp.primitive.cylinder.pos;
	obj1->primitive.disk.related = scene->cur_obj - 1;
}

void			fill_cone_hat1(t_scene *scene, t_obj tmp)
{
	t_obj		obj1;
	t_obj		obj2;

	get_common_hat_cone(&obj1, tmp, scene);
	obj2 = obj1;
	obj1.primitive.disk.r =
			(cl_float)fabs(tmp.primitive.cone.m2 * tmp.primitive.cone.tng);
	obj2.primitive.disk.r =
			(cl_float)fabs(tmp.primitive.cone.m1 * tmp.primitive.cone.tng);
	obj2.primitive.disk.pos.x += tmp.basis.u.x * fabs(tmp.primitive.cone.m1);
	obj2.primitive.disk.pos.y += tmp.basis.u.y * fabs(tmp.primitive.cone.m1);
	obj2.primitive.disk.pos.z += tmp.basis.u.z * fabs(tmp.primitive.cone.m1);
	obj2.basis.u.x = -obj2.basis.u.x;
	obj2.basis.u.y = -obj2.basis.u.y;
	obj2.basis.u.z = -obj2.basis.u.z;

	obj1.primitive.disk.pos.x += tmp.basis.u.x * tmp.primitive.cone.m2;
	obj1.primitive.disk.pos.y += tmp.basis.u.y * tmp.primitive.cone.m2;
	obj1.primitive.disk.pos.z += tmp.basis.u.z * tmp.primitive.cone.m2;
	scene->obj[scene->cur_obj++] = obj1;
	scene->obj[scene->cur_obj++] = obj2;
}

void			fill_cone_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "tng") == 0)
		tmp->primitive.cone.tng = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "m1") == 0)
		tmp->primitive.cone.m1 = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "m2") == 0)
		tmp->primitive.cone.m2 = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "tex_scale") == 0)
		tmp->primitive.cone.tex_scale = (int)v.u.dbl;
	if (tmp->primitive.cone.tex_scale < 1 ||
		tmp->primitive.cone.tex_scale > 100)
		error_fedun("check tex_scale of cone. 1 < x < 100");
}

void			fillthecone(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

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
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.cone.pos), scene->cam.pos);
	tmp.type = cone;
	check_basis(&tmp);
	if (tmp.primitive.cone.m2 <= tmp.primitive.cone.m1
		|| tmp.primitive.cone.m1 < 0.0 || tmp.primitive.cone.m2 < 0)
		error_fedun("m1 > 0.0. m2 > 0; m2 > m1");
	scene->obj[scene->cur_obj++] = tmp;
	fill_cone_hat1(scene, tmp);
}
