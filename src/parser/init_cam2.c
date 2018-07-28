/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:09:32 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:09:33 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern int	g_win_width;
extern int	g_win_height;

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
	if (cam->brightness <= 0 || cam->brightness >= 10)
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
