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
	if ((fd = open("scene/writing.json", O_RDWR | O_CREAT | O_TRUNC, 0777)) == -1)
		error_fedun("cannot save scene");
	ft_putstr_fd("{\n\t", fd);
	write_cam(scene->cam, fd);
	while (i < scene->num_obj)
	{
		write_which_obj(scene, i, fd);
		if (scene->obj[i].type == cylinder || scene->obj[i].type == cone)
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
