/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:14:41 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:14:42 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			write_rectangle(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"rectangle\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.rectangle.pos, obj.color, fd);
	write_feature("h", obj.primitive.rectangle.h, fd);
	write_feature("w", obj.primitive.rectangle.w, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_torus(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"torus\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.torus.pos, obj.color, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	ft_putstr_fd("\t\t", fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_feature("radius big", obj.primitive.torus.R, fd);
	write_feature("radius small", obj.primitive.torus.r, fd);
	write_light(obj, fd);
}

void			write_ellipse(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"elipsoid\" :\n\t{\n\t\t", fd);
	write_feature("c1 x", obj.primitive.elipsoid.c1.x, fd);
	write_feature("c1 y", obj.primitive.elipsoid.c1.y, fd);
	write_feature("c1 z", obj.primitive.elipsoid.c1.z, fd);
	write_feature("c2 x", obj.primitive.elipsoid.c2.x, fd);
	write_feature("c2 y", obj.primitive.elipsoid.c2.y, fd);
	write_feature("c2 z", obj.primitive.elipsoid.c2.z, fd);
	write_feature("radius", obj.primitive.elipsoid.r, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_pos_color((cl_float3){0, 0, 0}, obj.color, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_triangle(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"triangle\" :\n\t{\n\t\t", fd);
	write_feature("d1 x", obj.primitive.triangle.d1.x, fd);
	write_feature("d1 y", obj.primitive.triangle.d1.y, fd);
	write_feature("d1 z", obj.primitive.triangle.d1.z, fd);
	write_feature("d2 x", obj.primitive.triangle.d2.x, fd);
	write_feature("d2 y", obj.primitive.triangle.d2.y, fd);
	write_feature("d2 z", obj.primitive.triangle.d2.z, fd);
	write_feature("d3 x", obj.primitive.triangle.d3.x, fd);
	write_feature("d3 y", obj.primitive.triangle.d3.y, fd);
	write_feature("d3 z", obj.primitive.triangle.d3.z, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_pos_color((cl_float3){0, 0, 0}, obj.color, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_parallelogram(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"paralelepiped\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.parallelogram.pos, obj.color, fd);
	write_feature("h", obj.primitive.parallelogram.h, fd);
	write_feature("w", obj.primitive.parallelogram.w, fd);
	write_feature("l", obj.primitive.parallelogram.l, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}
