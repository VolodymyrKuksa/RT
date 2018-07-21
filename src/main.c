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
//	printf("samples: %u, influence: %f\n", env->num_samples, sample_influence);
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
		//check out messages from clients
		if (env->mv_data.move_keys)
			movement_events(env);
		cl_exec(&env->cl);
		update_window(env);
	}
}

int		main(int argc, char **argv)
{
	t_env	env;

	init_opencl(&env.cl);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	init_defaults(&env);
	init_scene(&env.scene, argc, argv);
	if (parse_server_data(argc, argv, &env.server))
		run_server(&env);
	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen);
	main_loop(&env);
	quit_server(&env.server);
	close_sdl(&env.screen);
	IMG_Quit();
	write_scene(&env.scene);
	print_scene(&env.scene);
	system("leaks -q RT"); //DEBUG
	return (0);
}
