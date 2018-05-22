/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 18:14:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/22 18:14:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvec.h"
#include <stdio.h> //forbidden

void	vec_print(t_vec v, char *str)
{
	if (str)
		printf("%s x: %lf; y: %lf; z: %lf;\n", str, v.x, v.y, v.z);
	else
		printf("x: %lf; y: %lf; z: %lf;\n", v.x, v.y, v.z);
}