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
}

void			check_camera2(t_cam *cam)
{
	if (cam->filter.x == 0 && cam->filter.y == 0 && cam->filter.z == 0)
		ft_putstr("warning! filter cannot be all zeros\n");
	if (cam->filter.x < 0 || cam->filter.x > 1)
		error_fedun("filter.x must be 0 <= x <= 1\n");
	if (cam->filter.y < 0 || cam->filter.y > 1)
		error_fedun("filter.y must be 0 <= y <= 1\n");
	if (cam->filter.z < 0 || cam->filter.z > 1)
		error_fedun("filter.z must be 0 <= z <= 1\n");
	if (cam->brightness <= 0 || cam->brightness > 10)
	{
		ft_putstr("setting brightness to default = 1\n");
		cam->brightness = 1.0f;
	}
	if (cam->refr_coef < 1 || cam->refr_coef > 2)
		error_fedun("refr_coef of camera is bad. 1 <= x <= 2");
}

void			check_camera(t_cam *cam)
{
	check_camera2(cam);
	if (cam->fov <= 10.0 || cam->fov >= 160.0)
	{
		ft_putstr("fov of camera is wrong. setting to default 90..\n");
		cam->fov = 90.0;
	}
	if (cam->aperture < 0.f || cam->aperture >= 100.0)
	{
		ft_putstr("aperture of camera is wrong. setting to def n0.00001..\n");
		cam->aperture = 0.00001f;
	}
	cam->updir.x = 0;
	cam->updir.y = 1;
	cam->updir.z = 0;
	cam->ldir.x = -1;
	cam->ldir.y = 0;
	cam->ldir.z = 0;
	cam->ratio = cam->f_length / calculate_ppd(cam->fov);
	cam->pr_pl_w = g_win_width;
	cam->pr_pl_h = g_win_height;
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
		i++;
	}
	check_camera(&(scene->cam));
	printf(" cam pos x  %f\n", scene->cam.pos.x);
	printf(" cam pos y  %f\n", scene->cam.pos.y);
	printf(" cam pos z  %f\n", scene->cam.pos.z);
	printf(" cam dir x  %f\n", scene->cam.dir.x);
	printf(" cam dir y  %f\n", scene->cam.dir.y);
	printf(" cam dir z  %f\n", scene->cam.dir.z);
	printf(" cam f_length  %f\n", scene->cam.f_length);
	printf(" cam dust  %f\n", scene->cam.dust);
	printf(" cam brightness  %f\n", scene->cam.brightness);
	printf(" cam fov  %f\n", scene->cam.fov);
	printf(" cam aperture  %f\n", scene->cam.aperture);
	printf(" refr_coef  %f\n", scene->cam.refr_coef);
	scene->cam.effect = NOEFFECT;
}
