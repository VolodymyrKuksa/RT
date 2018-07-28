/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:18:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/23 16:18:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			minus_camera(cl_float3 *pos, cl_float3 cam_pos)
{
	pos->x -= cam_pos.x;
	pos->y -= cam_pos.y;
	pos->z -= cam_pos.z;
}

void			fill_position(char *name, cl_float value, cl_float3 *pos)
{
	if (ft_strcmp(name, "pos x") == 0)
		pos->x = value;
	if (ft_strcmp(name, "pos y") == 0)
		pos->y = value;
	if (ft_strcmp(name, "pos z") == 0)
		pos->z = value;
}

void			fill_color(char *name, cl_float value, t_obj *tmp)
{
	if (ft_strcmp(name, "color x") == 0)
		tmp->color.x = value;
	if (ft_strcmp(name, "color y") == 0)
		tmp->color.y = value;
	if (ft_strcmp(name, "color z") == 0)
		tmp->color.z = value;
	if (tmp->color.x < 0 || tmp->color.x > 1)
		error_fedun("0 <= color x <= 1");
	if (tmp->color.y < 0 || tmp->color.y > 1)
		error_fedun("0 <= color y <= 1");
	if (tmp->color.z < 0 || tmp->color.z > 1)
		error_fedun("0 <= color z <= 1");
}
