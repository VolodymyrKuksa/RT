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
	scene->num_obj = 2;
	scene->obj = (t_sphere*)malloc(sizeof(t_sphere) * scene->num_obj);

	scene->obj[0].pos.x = -5;
	scene->obj[0].pos.y = 0;
	scene->obj[0].pos.z = 0;
	scene->obj[0].col.x = 1.0f;
	scene->obj[0].col.y = 0.5f;
	scene->obj[0].col.z = 0.5f;
	scene->obj[0].emission.x = 0;
	scene->obj[0].emission.y = 0;
	scene->obj[0].emission.z = 0;
	scene->obj[0].r = 10;

	scene->obj[1].pos.x = 5;
	scene->obj[1].pos.y = 0;
	scene->obj[1].pos.z = 0;
	scene->obj[1].col.x = 0.5f;
	scene->obj[1].col.y = 1.0f;
	scene->obj[1].col.z = 0.5f;
	scene->obj[1].emission.x = 0;
	scene->obj[1].emission.y = 0;
	scene->obj[1].emission.z = 0;
	scene->obj[1].r = 10;

	scene->cam.pos.x = 0;
	scene->cam.pos.y = 0;
	scene->cam.pos.z = 50;
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