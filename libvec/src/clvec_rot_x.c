/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clvec_rot_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:50:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 16:50:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

cl_float3	clvec_rot_x(cl_float3 v, double a)
{
	cl_float3	r;

	r.x = v.x;
	r.y = (float)(v.y * cos(a) - v.z * sin(a));
	r.z = (float)(v.y * sin(a) + v.z * cos(a));
	return (r);
}
