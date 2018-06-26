/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clvec_rot_y.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:30:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 17:30:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

cl_float3	clvec_rot_y(cl_float3 v, double a)
{
	cl_float3	r;

	r.x = (float)(v.x * cos(a) + v.z * sin(a));
	r.y = v.y;
	r.z = (float)(v.z * cos(a) - v.x * sin(a));
	return (r);
}
