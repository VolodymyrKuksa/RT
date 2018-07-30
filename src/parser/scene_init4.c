/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:37:28 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:37:29 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			fill_basis(char *name, t_obj *tmp, cl_float v)
{
	if (ft_strcmp(name, "u x") == 0)
		tmp->basis.u.x = v;
	if (ft_strcmp(name, "u y") == 0)
		tmp->basis.u.y = v;
	if (ft_strcmp(name, "u z") == 0)
		tmp->basis.u.z = v;
	if (ft_strcmp(name, "v x") == 0)
		tmp->basis.v.x = v;
	if (ft_strcmp(name, "v y") == 0)
		tmp->basis.v.y = v;
	if (ft_strcmp(name, "v z") == 0)
		tmp->basis.v.z = v;
	if (ft_strcmp(name, "w x") == 0)
		tmp->basis.w.x = v;
	if (ft_strcmp(name, "w y") == 0)
		tmp->basis.w.y = v;
	if (ft_strcmp(name, "w z") == 0)
		tmp->basis.w.z = v;
}
