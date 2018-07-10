/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_turn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 11:08:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/10 11:08:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rot_sphere(float d, t_obj *s, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	s->primitive.sphere.pos = f(d, s->primitive.sphere.pos, mvdata);
	s->primitive.sphere.rot = f(d, s->primitive.sphere.rot, mvdata);
}

void	rot_plane(float d, t_obj *p, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	p->primitive.plane.pos = f(d, p->primitive.plane.pos, mvdata);
	p->primitive.plane.rot = f(d, p->primitive.plane.rot, mvdata);
}

void	rot_cylinder(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.cylinder.pos = f(d, c->primitive.cylinder.pos, mvdata);
	c->primitive.cylinder.rot = f(d, c->primitive.cylinder.rot, mvdata);
}

void	rot_cone(float d, t_obj *c, t_mvdata mvdata,
	cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	c->primitive.cylinder.pos = f(d, c->primitive.cylinder.pos, mvdata);
	c->primitive.cylinder.rot = f(d, c->primitive.cylinder.rot, mvdata);
}