/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rot_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 14:02:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/30 14:02:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rot_disk(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.disk.pos = f(d, c->primitive.disk.pos, mvdata);
}

void	rot_rectangle(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.rectangle.pos = f(d, c->primitive.rectangle.pos, mvdata);
}

void	rot_parallelogram(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.parallelogram.pos =
		f(d, c->primitive.parallelogram.pos, mvdata);
}

void	rot_triangle(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.triangle.d1 = f(d, c->primitive.triangle.d1, mvdata);
	c->primitive.triangle.d2 = f(d, c->primitive.triangle.d2, mvdata);
	c->primitive.triangle.d3 = f(d, c->primitive.triangle.d3, mvdata);
}

void	rot_paraboloid(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.paraboloid.pos = f(d, c->primitive.paraboloid.pos, mvdata);
}
