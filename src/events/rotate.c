/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 13:13:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/27 13:13:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	rotate_x(float dir, cl_float3 v, t_mvdata mv)
{
	cl_float3	r;

	r.x = v.x;
	r.y = (float)(v.y * mv.cosine_a - dir * v.z * mv.sine_a);
	r.z = (float)(v.y * dir * mv.sine_a + v.z * mv.cosine_a);
	return (r);
}

cl_float3	rotate_y(float dir, cl_float3 v, t_mvdata mv)
{
	cl_float3	r;

	r.x = (float)(v.x * mv.cosine_a + v.z * dir * mv.sine_a);
	r.y = v.y;
	r.z = (float)(v.z * mv.cosine_a - v.x * dir * mv.sine_a);
	return (r);
}

cl_float3	rotate_z(float dir, cl_float3 v, t_mvdata mv)
{
	cl_float3	r;

	r.x = (float)(v.x * mv.cosine_a - v.y * dir * mv.sine_a);
	r.y = (float)(v.x * mv.sine_a * dir + v.y * mv.cosine_a);
	r.z = v.z;
	return (r);
}
