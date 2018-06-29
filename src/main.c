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

void	update_window(t_cldata *cl)
{
	float		sample_influence;
	int			i;

	++(cl->num_samples);
	sample_influence = (1.0f / cl->num_samples);
	i = -1;
	while (++i < cl->global_size)
	{
		cl->pixels[i].x *= 1.0f - sample_influence;
		cl->pixels[i].y *= 1.0f - sample_influence;
		cl->pixels[i].z *= 1.0f - sample_influence;
		cl->pixels[i].x += cl->px_host[i].x * sample_influence;
		cl->pixels[i].y += cl->px_host[i].y * sample_influence;
		cl->pixels[i].z += cl->px_host[i].z * sample_influence;
		clamp(cl->pixels + i);
		cl->screen.surf_arr[i].bgra[0] = (u_char)(cl->pixels[i].z * 0xff);
		cl->screen.surf_arr[i].bgra[1] = (u_char)(cl->pixels[i].y * 0xff);
		cl->screen.surf_arr[i].bgra[2] = (u_char)(cl->pixels[i].x * 0xff);
	}
	printf("samples: %u, influence: %f\n", cl->num_samples, sample_influence);
	SDL_UpdateWindowSurface(cl->screen.window);
}

void	main_loop(t_cldata *cl)
{
	SDL_Event	e;

	cl_setup(cl);
	while (!(cl->move_keys & KEY_ESC))
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				cl->move_keys |= KEY_ESC;
			else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
				keyboard_event(e, cl);
		}
		if (cl->move_keys)
			movement_events(cl);
		cl_exec(cl);
		update_window(cl);
	}
}

int		main(void)
{
	t_cldata	cl;

	init_opencl(&cl);
	IMG_Init(IMG_INIT_PNG);
	init_defaults(&cl);
	init_scene(&cl.sc);
	init_seeds(&cl.seeds);
	get_work_group_size(&cl);
	init_win(&cl.screen);
	main_loop(&cl);
	close_sdl(&cl.screen);
	IMG_Quit();
	system("leaks -q RT"); //DEBUG
	return (0);
}
