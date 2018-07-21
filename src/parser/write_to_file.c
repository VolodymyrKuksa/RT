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

cl_float3	rotate_now(cl_float3 v)
{
	cl_float3	res;

	res.x = -(cl_float)(acos(v.x) / M_PI * 180.0);
	res.y = -(cl_float)(acos(v.y) / M_PI * 180.0);
	res.z = -(cl_float)(acos(v.z) / M_PI * 180.0);
	return (res);
}

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

void			write_pos_dir(cl_float3 dir, int fd)
{
	write_feature("pos x", 0.0f, fd);
	write_feature("pos y", 0.0f, fd);
	write_feature("pos z", 0.0f, fd);
	write_feature("dir x", dir.x, fd);
	write_feature("dir y", dir.y, fd);
	write_feature("dir z", dir.z, fd);
}

void			write_pos_color_rot(cl_float3 pos,
				cl_float3 rot, cl_float3 color, int fd, cl_float3 v)
{
	rot = rotate_now(v);
	write_feature("pos x", pos.x, fd);
	write_feature("pos y", pos.y, fd);
	write_feature("pos z", pos.z, fd);
	write_feature("rot x", rot.x, fd);
	write_feature("rot y", rot.y, fd);
	write_feature("rot z", rot.z, fd);
	write_feature("color x", color.x, fd);
	write_feature("color y", color.y, fd);
	write_feature("color z", color.z, fd);
}

void			write_cam(t_cam cam, int fd)
{
	ft_putstr_fd("\"scene\" :\n\t{\n\t\t", fd);
	write_pos_dir(cam.dir, fd);
	write_feature("f_length", cam.f_length, fd);
	write_feature("dust", cam.dust, fd);
	write_feature("fov", (cl_float)cam.fov, fd);
	write_feature("aperture", cam.aperture, fd);
	ft_putstr_fd("},\n\t\n", fd);
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
	write_pos_color_rot(obj.primitive.sphere.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_feature("radius", obj.primitive.sphere.r, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_disk(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"disk\" :\n\t{\n\t\t", fd);
	write_pos_color_rot(obj.primitive.disk.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_feature("radius", obj.primitive.disk.r, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_cone(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"cone\" :\n\t{\n\t\t", fd);
	write_pos_color_rot(obj.primitive.cone.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_feature("tng", obj.primitive.cone.tng, fd);
	write_feature("m1", obj.primitive.cone.m1, fd);
	write_feature("m2", obj.primitive.cone.m2, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_cylinder(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"cylinder\" :\n\t{\n\t\t", fd);
	write_pos_color_rot(obj.primitive.cylinder.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_feature("radius", obj.primitive.cylinder.r, fd);
	write_feature("h", obj.primitive.cylinder.h, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_plane(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"plane\" :\n\t{\n\t\t", fd);
	write_pos_color_rot(obj.primitive.cone.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_rectangle(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"rectangle\" :\n\t{\n\t\t", fd);
	write_pos_color_rot(obj.primitive.rectangle.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_feature("h", obj.primitive.rectangle.h, fd);
	write_feature("w", obj.primitive.rectangle.w, fd);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_light(obj, fd);
}

void			write_torus(t_obj obj, int fd)
{
	ft_putstr_fd("\t\"torus\" :\n\t{\n\t\t", fd);
	write_pos_color_rot(obj.primitive.torus.pos, obj.rot, obj.color, fd, obj.basis.v);
	write_texture(obj.mater_tex_id, obj.tex_id, fd);
	write_feature("radius big", obj.primitive.torus.R, fd);
	write_feature("radius small", obj.primitive.torus.r, fd);
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
		if (i == scene->num_obj - 1)
			ft_putstr_fd("}\n", fd);
		else
			ft_putstr_fd("},\n", fd);
		i++;
	}
	ft_putstr_fd("}", fd);
	close(fd);
}
