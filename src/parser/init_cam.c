/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 12:33:05 by afedun            #+#    #+#             */
/*   Updated: 2018/07/18 12:33:06 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <json.h>
#include "rt.h"

extern int	g_win_width;
extern int	g_win_height;

void			camera_default(t_cam *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 0;
	cam->f_length = 60.0f;
	cam->aperture = 0.00001f;
	cam->fov = 90;
	cam->dust = 0.f;
	cam->filter = (cl_float3){1.f, 1.f, 1.f};
	cam->rot = (cl_float3){0.0, 0.0, 0.0};
	cam->brightness = 1.f;
	cam->refr_coef = 1.5f;
	cam->effect = NOEFFECT;
}

void			fill_cam_effect(char *name, json_value v, t_cam *cam)
{
	if (ft_strcmp(name, "effect") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("effect field is missing");
		if (ft_strcmp(v.u.string.ptr, "NOEFFECT") == 0
			|| ft_strcmp(name, "") == 0)
			cam->effect = NOEFFECT;
		if (ft_strcmp(v.u.string.ptr, "BLACK_N_WHITE") == 0)
			cam->effect = BLACK_N_WHITE;
		if (ft_strcmp(v.u.string.ptr, "NEGATIVE") == 0)
			cam->effect = NEGATIVE;
		if (ft_strcmp(v.u.string.ptr, "SEPIA") == 0)
			cam->effect = SEPIA;
		if (ft_strcmp(v.u.string.ptr, "CARTOON") == 0)
			cam->effect = CARTOON;
	}
}

void			get_cam_params2(char *name, json_value v, t_scene *scene)
{
	if (ft_strcmp(name, "f_length") == 0)
		scene->cam.f_length = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "dust") == 0)
		scene->cam.dust = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "fov") == 0)
		scene->cam.fov = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "aperture") == 0)
		scene->cam.aperture = (float)v.u.dbl;
	if (ft_strcmp(name, "brightness") == 0)
		scene->cam.brightness = (float)v.u.dbl;
	if (ft_strcmp(name, "filter x") == 0)
		scene->cam.filter.x = (float)v.u.dbl;
	if (ft_strcmp(name, "filter y") == 0)
		scene->cam.filter.y = (float)v.u.dbl;
	if (ft_strcmp(name, "filter z") == 0)
		scene->cam.filter.z = (float)v.u.dbl;
	if (ft_strcmp(name, "rot x") == 0)
		scene->cam.rot.x = (float)v.u.dbl;
	if (ft_strcmp(name, "rot y") == 0)
		scene->cam.rot.y = (float)v.u.dbl;
	if (ft_strcmp(name, "rot z") == 0)
		scene->cam.rot.z = (float)v.u.dbl;
	if (ft_strcmp(name, "refr_coef") == 0)
		scene->cam.refr_coef = (float)v.u.dbl;
}

void			get_camera_params(json_value *value, t_scene *scene)
{
	int			i;
	json_value	v;

	i = 0;
	camera_default(&(scene->cam));
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
					(cl_float)v.u.dbl, &(scene->cam.pos));
		get_cam_params2(value->u.object.values[i].name, v, scene);
		fill_cam_effect(value->u.object.values[i].name, v, &scene->cam);
		i++;
	}
	check_camera(&(scene->cam));
}
