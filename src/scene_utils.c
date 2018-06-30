/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 20:49:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/30 20:49:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int	g_win_width;

float	calculate_ppd(double fov)
{
	float	dist;

	fov /= 2;
	dist = (float)(g_win_width / tan(DTR(fov)));
	return (dist);
}
