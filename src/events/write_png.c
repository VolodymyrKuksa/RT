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

extern unsigned int	g_win_width;
extern unsigned int	g_win_height;

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

t_rgb	*get_pixels(cl_float3 *px_host)
{
	t_rgb			*pixels;
	unsigned int	i;
	unsigned int	size;

	size = g_win_height *g_win_width;
	if (!(pixels = (t_rgb*)malloc(sizeof(t_rgb) * size)))
		return NULL;
	i = 0;
	while (i < size)
	{
		pixels[i].bgra[0] = (u_char)(px_host[i].z * 0xff);
		pixels[i].bgra[1] = (u_char)(px_host[i].y * 0xff);
		pixels[i].bgra[2] = (u_char)(px_host[i].x * 0xff);
		i++;
	}
	return (pixels);
}

void	write_png(t_env *env)
{
	char		*name;
	SDL_Surface	*srf;
	t_rgb		*pixels;

	pixels = get_pixels(env->cl.pixels);
	name = get_name(env->num_samples);
	if (!name || !pixels)
	{
		ft_putendl("Failed to save image :(");
		return ;
	}
	srf = SDL_CreateRGBSurface(0, g_win_width, g_win_height,
		32, 0, 0, 0, 0);
	ft_memcpy(srf->pixels, pixels,
		g_win_width * g_win_height * sizeof(t_rgb));
	free(pixels);
	IMG_SavePNG(srf, name);
	ft_putstr("Saved image ");
	ft_putendl(name);
	free(name);
	SDL_FreeSurface(srf);
}
