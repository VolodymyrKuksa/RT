/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_objs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 11:59:58 by afedun            #+#    #+#             */
/*   Updated: 2018/07/18 12:00:00 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj			default_sphere(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.sphere.pos = (cl_float3){-5.0f, -60, -5.0f};
	tmp.primitive.sphere.r = 5;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_cone(void)
{
	t_obj		tmp;

	tmp.primitive.cone.pos.x = -2;
	tmp.primitive.cone.pos.y = -2;
	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.cone.m1 = 0.0f;
	tmp.primitive.cone.m2 = 200.0f;
	tmp.primitive.cone.tng = 0.1;
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = cone;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.primitive.cone.m1 = 3.f;
	tmp.primitive.cone.m2 = 7.f;
	return (tmp);
}

t_obj			default_cylinder(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.cylinder.pos = (cl_float3){-5.0f, -5.0f, -5.0f};
	tmp.primitive.cylinder.h = 150.f;
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.primitive.cylinder.r = 2;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.type = cylinder;
	return (tmp);
}

t_obj			default_plane(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.plane.pos.x = 10;
	tmp.primitive.plane.pos.y = 10;
	tmp.primitive.plane.pos.z = 10;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 1;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.type = plane;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_torus(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.torus.pos.x = 0;
	tmp.primitive.torus.pos.y = 0;
	tmp.primitive.torus.pos.z = -30;
	tmp.primitive.torus.r = 40.f;
	tmp.primitive.torus.R = 60.f;
	tmp.color.x = 0.f;
	tmp.color.y = 1.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = torus;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_rectangle(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.rectangle.pos.x = 0;
	tmp.primitive.rectangle.pos.y = 0;
	tmp.primitive.rectangle.pos.z = -30;
	tmp.primitive.rectangle.w = 5.f;
	tmp.primitive.rectangle.h = 10.f;
	tmp.color.x = 1.f;
	tmp.color.y = 0.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = rectangle;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_disk(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.disk.pos = (cl_float3){-5.0f, 60, -5.0f};
	tmp.primitive.disk.r = 5;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = disk;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_ellipse(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.ellipse.c1 = (cl_float3){-5.0f, -5.0f, -5.0f};
	tmp.primitive.ellipse.c2 = (cl_float3){5.0f, 5.0f, 5.0f};
	tmp.primitive.ellipse.r = 9.0f;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = ellipse;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_triangle(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.triangle.d1 = (cl_float3){0.0f, 5.0f, 0.0f};
	tmp.primitive.triangle.d2 = (cl_float3){0.0f, 0.0f, 5.0f};
	tmp.primitive.triangle.d3 = (cl_float3){5.0f, 0.0f, 0.0f};
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = triangle;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}

t_obj			default_parallelogram(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.parallelogram.pos = (cl_float3){0.0, 0.0, -30.0f};
	tmp.primitive.parallelogram.w = 5.f;
	tmp.primitive.parallelogram.h = 10.f;
	tmp.primitive.parallelogram.l = 1.f;
	tmp.color.x = 1.f;
	tmp.color.y = 0.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = parallelogram;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	return (tmp);
}
