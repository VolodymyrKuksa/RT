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

void			fill_cylinder_params(char *name, json_value v, t_obj *tmp)
{
	printf("%s\n", name);
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
	print_cylinder(tmp);
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
	obj2.primitive.disk.pos.x -= tmp.basis.u.x * fabs(tmp.primitive.cone.m1);
	obj2.primitive.disk.pos.y -= tmp.basis.u.y * fabs(tmp.primitive.cone.m1);
	obj2.primitive.disk.pos.z -= tmp.basis.u.z * fabs(tmp.primitive.cone.m1);
	obj1.primitive.disk.pos.x -= tmp.basis.u.x * tmp.primitive.cone.m2;
	obj1.primitive.disk.pos.y -= tmp.basis.u.y * tmp.primitive.cone.m2;
	obj1.primitive.disk.pos.z -= tmp.basis.u.z * tmp.primitive.cone.m2;
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
		|| tmp.primitive.cone.m1 > 0.1 || tmp.primitive.cone.m2 < 0)
		error_fedun("m1 > 0.1. m2 > 0; m2 > m1");
	scene->obj[scene->cur_obj++] = tmp;
	fill_cone_hat1(scene, tmp);
	print_cone(tmp);
}

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
	print_plane(tmp);
}

void			fillthesphere(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

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
	check_basis(&tmp);
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
	if (tmp->primitive.torus.R < 0.5f)
		error_fedun("torus big radius must be bigger 0.5");
}

void			filltorus(json_value *value, t_scene *scene, int i)
{

	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

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
	tmp.type = torus;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.torus.pos), scene->cam.pos);
	check_basis(&tmp);
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
	if (tmp->primitive.rectangle.h <= 0 || tmp->primitive.rectangle.w <= 0)
		error_fedun("w and h in rectangle must be > 0");
}

void			fillrectangle(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

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
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.rectangle.pos), scene->cam.pos);
	tmp.type = rectangle;
	check_basis(&tmp);
	scene->obj[scene->cur_obj++] = tmp;
	print_rectangle(tmp);
}

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
		error_fedun("radius of sphere is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_disk(tmp);
}

void			fill_paraboloid_centers(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "c x") == 0)
		tmp->primitive.paraboloid.pos.x = (float)v.u.dbl;
	if (ft_strcmp(name, "c y") == 0)
		tmp->primitive.paraboloid.pos.y = (float)v.u.dbl;
	if (ft_strcmp(name, "c z") == 0)
		tmp->primitive.paraboloid.pos.z = (float)v.u.dbl;
}

void			fillparaboloid(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_paraboloid();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		//fill_paraboloid_centers(value->u.object.values[i].name, v, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "k") == 0)
			tmp.primitive.paraboloid.k = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "m") == 0)
			tmp.primitive.paraboloid.m = (cl_float)fabs(v.u.dbl);
		fill_position(value->u.object.values[i].name,
					  (cl_float)v.u.dbl, &(tmp.primitive.paraboloid.pos));
		fill_common(value->u.object.values[i].name, &tmp, &v, &rot);
		i++;
	}

	tmp.type = paraboloid;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.paraboloid.pos), scene->cam.pos);
	check_basis(&tmp);
	//if (SUKA(tmp.primitive.paraboloid.k, 0) == 0)
	//	error_fedun("radius of ellipse is bad");
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

void			filltriangle(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_triangle();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
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

void			fillparallelogram(json_value *value, t_scene *scene, int i)
{
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	tmp = default_parallelogram();
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < value->u.object.length)
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
	print_parallelogram(tmp);
}
