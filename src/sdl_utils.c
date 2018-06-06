/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:01:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/28 13:01:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int	g_win_width; /* extern^ help me with it*/
extern unsigned int g_win_height;

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
		SDL_WINDOWPOS_UNDEFINED, g_win_width, g_win_height,
		SDL_WINDOW_SHOWN);
		if (screen->window == NULL)
		{
			ft_putstr("Window could not be created! Error: ");
			ft_putendl(SDL_GetError());
			return (0);
		}
		else
			screen->surface = SDL_GetWindowSurface(screen->window); /*fast ????*/
	}
	screen->surf_arr = (t_rgb *)screen->surface->pixels;
	return (1);
}

void	close_sdl(t_scrn *screen)
{
	SDL_FreeSurface(screen->surface);
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
}
