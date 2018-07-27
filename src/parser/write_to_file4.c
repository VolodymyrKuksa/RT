/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 19:15:42 by afedun            #+#    #+#             */
/*   Updated: 2018/07/27 19:15:44 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			write_light(t_obj obj, int fd)
{
	ft_putstr_fd("\t\t\"light\" : {\n\t\t", fd);
	write_feature("emission x", obj.emission.x, fd);
	write_feature("emission y", obj.emission.y, fd);
	write_feature("emission z", obj.emission.z, fd);
	write_feature("diffuse", obj.diffuse, fd);
	write_feature("specular", obj.specular, fd);
	write_feature("refraction", obj.refraction, fd);
	write_feature("roughness", obj.roughness, fd);
	ft_putstr_fd("\t}\n\t", fd);
}

void			write_texture(int id_mat, int id, int fd)
{
	char		*s;

	s = get_texture_name(id_mat);
	ft_putstr_fd("\"material texture\": \"", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\",\n", fd);
	s = get_texture_name(id);
	ft_putstr_fd("\t\t\"texture\": \"", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\",\n", fd);
}

void			write_basis(t_obj obj, int fd)
{
	write_feature("u x", obj.basis.u.x, fd);
	write_feature("u y", obj.basis.u.y, fd);
	write_feature("u z", obj.basis.u.z, fd);
	write_feature("v x", obj.basis.v.x, fd);
	write_feature("v y", obj.basis.v.y, fd);
	write_feature("v z", obj.basis.v.z, fd);
	write_feature("w x", obj.basis.w.x, fd);
	write_feature("w y", obj.basis.w.y, fd);
	write_feature("w z", obj.basis.w.z, fd);
}

void			write_disrupt_tex_offs(t_obj obj, int fd)
{
	write_feature("tex_offs x", obj.tex_offs.x, fd);
	write_feature("tex_offs y", obj.tex_offs.y, fd);
	ft_putstr_fd("\"col_disrupt\": \"", fd);
	if (obj.col_disrupt == NODISRUPT)
		ft_putstr_fd("NODISTRUPT", fd);
	else if (obj.col_disrupt == COS)
		ft_putstr_fd("COS", fd);
	else if (obj.col_disrupt == CIRCLE)
		ft_putstr_fd("CIRCLE", fd);
	else if (obj.col_disrupt == CHESS)
		ft_putstr_fd("CHESS", fd);
	else if (obj.col_disrupt == PERLIN)
		ft_putstr_fd("PERLIN", fd);
	else if (obj.col_disrupt == PERLIN_GREEN)
		ft_putstr_fd("PERLIN_GREEN", fd);
	else if (obj.col_disrupt == PERLIN_RED)
		ft_putstr_fd("PERLIN_RED", fd);
	else if (obj.col_disrupt == PERLIN_BLUE)
		ft_putstr_fd("PERLIN_BLUE", fd);
	ft_putstr_fd("\",\n\t\t", fd);
}

void			write_pos_color(cl_float3 pos, cl_float3 color, int fd)
{
	write_feature("pos x", pos.x, fd);
	write_feature("pos y", pos.y, fd);
	write_feature("pos z", pos.z, fd);
	write_feature("color x", color.x, fd);
	write_feature("color y", color.y, fd);
	write_feature("color z", color.z, fd);
}
