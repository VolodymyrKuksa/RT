/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_ppm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 13:18:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/29 13:18:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void	put_header_ppm(int fd)
{
	ft_putendl_fd("P3", fd);
	ft_putnbr_fd(g_win_width, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(g_win_height, fd);
	ft_putchar_fd('\n', fd);
	ft_putendl_fd("256", fd);
}

void	put_pixel_ppm(int fd, cl_float3 px)
{
	int		tmp;

	tmp = (int)(256 * px.x);
	tmp = tmp > 256 ? 256 : tmp;
	ft_putnbr_fd(tmp, fd);
	ft_putchar_fd(' ', fd);
	tmp = (int)(256 * px.y);
	tmp = tmp > 256 ? 256 : tmp;
	ft_putnbr_fd(tmp, fd);
	ft_putchar_fd(' ', fd);
	tmp = (int)(256 * px.z);
	tmp = tmp > 256 ? 256 : tmp;
	ft_putnbr_fd(tmp, fd);
	ft_putchar_fd(' ', fd);
}

int		write_ppm(char *filename, cl_float3 *pixels)
{
	int		fd;
	int		i;
	int		size;

	if ((fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		return (0);
	put_header_ppm(fd);
	size = g_win_width * g_win_height;
	i = -1;
	while (++i < size)
		put_pixel_ppm(fd, pixels[i]);
	return (1);
}
