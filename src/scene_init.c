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

	scene->num_obj = 10;
	scene->obj = (t_sphere*)malloc(sizeof(t_sphere) * scene->num_obj);

	tmp.pos.x = 0;
	tmp.pos.y = 0;
	tmp.pos.z = -750;
	tmp.col.x = 1.0f;
	tmp.col.y = 0.9f;
	tmp.col.z = 0.9f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 490;
	scene->obj[0] = tmp;

	tmp.pos.x = 500;
	tmp.pos.y = 0;
	tmp.pos.z = 0;
	tmp.col.x = 0.5f;
	tmp.col.y = 1.0f;
	tmp.col.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 490;
	scene->obj[1] = tmp;

	tmp.pos.x = -500;
	tmp.pos.y = 0;
	tmp.pos.z = 0;
	tmp.col.x = 0.5f;
	tmp.col.y = 0.5f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 490;
	scene->obj[2] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 0;
	tmp.pos.z = -90;
	tmp.col.x = 1.0f;
	tmp.col.y = 1.0f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 5;
	scene->obj[3] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 500;
	tmp.pos.z = 0;
	tmp.col.x = 1.0f;
	tmp.col.y = 1.0f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 1;
	tmp.emission.y = 1;
	tmp.emission.z = 1;
	tmp.r = 490;
	scene->obj[4] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = -500;
	tmp.pos.z = 0;
	tmp.col.x = 1.0f;
	tmp.col.y = 0.5f;
	tmp.col.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 490;
	scene->obj[5] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 0;
	tmp.pos.z = 500;
	tmp.col.x = 0.0f;
	tmp.col.y = 0.0f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 490;
	scene->obj[6] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 0;
	tmp.pos.z = -90;
	tmp.col.x = 1.0f;
	tmp.col.y = 1.0f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 4;
	scene->obj[7] = tmp;

	tmp.pos.x = 4;
	tmp.pos.y = 4;
	tmp.pos.z = -100;
	tmp.col.x = 0.7f;
	tmp.col.y = 0.7f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 5;
	scene->obj[8] = tmp;

	tmp.pos.x = -4;
	tmp.pos.y = -4;
	tmp.pos.z = -80;
	tmp.col.x = 0.7f;
	tmp.col.y = 1.f;
	tmp.col.z = 0.7f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.r = 5;
	scene->obj[9] = tmp;

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
	scene->cam.f_length = 90.0f;
	scene->cam.aperture = 1.0f;
	scene->cam.ratio = scene->cam.f_length / 935.0f;
	scene->cam.pr_pl_w = g_win_width;
	scene->cam.pr_pl_h = g_win_height;
//	printf("ratio: %f\n", scene->cam.ratio);
}