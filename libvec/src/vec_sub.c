/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 19:07:29 by vkuksa            #+#    #+#             */
/*   Updated: 2018/03/13 19:07:31 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"

t_vec	vec_sub(t_vec a, t_vec b)
{
	b = vec_scale(b, -1);
	return (vec_add(a, b));
}
