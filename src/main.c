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

void	init_seeds(t_seeds *s)
{
	int		i;

	s->size = (uint)(g_win_height * g_win_width * 2);
	s->seeds = (uint*)malloc(sizeof(uint) * s->size);
	srand((uint)clock());
	i = -1;
	while (++i < s->size)
		s->seeds[i] = (uint)rand();
}

void	clamp(cl_float3 *px)
{
	px->x = px->x > 1.f ? 1.f : px->x;
	px->y = px->y > 1.f ? 1.f : px->y;
	px->z = px->z > 1.f ? 1.f : px->z;
}

void	update_window(t_env *env)
{
	float		sample_influence;
	int			i;

	++(env->num_samples);
	sample_influence = (1.0f / env->num_samples);
	i = -1;
	while (++i < env->cl.global_size)
	{
//		if(i<100 && env->cl.px_host[i].x == 0.f) {
//			printf("%i (%f|%f|%f)\n", i,env->cl.px_host[i].x, env->cl.px_host[i].y,
//				   env->cl.px_host[i].z);
//		}
		env->cl.pixels[i].x *= 1.0f - sample_influence;
		env->cl.pixels[i].y *= 1.0f - sample_influence;
		env->cl.pixels[i].z *= 1.0f - sample_influence;
		env->cl.pixels[i].x += env->cl.px_host[i].x * sample_influence;
		env->cl.pixels[i].y += env->cl.px_host[i].y * sample_influence;
		env->cl.pixels[i].z += env->cl.px_host[i].z * sample_influence;
		clamp(env->cl.pixels + i);
		env->screen.surf_arr[i].bgra[0] = (u_char)(env->cl.pixels[i].z * 0xff);
		env->screen.surf_arr[i].bgra[1] = (u_char)(env->cl.pixels[i].y * 0xff);
		env->screen.surf_arr[i].bgra[2] = (u_char)(env->cl.pixels[i].x * 0xff);
	}
	printf("samples: %u, influence: %f\n", env->num_samples, sample_influence);
	SDL_UpdateWindowSurface(env->screen.window);
}

void	main_loop(t_env *env)
{
	SDL_Event	e;

	cl_setup(env);
	while (!(env->mv_data.move_keys & KEY_ESC))
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				env->mv_data.move_keys |= KEY_ESC;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				keyboard_event(e, env);
			else if (e.type == SDL_WINDOWEVENT)
				window_event(e, env);
		}
		if (env->mv_data.move_keys)
			movement_events(env);
		cl_exec(&env->cl);
		update_window(env);
//		if (env->num_samples == 500)
//			exit(0);
	}
}

void init_torus(t_scene *scene)
{
	t_obj tmp;
	scene->num_obj = 5;
	scene->obj = (t_obj *)malloc(sizeof(t_obj) * scene->num_obj);

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){0.0, 0.0, 1.0};
	tmp.basis.w = (cl_float3){1.0, 0.0, 0.0};
	tmp.primitive.torus.pos.x = 0;
	tmp.primitive.torus.pos.y = 0;
	tmp.primitive.torus.pos.z = -30;
	tmp.primitive.torus.r = 1.f;
	tmp.primitive.torus.R = 60.f;
	tmp.color.x = 0.f;
	tmp.color.y = 1.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = torus;
	tmp.tex_id = -1;
	scene->obj[0] = tmp;

	tmp.basis.u = (cl_float3){0.0, 0.0, 1.0};
	tmp.basis.v = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.w = (cl_float3){1.0, 0.0, 0.0};
	tmp.primitive.torus.pos.x = 0;
	tmp.primitive.torus.pos.y = 0;
	tmp.primitive.torus.pos.z = -30;
	tmp.primitive.torus.r = 1.f;
	tmp.primitive.torus.R = 60.f;
	tmp.color.x = 1.f;
	tmp.color.y = 0.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = torus;
	tmp.tex_id = -1;
	scene->obj[1] = tmp;

	tmp.basis.u = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.v = (cl_float3){0.0, 0.0, 1.0};
	tmp.basis.w = (cl_float3){0.0, 1.0, 0.0};
	tmp.primitive.torus.pos.x = 0;
	tmp.primitive.torus.pos.y = 0;
	tmp.primitive.torus.pos.z = -30;
	tmp.primitive.torus.r = 1.f;
	tmp.primitive.torus.R = 60.f;
	tmp.color.x = 0.f;
	tmp.color.y = 0.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = torus;
	tmp.tex_id = -1;
	scene->obj[2] = tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = -30;
	tmp.primitive.sphere.r = 20;
	tmp.color.x = 0.f;
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
	scene->obj[3] = tmp;


	tmp.basis.u = (cl_float3){0.0, 0.0, 1.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 1.0, 0.0};
	tmp.primitive.plane.pos.x = 0;
	tmp.primitive.plane.pos.y = -3000;
	tmp.primitive.plane.pos.z = 3000;
	tmp.color.x = 0.f;
	tmp.color.y = 0.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 12.f;
	tmp.emission.y = 12.f;
	tmp.emission.z = 12.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = plane;
	tmp.tex_id = -1;
	scene->obj[4] = tmp;
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
	init_scene(&env.sc, argc, argv);
//	init_torus(&env.sc);
//	ccamera_default(&env.sc.cam);
	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen);
	main_loop(&env);
	close_sdl(&env.screen);
	IMG_Quit();
	system("leaks -q RT"); //DEBUG
	return (0);
}
