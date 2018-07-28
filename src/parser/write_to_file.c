/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_to_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 12:41:31 by afedun            #+#    #+#             */
/*   Updated: 2018/07/21 12:41:34 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			write_feature(char *s, cl_float num, int fd)
{
	ft_putstr_fd("\"", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\" : ", fd);
	ftoa((float)num, 4, 0, fd);
	if (ft_strcmp(s, "aperture") != 0 && ft_strcmp(s, "roughness") != 0)
		ft_putstr_fd(",\n\t\t", fd);
	else
		ft_putstr_fd("\n\t", fd);
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

void			write_cam(t_cam cam, int fd)
{
	ft_putstr_fd("\"scene\" :\n\t{\n\t\t", fd);
	write_feature("pos x", 0.0f, fd);
	write_feature("pos y", 0.0f, fd);
	write_feature("pos z", 0.0f, fd);
	write_feature("rot x", cam.rot.x, fd);
	write_feature("rot y", cam.rot.y, fd);
	write_feature("rot z", cam.rot.z, fd);
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
	char			*s;

	s = get_texture_name(id_mat);
	ft_putstr_fd("\"material texture\": \"", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\",\n", fd);
	s = get_texture_name(id);
	ft_putstr_fd("\t\t\"texture\": \"", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\",\n", fd);
}

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
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_feature("radius big", obj.primitive.torus.R, fd);
	write_feature("radius small", obj.primitive.torus.r, fd);
	write_light(obj, fd);
}

void			write_paraboloid(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"paraboloid\" :\n\t{\n\t\t", fd);
	write_feature("pos x", obj.primitive.paraboloid.pos.x, fd);
	write_feature("pos y", obj.primitive.paraboloid.pos.y, fd);
	write_feature("pos z", obj.primitive.paraboloid.pos.z, fd);
	write_feature("k", obj.primitive.paraboloid.k, fd);
	write_feature("m", obj.primitive.paraboloid.m, fd);
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
	ft_putstr_fd("\t\"parallelogram\" :\n\t{\n\t\t", fd);
	write_pos_color(obj.primitive.parallelogram.pos, obj.color, fd);
	write_feature("h", obj.primitive.parallelogram.h, fd);
	write_feature("w", obj.primitive.parallelogram.w, fd);
	write_feature("l", obj.primitive.parallelogram.w, fd);
	write_basis(obj, fd);
	write_disrupt_tex_offs(obj, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_which_obj(t_scene *scene, int i, int fd)
{
	if (scene->obj[i].type == sphere)
		write_sphere(scene->obj[i], fd);
	else if (scene->obj[i].type == cone)
		write_cone(scene->obj[i], fd);
	else if (scene->obj[i].type == plane)
		write_plane(scene->obj[i], fd);
	else if (scene->obj[i].type == cylinder)
		write_cylinder(scene->obj[i], fd);
	else if (scene->obj[i].type == torus)
		write_torus(scene->obj[i], fd);
	else if (scene->obj[i].type == disk)
		write_disk(scene->obj[i], fd);
	else if (scene->obj[i].type == rectangle)
		write_rectangle(scene->obj[i], fd);
	else if (scene->obj[i].type == paraboloid)
		write_paraboloid(scene->obj[i], fd);
	else if (scene->obj[i].type == triangle)
		write_triangle(scene->obj[i], fd);
	else if (scene->obj[i].type == parallelogram)
		write_parallelogram(scene->obj[i], fd);
}

void				write_scene(t_scene *scene)
{
	int				fd;
	int				i;

	i = 0;
	if ((fd = open("writing.json", O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		error_fedun("cannot save scene");
	ft_putstr_fd("{\n\t", fd);
	write_cam(scene->cam, fd);
	while (i < scene->num_obj)
	{
		write_which_obj(scene, i, fd);
		if (scene->obj[i].type == cylinder)
			i += 2;
		if (i == scene->num_obj - 1)
			ft_putstr_fd("}\n", fd);
		else
			ft_putstr_fd("},\n", fd);
		i++;
	}
	ft_putstr_fd("}", fd);
	close(fd);
}
