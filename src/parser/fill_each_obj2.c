/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_each_obj2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:11:26 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:11:27 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fill_plane_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "tex_scale") == 0)
		tmp->primitive.plane.tex_scale = (int)v.u.dbl;
	if (tmp->primitive.plane.tex_scale < 1 ||
		tmp->primitive.plane.tex_scale > 100)
		error_fedun("check tex_scale of plane. 1 < x < 100");
}

void			filltheplane(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_plane();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
					(cl_float)v.u.dbl, &(tmp.primitive.plane.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		fill_plane_params(value->u.object.values[i].name, v, &tmp);
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	check_basis(&tmp);
	minus_camera(&(tmp.primitive.plane.pos), scene->cam.pos);
	tmp.type = plane;
	scene->obj[scene->cur_obj++] = tmp;
}

void			fill_cylinder_params(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "radius") == 0)
		tmp->primitive.cylinder.r = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "h") == 0)
		tmp->primitive.cylinder.h = (cl_float)v.u.dbl;
	if (tmp->primitive.cylinder.h <= 0)
		error_fedun("height of cylinder must be > 0\n");
	if (tmp->primitive.cylinder.r <= 0)
		error_fedun("radius of cylinder must be > 0\n");
	if (ft_strcmp(name, "tex_scale") == 0)
		tmp->primitive.cylinder.tex_scale = (int)v.u.dbl;
	if (tmp->primitive.cylinder.tex_scale < 1 ||
		tmp->primitive.cylinder.tex_scale > 100)
		error_fedun("check tex_scale of plane. 1 < x < 100");
}

void			fill_cylind_hats(t_scene *scene, t_obj tmp)
{
	t_obj		obj1;
	t_obj		obj2;

	obj1 = default_disk();
	obj1.basis = tmp.basis;
	obj1.type = disk;
	obj1.tex_id = tmp.tex_id;
	obj1.mater_tex_id = tmp.mater_tex_id;
	obj1.color = tmp.color;
	obj1.emission = tmp.emission;
	obj1.diffuse = tmp.diffuse;
	obj1.refraction = tmp.refraction;
	obj1.roughness = tmp.roughness;
	obj1.specular = tmp.specular;
	obj1.primitive.disk.r = tmp.primitive.cylinder.r;
	obj1.primitive.disk.related = scene->cur_obj - 1;
	obj2 = obj1;
	obj1.primitive.disk.pos = tmp.primitive.cylinder.pos;
	obj2.primitive.disk.pos = tmp.primitive.cylinder.pos;
	obj2.primitive.disk.pos.x += tmp.basis.u.x * tmp.primitive.cylinder.h;
	obj2.primitive.disk.pos.y += tmp.basis.u.y * tmp.primitive.cylinder.h;
	obj2.primitive.disk.pos.z += tmp.basis.u.z * tmp.primitive.cylinder.h;
	scene->obj[scene->cur_obj++] = obj1;
	scene->obj[scene->cur_obj++] = obj2;
}

void			fillthecylind(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

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
	init_rotate(&(tmp.basis), rot);
	tmp.type = cylinder;
	minus_camera(&(tmp.primitive.cylinder.pos), scene->cam.pos);
	check_basis(&tmp);
	scene->obj[scene->cur_obj++] = tmp;
	fill_cylind_hats(scene, tmp);
}