/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:18:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/23 16:18:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"

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

void			init_rotate(t_basis *basis, cl_float3 rot)
{
	basis->u = clvec_rot_x(basis->u, DTR(rot.x));
	basis->u = clvec_rot_y(basis->u, DTR(rot.y));
	basis->u = clvec_rot_z(basis->u, DTR(rot.z));
	basis->v = clvec_rot_x(basis->v, DTR(rot.x));
	basis->v = clvec_rot_y(basis->v, DTR(rot.y));
	basis->v = clvec_rot_z(basis->v, DTR(rot.z));
	basis->w = clvec_rot_x(basis->w, DTR(rot.x));
	basis->w = clvec_rot_y(basis->w, DTR(rot.y));
	basis->w = clvec_rot_z(basis->w, DTR(rot.z));
}

void			checksumandemiss(t_obj *tmp)
{
	float		sum;

	tmp->diffuse = fabs(tmp->diffuse);
	tmp->specular = fabs(tmp->specular);
	tmp->refraction = fabs(tmp->refraction);
	if (tmp->diffuse == 0 && tmp->specular == 0 && tmp->refraction == 0)
		error_fedun("cannot be all zeros");
	sum = tmp->diffuse + tmp->specular + tmp->refraction;
	tmp->diffuse = tmp->diffuse / sum;
	tmp->specular = tmp->specular / sum;
	tmp->refraction = tmp->refraction / sum;
	if ((tmp->emission.x == 0.0f || tmp->emission.x >= 1.0f) &&
		(tmp->emission.y == 0.0f || tmp->emission.y >= 1.0f) &&
		(tmp->emission.z == 0.0f || tmp->emission.z >= 1.0f))
		return ;
	else
		error_fedun("emission > 1 or == 0");
	if (tmp->emission.x > 5.0f || tmp->emission.y > 5.0f ||
		tmp->emission.z > 5.0f)
		error_fedun("emission < 5");
}
