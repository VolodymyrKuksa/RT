/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clvec_rot_z.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:33:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 17:33:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

cl_float3	clvec_rot_z(cl_float3 v, double a)
{
	cl_float3	r;

	r.x = (float)(v.x * cos(a) - v.y * sin(a));
	r.y = (float)(v.x * sin(a) + v.y * cos(a));
	r.z = v.z;
	return (r);
}
