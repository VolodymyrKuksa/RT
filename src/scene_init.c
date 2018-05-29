/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:27:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/28 15:27:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern int	g_win_width;
extern int	g_win_height;

void	init_scene(t_scene *scene)
{
	t_sphere	tmp;

	scene->num_obj = 3;
	scene->obj = (t_sphere*)malloc(sizeof(t_sphere) * scene->num_obj);

	tmp.pos.x = -5;
	tmp.pos.y = -5;
	tmp.pos.z = -50;
	tmp.col.x = 1.0f;
	tmp.col.y = 0.5f;
	tmp.col.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 10;
	scene->obj[0] = tmp;

	tmp.pos.x = 5;
	tmp.pos.y = -5;
	tmp.pos.z = -50;
	tmp.col.x = 0.5f;
	tmp.col.y = 1.0f;
	tmp.col.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 10;
	scene->obj[1] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 13;
	tmp.pos.z = -50;
	tmp.col.x = 1.0f;
	tmp.col.y = 1.0f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 1;
	tmp.emission.y = 1;
	tmp.emission.z = 1;
	tmp.r = 5;
	scene->obj[2] = tmp;


	scene->cam.pos.x = 0;
	scene->cam.pos.y = 0;
	scene->cam.pos.z = 0;
	scene->cam.dir.x = 0;
	scene->cam.dir.y = 0;
	scene->cam.dir.z = -1;
	scene->cam.updir.x = 0;
	scene->cam.updir.y = 1;
	scene->cam.updir.z = 0;
	scene->cam.ldir.x = -1;
	scene->cam.ldir.y = 0;
	scene->cam.ldir.z = 0;
	scene->cam.f_length = 935.0f;
	scene->cam.aperture = 0;
	scene->cam.pr_pl_w = g_win_width;
	scene->cam.pr_pl_h = g_win_height;
}