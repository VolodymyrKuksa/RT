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

int		init_win(t_scrn *screen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putstr("SDL could not initialize! Error: ");
		ft_putendl(SDL_GetError());
		return (0);
	}
	else
	{
		screen->window = SDL_CreateWindow("CANCER RT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		if (screen->window == NULL)
		{
			ft_putstr("Window could not be created! Error: ");
			ft_putendl(SDL_GetError());
			return (0);
		}
		else
			screen->surface = SDL_GetWindowSurface(screen->window);
	}
	screen->surf_arr = (unsigned int *)screen->surface->pixels;
	return (1);
}

void	main_loop(t_scrn *screen)
{
	SDL_Event	e;
	int			quit;

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
		SDL_UpdateWindowSurface(screen->window);
	}
}

void	close_sdl(t_scrn *screen)
{
	SDL_FreeSurface(screen->surface);
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
}

int		main(void)
{
	t_scrn	screen;

	init_win(&screen);
	main_loop(&screen);
	close_sdl(&screen);

	return (0);
}
