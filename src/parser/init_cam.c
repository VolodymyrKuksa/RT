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
#include "parser.h"

extern int	g_win_width;
extern int	g_win_height;

void			camera_default(t_cam *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 0;
	cam->dir.x = 0;
	cam->dir.y = 0;
	cam->dir.z = -1;
	cam->f_length = 60.0f;
	cam->aperture = 0.00001f;
	cam->fov = 90;
	cam->dust = 0.f;
//	cam->filter = (cl_float3){1.f, 1.f, 1.f};
}

void			check_camera(t_cam *cam)
{
	if (cam->fov <= 10.0 || cam->fov >= 160.0)
	{
		ft_putstr("fov of camera is wrong. setting to default 90..\n");
		printf("\n%f\n", cam->fov);
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
	if (ft_strcmp(name, "dir x") == 0)
		scene->cam.dir.x = (cl_float)SUKA(v.u.dbl, 0.0f);
	if (ft_strcmp(name, "dir y") == 0)
		scene->cam.dir.y = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "dir z") == 0)
		scene->cam.dir.z = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "f_length") == 0)
		scene->cam.f_length = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "dust") == 0)
		scene->cam.dust = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "fov") == 0)
		scene->cam.fov = (cl_float)v.u.dbl;
	if (ft_strcmp(name, "aperture") == 0)
		scene->cam.aperture = (float)v.u.dbl;
}

void			get_camera_params(json_value *value, t_scene *scene)
{
	int			i;
	json_value	v;

	i = 0;
	if (value->u.object.length != 10)
		error_fedun("wrong number of parameters in scene");
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
	printf(" cam fov  %f\n", scene->cam.fov);
	printf(" cam aperture  %f\n", scene->cam.aperture);
	scene->cam.filter = (cl_float3){1.f,1.f,1.f}; // <- Just do it, Fedun!
	scene->cam.brightness = 1.f; //and this
}
