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
#define	LENGTH(a) sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
#define NORMAL(a) (cl_float3){a.x/LENGTH(a), a.y/LENGTH(a), a.z/LENGTH(a)} //just for test

void	init_scene(t_scene *scene)
{
	t_obj	tmp;

	scene->num_obj = 15;
	scene->obj = (t_obj*)malloc(sizeof(t_obj) * scene->num_obj);

	tmp.primitive.sphere.pos.x = -5;
	tmp.primitive.sphere.pos.y = -3;
	tmp.primitive.sphere.pos.z = -50;
	tmp.primitive.sphere.r= 4;
	tmp.color.x = 1.f;
	tmp.color.y = 0.5f;
	tmp.color.z = 0.5f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	scene->obj[0] = tmp;

	tmp.primitive.sphere.pos.x = -8;
	tmp.primitive.sphere.pos.y = -7;
	tmp.primitive.sphere.pos.z = -40;
	tmp.primitive.sphere.r= 3;
	tmp.color.x = 1.f;
	tmp.color.y = 0.9f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	scene->obj[1] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = -600;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 0.f;
	tmp.specular = 1.f;
	tmp.refraction = 0.f;
	tmp.primitive.sphere.r= 490;
	tmp.type = sphere;
	scene->obj[2] = tmp;

	tmp.primitive.sphere.pos.x = 500;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 0.5f;
	tmp.color.y = 1.0f;
	tmp.color.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[3] = tmp;

	tmp.primitive.sphere.pos.x = -500;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 0.5f;
	tmp.color.y = 0.5f;
	tmp.color.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[4] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 500;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 1.0f;
	tmp.color.y = 1.0f;
	tmp.color.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[5] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = -500;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 1.0f;
	tmp.color.y = 0.5f;
	tmp.color.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[6] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = 500;
	tmp.color.x = 1.0f;
	tmp.color.y = 0.0f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[7] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 13;
	tmp.primitive.sphere.pos.z = -60;
	tmp.color.x = 1.0f;
	tmp.color.y = 1.0f;
	tmp.color.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 4;
	scene->obj[8] = tmp;

	tmp.primitive.sphere.pos.x = 2.5;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = -60;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 0.3f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0.02f;
	tmp.diffuse = 0.5f;
	tmp.specular = 0.5f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 5;
	scene->obj[9] = tmp;

	tmp.primitive.sphere.pos.x = -2;
	tmp.primitive.sphere.pos.y = -2;
	tmp.primitive.sphere.pos.z = -40;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0.1f;
	tmp.diffuse = 0.9f;
	tmp.specular = 0.1f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 3;
	scene->obj[10] = tmp;

	tmp.primitive.sphere.pos.x = -5;
	tmp.primitive.sphere.pos.y = 3;
	tmp.primitive.sphere.pos.z = -60;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0.f;
	tmp.diffuse = 0.2f;
	tmp.specular = 0.8f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 3.5;
	scene->obj[11] = tmp;

	tmp.primitive.cylinder.pos.x = -5;
	tmp.primitive.cylinder.pos.y = 3;
	tmp.primitive.cylinder.pos.z = -60;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 3;
	tmp.emission.y = 3;
	tmp.emission.z = 3;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.primitive.cylinder.r = 2;
	tmp.primitive.cylinder.rot.x = 0;
	tmp.primitive.cylinder.rot.y = 1;
	tmp.primitive.cylinder.rot.z = 0;
	tmp.type = cylinder;
	scene->obj[12] = tmp;

	tmp.primitive.cone.pos.x = -2;
	tmp.primitive.cone.pos.y = -2;
	tmp.primitive.cone.pos.z = -40;
	tmp.primitive.cone.rot.x = 1;
	tmp.primitive.cone.rot.y = 0;
	tmp.primitive.cone.rot.z = 0;
	tmp.primitive.cone.tng = 0.1;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 3;
	tmp.emission.y = 3;
	tmp.emission.z = 3;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = cone;
	scene->obj[13] = tmp;

	tmp.primitive.plane.pos.x = 10;
	tmp.primitive.plane.pos.y = -10;
	tmp.primitive.plane.pos.z = 0;
	tmp.primitive.plane.rot.x = -1;
	tmp.primitive.plane.rot.y = 1;
	tmp.primitive.plane.rot.z = 0;
	tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0.5;
	tmp.emission.y = 0.5;
	tmp.emission.z = 0.5;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = plane;
	scene->obj[14] = tmp;

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
	scene->cam.aperture = 0.00001f;
	scene->cam.ratio = scene->cam.f_length / 935.0f; //935.f for 60 degree fov
	scene->cam.pr_pl_w = g_win_width;
	scene->cam.pr_pl_h = g_win_height;
	scene->cam.dust = 0.f;
	printf("ratio: %f\n", scene->cam.ratio);
}
