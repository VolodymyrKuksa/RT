/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:14:20 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:14:21 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			write_sphere(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"sphere\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.sphere.pos, obj.color, fd);
	write_feature("radius", obj.primitive.sphere.r, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_disk(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"disk\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.disk.pos, obj.color, fd);
	write_feature("radius", obj.primitive.disk.r, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_cone(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"cone\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.cone.pos, obj.color, fd);
	write_feature("tng", obj.primitive.cone.tng, fd);
	write_feature("m1", obj.primitive.cone.m1, fd);
	write_feature("m2", obj.primitive.cone.m2, fd);
	write_feature("tex_scale", obj.primitive.cone.tex_scale, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_cylinder(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"cylinder\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.cylinder.pos, obj.color, fd);
	write_feature("radius", obj.primitive.cylinder.r, fd);
	write_feature("h", obj.primitive.cylinder.h, fd);
	write_feature("tex_scale", obj.primitive.cylinder.tex_scale, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_plane(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"plane\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.plane.pos, obj.color, fd);
	write_feature("tex_scale", obj.primitive.plane.tex_scale, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}
