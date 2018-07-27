/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:16:04 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:16:05 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			write_cam_effect(t_cam cam, int fd)
{
	ft_putstr_fd("\"effect\": \"", fd);
	if (cam.effect == NOEFFECT)
		ft_putstr_fd("NOEFFECT", fd);
	else if (cam.effect == SEPIA)
		ft_putstr_fd("SEPIA", fd);
	else if (cam.effect == NEGATIVE)
		ft_putstr_fd("NEGATIVE", fd);
	else if (cam.effect == BLACK_N_WHITE)
		ft_putstr_fd("BLACK_N_WHITE", fd);
	else if (cam.effect == CARTOON)
		ft_putstr_fd("CARTOON", fd);
	ft_putstr_fd("\",\n\t\t", fd);
}

void			write_cam(t_cam cam, int fd)
{
	ft_putstr_fd("\"scene\" :\n\t{\n\t\t", fd);
	write_feature("pos x", 0.0f, fd);
	write_feature("pos y", 0.0f, fd);
	write_feature("pos z", 0.0f, fd);
	write_feature("rot x", cam.rot.x, fd);
	write_feature("rot y", cam.rot.y, fd);
	write_feature("rot z", cam.rot.z, fd);
	write_cam_effect(cam, fd);
	write_feature("f_length", cam.f_length, fd);
	write_feature("dust", cam.dust, fd);
	write_feature("fov", (cl_float)cam.fov, fd);
	write_feature("refr_coef", cam.refr_coef, fd);
	write_feature("brightness", (cl_float)cam.brightness, fd);
	write_feature("filter x", (cl_float)cam.filter.x, fd);
	write_feature("filter y", (cl_float)cam.filter.y, fd);
	write_feature("filter z", (cl_float)cam.filter.z, fd);
	write_feature("aperture", cam.aperture, fd);
	ft_putstr_fd("},\n", fd);
}
