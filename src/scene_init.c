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

	scene->num_obj = 13;
	scene->obj = (t_sphere*)malloc(sizeof(t_sphere) * scene->num_obj);

	tmp.pos.x = 0;
	tmp.pos.y = 0;
	tmp.pos.z = -600;
	tmp.col.x = 1.f;
	tmp.col.y = 1.f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 1.f;
	tmp.surf.type.x = 0.f;
	tmp.surf.type.y = 1.f;
	tmp.surf.type.z = 0.f;
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
	tmp.surf.roughness = 1.f;
	tmp.surf.type.x = 1.f;
	tmp.surf.type.y = 0.f;
	tmp.surf.type.z = 0.f;
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
	tmp.surf.roughness = 1.f;
	tmp.surf.type.x = 1.f;
	tmp.surf.type.y = 0.f;
	tmp.surf.type.z = 0.f;
	tmp.r = 490;
	scene->obj[2] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 500;
	tmp.pos.z = 0;
	tmp.col.x = 1.0f;
	tmp.col.y = 1.0f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 1.f;
	tmp.surf.type.x = 1.f;
	tmp.surf.type.y = 0.f;
	tmp.surf.type.z = 0.f;
	tmp.r = 490;
	scene->obj[3] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = -500;
	tmp.pos.z = 0;
	tmp.col.x = 1.0f;
	tmp.col.y = 0.5f;
	tmp.col.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 1.f;
	tmp.surf.type.x = 1.f;
	tmp.surf.type.y = 0.f;
	tmp.surf.type.z = 0.f;
	tmp.r = 490;
	scene->obj[4] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 0;
	tmp.pos.z = 500;
	tmp.col.x = 1.0f;
	tmp.col.y = 0.0f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 1.f;
	tmp.surf.type.x = 1.f;
	tmp.surf.type.y = 0.f;
	tmp.surf.type.z = 0.f;
	tmp.r = 490;
	scene->obj[5] = tmp;

	tmp.pos.x = 0;
	tmp.pos.y = 13;
	tmp.pos.z = -60;
	tmp.col.x = 1.0f;
	tmp.col.y = 1.0f;
	tmp.col.z = 1.0f;
	tmp.emission.x = 12;
	tmp.emission.y = 12;
	tmp.emission.z = 12;
	tmp.r = 4;
	scene->obj[6] = tmp;

	tmp.pos.x = 2.5;
	tmp.pos.y = 0;
	tmp.pos.z = -60;
	tmp.col.x = 1.f;
	tmp.col.y = 1.f;
	tmp.col.z = 0.3f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.refraction = 1.5f;
	tmp.surf.roughness = 0.02f;
	tmp.surf.type.x = 0.5f;
	tmp.surf.type.y = 0.5f;
	tmp.surf.type.z = 0.f;
	tmp.r = 5;
	scene->obj[7] = tmp;

	tmp.pos.x = -2;
	tmp.pos.y = -2;
	tmp.pos.z = -40;
	tmp.col.x = 1.f;
	tmp.col.y = 1.f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 0.1f;
	tmp.surf.refraction = 2.f;
	tmp.surf.type.x = 0.9f;
	tmp.surf.type.y = 0.1f;
	tmp.surf.type.z = 0.f;
	tmp.r = 3;
	scene->obj[8] = tmp;

	tmp.pos.x = -5;
	tmp.pos.y = 3;
	tmp.pos.z = -60;
	tmp.col.x = 1.f;
	tmp.col.y = 1.f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 0.f;
	tmp.surf.refraction = 2.f;
	tmp.surf.type.x = 0.f;
	tmp.surf.type.y = 1.f;
	tmp.surf.type.z = 0.f;
	tmp.r = 3.5;
	scene->obj[9] = tmp;

	tmp.pos.x = 5;
	tmp.pos.y = -3;
	tmp.pos.z = -50;
	tmp.col.x = 1.f;
	tmp.col.y = 0.9f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 0.f;
	tmp.surf.refraction = 1.5f;
	tmp.surf.type.x = 0.1f;
	tmp.surf.type.y = 0.1f;
	tmp.surf.type.z = 0.8f;
	tmp.r = 3;
	scene->obj[10] = tmp;

	tmp.pos.x = -8;
	tmp.pos.y = -7;
	tmp.pos.z = -40;
	tmp.col.x = 1.f;
	tmp.col.y = 0.9f;
	tmp.col.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 0.f;
	tmp.surf.refraction = 1.5f;
	tmp.surf.type.x = 0.1f;
	tmp.surf.type.y = 0.1f;
	tmp.surf.type.z = 0.8f;
	tmp.r = 3;
	scene->obj[11] = tmp;

	tmp.pos.x = 0.5;
	tmp.pos.y = 4.5;
	tmp.pos.z = -80;
	tmp.col.x = 1.f;
	tmp.col.y = 0.5f;
	tmp.col.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.surf.roughness = 0.f;
	tmp.surf.refraction = 1.5f;
	tmp.surf.type.x = 1.f;
	tmp.surf.type.y = 0.f;
	tmp.surf.type.z = 0.f;
	tmp.r = 4;
	scene->obj[12] = tmp;

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
	scene->cam.f_length = 60.0f;
	scene->cam.aperture = 0.f;
	scene->cam.ratio = scene->cam.f_length / 1400.0f; //935.f for 60 degree fov
	scene->cam.pr_pl_w = g_win_width;
	scene->cam.pr_pl_h = g_win_height;
//	printf("ratio: %f\n", scene->cam.ratio);
}