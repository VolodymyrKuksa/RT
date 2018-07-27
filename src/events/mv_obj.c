/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_obj.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 12:06:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/10 12:06:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	mv_sphere(cl_float3 d, t_obj *s, t_mvdata mvdata)
{
	s->primitive.sphere.pos.x += d.x * mvdata.move_spd;
	s->primitive.sphere.pos.y += d.y * mvdata.move_spd;
	s->primitive.sphere.pos.z += d.z * mvdata.move_spd;
}

void	mv_plane(cl_float3 d, t_obj *p, t_mvdata mvdata)
{
	p->primitive.plane.pos.x += d.x * mvdata.move_spd;
	p->primitive.plane.pos.y += d.y * mvdata.move_spd;
	p->primitive.plane.pos.z += d.z * mvdata.move_spd;
}

void	mv_cylinder(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.cylinder.pos.x += d.x * mvdata.move_spd;
	c->primitive.cylinder.pos.y += d.y * mvdata.move_spd;
	c->primitive.cylinder.pos.z += d.z * mvdata.move_spd;
}

void	mv_cone(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.cone.pos.x += d.x * mvdata.move_spd;
	c->primitive.cone.pos.y += d.y * mvdata.move_spd;
	c->primitive.cone.pos.z += d.z * mvdata.move_spd;
}

void	mv_torus(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.torus.pos.x += d.x * mvdata.move_spd;
	c->primitive.torus.pos.y += d.y * mvdata.move_spd;
	c->primitive.torus.pos.z += d.z * mvdata.move_spd;
}

void	mv_disk(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.disk.pos.x += d.x * mvdata.move_spd;
	c->primitive.disk.pos.y += d.y * mvdata.move_spd;
	c->primitive.disk.pos.z += d.z * mvdata.move_spd;
}

void	mv_rectangle(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.rectangle.pos.x += d.x * mvdata.move_spd;
	c->primitive.rectangle.pos.y += d.y * mvdata.move_spd;
	c->primitive.rectangle.pos.z += d.z * mvdata.move_spd;
}

void	mv_paralellogram(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.paralellogram.pos.x += d.x * mvdata.move_spd;
	c->primitive.paralellogram.pos.y += d.y * mvdata.move_spd;
	c->primitive.paralellogram.pos.z += d.z * mvdata.move_spd;
}

void	mv_triangle(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.triangle.d1.x += d.x * mvdata.move_spd;
	c->primitive.triangle.d1.y += d.y * mvdata.move_spd;
	c->primitive.triangle.d1.z += d.z * mvdata.move_spd;

	c->primitive.triangle.d2.x += d.x * mvdata.move_spd;
	c->primitive.triangle.d2.y += d.y * mvdata.move_spd;
	c->primitive.triangle.d2.z += d.z * mvdata.move_spd;

	c->primitive.triangle.d3.x += d.x * mvdata.move_spd;
	c->primitive.triangle.d3.y += d.y * mvdata.move_spd;
	c->primitive.triangle.d3.z += d.z * mvdata.move_spd;
}