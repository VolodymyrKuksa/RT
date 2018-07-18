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
#include "parser.h"

t_obj			default_sphere(void)
{
	t_obj		tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.sphere.pos = (cl_float3){-5.0, -60, -5.0};
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
	tmp.primitive.cylinder.pos = (cl_float3){-5.0, -5.0, -5.0};
	tmp.color = (cl_float3){1.0, 1.0, 1.0};
	tmp.emission = (cl_float3){0.0, 0.0, 0.0};
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.primitive.cylinder.r = 2;
	tmp.tex_id = -1;
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
	return (tmp);
}
