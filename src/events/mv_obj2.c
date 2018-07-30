/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_obj2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 14:04:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/30 14:04:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	mv_parallelogram(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.parallelogram.pos.x += d.x * mvdata.move_spd;
	c->primitive.parallelogram.pos.y += d.y * mvdata.move_spd;
	c->primitive.parallelogram.pos.z += d.z * mvdata.move_spd;
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

void	mv_paraboloid(cl_float3 d, t_obj *c, t_mvdata mvdata)
{
	c->primitive.paraboloid.pos.x += d.x * mvdata.move_spd;
	c->primitive.paraboloid.pos.y += d.y * mvdata.move_spd;
	c->primitive.paraboloid.pos.z += d.z * mvdata.move_spd;
}
