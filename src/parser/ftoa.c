/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 12:32:28 by afedun            #+#    #+#             */
/*   Updated: 2018/07/21 12:32:30 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		powk(int x, unsigned int y)
{
	if (y == 0)
		return (1);
	else if (y % 2 == 0)
		return (powk(x, y / 2) * powk(x, y / 2));
	else
		return (x * powk(x, y / 2) * powk(x, y / 2));
}

void			ftoa(float flt, int after_point, int xy, int fd)
{
	int			mut_ab;
	int			after_point_flt;
	int			multiplier;
	int			muted;

	if (flt < 0)
	{
		ft_putchar_fd('-', fd);
		flt = -flt;
	}
	ft_putnbr_fd((int)flt, fd);
	ft_putchar_fd('.', fd);
	mut_ab = powk(10, (unsigned int)after_point);
	after_point_flt = (int)(flt * mut_ab);
	multiplier = powk(10, (unsigned int)(after_point - 1));
	while (xy++ < after_point)
	{
		muted = (after_point_flt/multiplier);
		muted = abs(muted % 10);
		ft_putnbr_fd(muted, fd);
		multiplier /= 10;
	}
}
