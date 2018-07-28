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
	tmp.color = (cl_float3){1.f, 1.f, 1.f};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	return (tmp);
}

t_obj			default_cone(void)
{
	t_obj		tmp;

	tmp.primitive.cone.pos = (cl_float3){-2.0f, -2.0f, -2.0f};
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
	tmp.primitive.cone.tex_scale = 20;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
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
	tmp.primitive.cylinder.tex_scale = 20;
	tmp.type = cylinder;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	return (tmp);
}

t_obj			default_plane(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.plane.pos = (cl_float3){10, 10, 10};
	tmp.primitive.plane.pos = (cl_float3){12.0f, 12.0f, 12.0f};
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.type = plane;
	tmp.primitive.plane.tex_scale = 20;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	return (tmp);
}

t_obj			default_torus(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.torus.pos = (cl_float3){-5.0f, 60, -5.0f};
	tmp.primitive.torus.r = 40.f;
	tmp.primitive.torus.R = 60.f;
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = torus;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	return (tmp);
}
