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

void	update_window(cl_float3 *pixels, cl_float3 *px_host, t_scrn *sc, int gs)
{
	static int	num_samples;
	float		sample_influence;
	int			i;

	++num_samples;
	sample_influence = (1.0f / num_samples);
	i = -1;
	while (++i < gs)
	{
		pixels[i].x *= 1.0f - sample_influence;
		pixels[i].y *= 1.0f - sample_influence;
		pixels[i].z *= 1.0f - sample_influence;
		pixels[i].x += px_host[i].x * sample_influence;
		pixels[i].y += px_host[i].y * sample_influence;
		pixels[i].z += px_host[i].z * sample_influence;
		clamp(pixels + i);
		sc->surf_arr[i].bgra[0] = (u_char)(pixels[i].z * 0xff);
		sc->surf_arr[i].bgra[1] = (u_char)(pixels[i].y * 0xff);
		sc->surf_arr[i].bgra[2] = (u_char)(pixels[i].x * 0xff);
	}
	printf("samples: %u, influence: %f\n", num_samples, sample_influence);
	SDL_UpdateWindowSurface(sc->window);
}

void	main_loop(t_scrn *screen, t_cldata *cl)
{
	SDL_Event	e;
	int			quit;

	cl_setup(cl);
	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
			}
		}
		cl_exec(cl);
		update_window(cl->pixels, cl->px_host, screen, (int)cl->global_size);
	}
}

int		main(void)
{
	t_cldata	cl;
	t_scrn		screen;

	init_opencl(&cl);
	init_scene(&cl.sc);
	init_seeds(&cl.seeds);
	get_work_group_size(&cl);
	init_win(&screen);
	main_loop(&screen, &cl);
	close_sdl(&screen);
	return (0);
}
