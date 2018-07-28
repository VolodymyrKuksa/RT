/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:02:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/22 17:02:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

unsigned int	g_win_width = 1080;
unsigned int	g_win_height = 720;







void init_torus(t_scene *scene)
{
	t_obj tmp;
	scene->num_obj = 2;
	scene->obj = (t_obj *)malloc(sizeof(t_obj) * scene->num_obj);

	tmp.basis.u = (cl_float3){0.0, 0.0, 1.0};
	tmp.basis.v = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.w = (cl_float3){1.0, 0.0, 0.0};
//	tmp.primitive.elipsoid.c1 = (cl_float3){-5, -5, -20};
//	tmp.primitive.elipsoid.c2 = (cl_float3){5, 5 ,-20};
	tmp.primitive.sphere.r = 5.f;
	tmp.primitive.sphere.pos = (cl_float3){5, 5 ,-20};
	tmp.color.x = 1.f;
	tmp.color.y = 0.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	tmp.tex_id = -1;
	scene->obj[0] = tmp;

	tmp.basis.u = (cl_float3){0.0, 0.0, 1.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 1.0, 0.0};
	tmp.primitive.plane.pos.x = 0;
	tmp.primitive.plane.pos.y = -3000;
	tmp.primitive.plane.pos.z = 3000;
	tmp.color.x = 0.f;
	tmp.color.y = 0.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 1.f;
	tmp.emission.y = 1.f;
	tmp.emission.z = 1.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = plane;
	tmp.tex_id = -1;
	scene->obj[1] = tmp;
}

void	ccamera_default(t_cam *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = -1;
	cam->dir.x = 0;
	cam->dir.y = 0;
	cam->dir.z = -1;
	cam->f_length = 60.0f;
	cam->aperture = 0.0000f;
	cam->fov = 90;
	cam->dust = 0.f;
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








int		main(int argc, char **argv)
{
	t_env	env;

	init_opencl(&env.cl);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	init_defaults(&env);
	init_scene(&env.scene, argc, argv);
	compress_texture(&env.textures);
	printf("tx count: %d\n", env.textures.tx_count);
	printf("tx size: %d\n", env.textures.total_size);
	if (parse_server_data(argc, argv, &env.server))
		run_server(&env);
//	ccamera_default(&env.scene.cam);
//	init_torus(&env.scene);

	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen, 1, 1);
	main_loop_server(&env);
	quit_server(&env.server);
	close_sdl(&env.screen);
	IMG_Quit();
	write_scene(&(env.scene));
	system("leaks -q RT"); //DEBUG
	return (0);
}
