/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:36:58 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:36:59 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parselight(json_value *value, t_obj *tmp)
{
	int			i;
	json_value	v;

	i = 0;
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		if (!ft_strcmp(value->u.object.values[i].name, "emission x"))
			tmp->emission.x = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "emission y"))
			tmp->emission.y = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "emission z"))
			tmp->emission.z = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "roughness"))
			tmp->roughness = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "diffuse"))
			tmp->diffuse = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "specular"))
			tmp->specular = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "refraction"))
			tmp->refraction = (cl_float)v.u.dbl;
		i++;
	}
	checksumandemiss(tmp);
}

void			check_tex_offs(cl_float2 tex_offs)
{
	if (tex_offs.x < 0 || tex_offs.x > 1)
		error_fedun("tex_offs x is not correct. 0 <= x <= 1");
	if (tex_offs.y < 0 || tex_offs.y > 1)
		error_fedun("tex_offs y is not correct. 0 <= y <= 1");
}

void			fill_col_distrupt(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "col_disrupt") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("value is absent in key col_disrupt");
		if (ft_strcmp(v.u.string.ptr, "CHESS") == 0)
			tmp->col_disrupt = CHESS;
		if (ft_strcmp(v.u.string.ptr, "NODISTRUPT") == 0 ||
			ft_strcmp(v.u.string.ptr, "") == 0)
			tmp->col_disrupt = NODISRUPT;
		if (ft_strcmp(v.u.string.ptr, "COS") == 0)
			tmp->col_disrupt = COS;
		if (ft_strcmp(v.u.string.ptr, "CIRCLE") == 0)
			tmp->col_disrupt = CIRCLE;
		if (ft_strcmp(v.u.string.ptr, "PERLIN") == 0)
			tmp->col_disrupt = PERLIN;
		if (ft_strcmp(v.u.string.ptr, "PERLIN_BLUE") == 0)
			tmp->col_disrupt = PERLIN_BLUE;
		if (ft_strcmp(v.u.string.ptr, "PERLIN_RED") == 0)
			tmp->col_disrupt = PERLIN_RED;
		if (ft_strcmp(v.u.string.ptr, "PERLIN_GREEN") == 0)
			tmp->col_disrupt = PERLIN_GREEN;
	}
	if (tmp->emission.x != 0.0 || tmp->emission.y != 0.0 ||
		tmp->emission.z != 0.0)
		tmp->col_disrupt = NODISRUPT;
}

void			fill_textures(char *name, t_obj *tmp, json_value v)
{
	if (ft_strcmp(name, "texture") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("texture path is missing");
		tmp->tex_id = load_texture(v.u.string.ptr);
	}
	if (ft_strcmp(name, "material texture") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("material  texture path is missing");
		tmp->mater_tex_id = load_texture(v.u.string.ptr);
	}
}

void			fill_common(char *name, t_obj *tmp,
							json_value *v, cl_float3 *rot)
{
	fill_color(name, (cl_float)(v->u.dbl), tmp);
	fill_basis(name, tmp, (cl_float)(v->u.dbl));
	if (ft_strcmp(name, "light") == 0)
		parselight(v, tmp);
	fill_textures(name, tmp, *v);
	if (ft_strcmp(name, "rot x") == 0)
		rot->x = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "rot y") == 0)
		rot->y = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "rot z") == 0)
		rot->z = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "tex_offs x") == 0)
		tmp->tex_offs.x = (cl_float)v->u.dbl;
	if (ft_strcmp(name, "tex_offs y") == 0)
		tmp->tex_offs.y = (cl_float)v->u.dbl;
	fill_col_distrupt(name, *v, tmp);
	check_tex_offs(tmp->tex_offs);
}
