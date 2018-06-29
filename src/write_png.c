/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_png.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 16:38:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/29 16:38:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

char	*get_name(unsigned int num_samples)
{
	char	*str;
	char	*tmp;

	tmp = ft_itoa(num_samples);
	str = ft_strjoin("RT_", tmp);
	free(tmp);
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, "_samples.png");
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}

void	write_png(t_env *env)
{
	char	*name;

	name = get_name(env->num_samples);
	if (!name)
	{
		ft_putendl("Failed to save image :(");
		return;
	}
	SDL_Surface *srf = SDL_CreateRGBSurface(0, g_win_width, g_win_height,
		32, 0, 0, 0, 0);
	ft_memcpy(srf->pixels, env->screen.surface->pixels, srf->h * srf->pitch);
	IMG_SavePNG(srf, name);
	ft_putstr("Saved image ");
	ft_putendl(name);
	free(name);
	SDL_FreeSurface(srf);
}
