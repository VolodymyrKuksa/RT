/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_objs2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:19:38 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:19:38 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj			default_rectangle(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.rectangle.pos = (cl_float3){-5.0f, 60, -5.0f};
	tmp.primitive.rectangle.w = 5.f;
	tmp.primitive.rectangle.h = 10.f;
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = rectangle;
	tmp.primitive.rectangle.tex_scale = 20;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
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
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = disk;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	tmp.primitive.disk.related = -1;
	return (tmp);
}

t_obj			default_paraboloid(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.paraboloid.pos = (cl_float3){-5.0f, -5.0f, -5.0f};
	tmp.primitive.paraboloid.k = 9.0f;
	tmp.primitive.paraboloid.k = 10.0f;
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = paraboloid;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
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
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = triangle;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	tmp.primitive.triangle.tex_scale = 20.f;
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
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = parallelogram;
	tmp.tex_id = -1;
	tmp.mater_tex_id = -1;
	tmp.tex_offs = (cl_float2){0.f, 0.f};
	tmp.col_disrupt = NODISRUPT;
	tmp.primitive.parallelogram.tex_scale = 20.f;
	return (tmp);
}
