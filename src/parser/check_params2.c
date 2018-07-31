/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:39:15 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:39:16 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

	tmp->diffuse = (cl_float)fabs(tmp->diffuse);
	tmp->specular = (cl_float)fabs(tmp->specular);
	tmp->refraction = (cl_float)fabs(tmp->refraction);
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
	if (tmp->emission.x > 500.0f || tmp->emission.y > 500.0f ||
		tmp->emission.z > 500.0f)
		error_fedun("emission < 500");
}

float			scalar_dobutok(cl_float3 a, cl_float3 b)
{
	float		res;

	res = 0;
	res += a.x * b.x + a.y * b.y + a.z * b.z;
	return ((cl_float)fabs(res));
}

void			check_basis(t_obj *tmp)
{
	if (scalar_dobutok(tmp->basis.u, tmp->basis.v) >= 0.001)
		error_fedun("basis u v is not ortogonal");
	if (scalar_dobutok(tmp->basis.w, tmp->basis.v) >= 0.001)
		error_fedun("basis v w is not ortogonal");
	if (scalar_dobutok(tmp->basis.u, tmp->basis.w) >= 0.001)
		error_fedun("basis u w is not ortogonal");
	tmp->basis.u = NORMAL(tmp->basis.u);
	tmp->basis.v = NORMAL(tmp->basis.v);
	tmp->basis.w = NORMAL(tmp->basis.w);
}
