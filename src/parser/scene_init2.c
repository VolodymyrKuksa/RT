/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:35:29 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:35:30 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			rot_pos_cam(cl_float3 *pos, cl_float3 rot)
{
	*pos = clvec_rot_x(*pos, DTR(-rot.x));
	*pos = clvec_rot_y(*pos, DTR(-rot.y));
	*pos = clvec_rot_z(*pos, DTR(-rot.z));
}

void			rotate_obj_by_camera(t_obj *tmp, cl_float3 rot)
{
	if (tmp->type == paraboloid)
	{
		rot_pos_cam(&(tmp->primitive.paraboloid.pos), rot);
	}
	else if (tmp->type == triangle)
	{
		rot_pos_cam(&(tmp->primitive.triangle.d1), rot);
		rot_pos_cam(&(tmp->primitive.triangle.d2), rot);
		rot_pos_cam(&(tmp->primitive.triangle.d3), rot);
	}
	else
	{
		rot_pos_cam(&(tmp->primitive.sphere.pos), rot);
	}
	init_rotate(&tmp->basis, (cl_float3){{-rot.x, -rot.y, -rot.z}});
}

void			rotate_scene_by_cam(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < scene->num_obj)
	{
		rotate_obj_by_camera(&scene->obj[i], scene->cam.rot);
		i++;
	}
}
