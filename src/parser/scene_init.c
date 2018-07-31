/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 15:27:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/28 15:27:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenCL/opencl.h>
#include <json.h>
#include "rt.h"

extern int	g_win_width;
extern int	g_win_height;

void			fill_scene_obj(json_value *value, t_scene *scene, int i)
{
	if (ft_strcmp("sphere", value->u.object.values[i].name) == 0)
		fillthesphere(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("cone", value->u.object.values[i].name) == 0)
		fillthecone(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("plane", value->u.object.values[i].name) == 0)
		filltheplane(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("cylinder", value->u.object.values[i].name) == 0)
		fillthecylind(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("torus", value->u.object.values[i].name) == 0)
		filltorus(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("rectangle", value->u.object.values[i].name) == 0)
		fillrectangle(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("disk", value->u.object.values[i].name) == 0)
		filldisk(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("paraboloid", value->u.object.values[i].name) == 0)
		fillparaboloid(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("triangle", value->u.object.values[i].name) == 0)
		filltriangle(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("paralelepiped", value->u.object.values[i].name) == 0)
		fillparallelogram(value->u.object.values[i].value, scene, 0);
	else
		error_fedun("wrong key in root");
}

int				count_helping_obj(json_value *value)
{
	unsigned int	i;
	int				res;

	i = 0;
	res = 0;
	while (i < value->u.object.length)
	{
		if (ft_strcmp(value->u.object.values[i].name, "cylinder") == 0)
			res = res + 2;
		if (ft_strcmp(value->u.object.values[i].name, "cone") == 0)
			res += 2;
		i++;
	}
	return (res);
}

void			fillthescene(json_value *value, t_scene *scene)
{
	int		l;
	int		i;

	l = value->u.object.length;
	if (l <= 1)
		error_fedun("objects are not defined");
	scene->num_obj = l - 1 + count_helping_obj(value);
	scene->obj = (t_obj *)malloc(sizeof(t_obj) * scene->num_obj);
	i = 0;
	if (ft_strcmp(value->u.object.values[i++].name, "scene"))
		error_fedun("scene must be first");
	get_camera_params(value->u.object.values[0].value, scene);
	while (i < l)
	{
		fill_scene_obj(value, scene, i);
		if (scene->cur_obj >= scene->num_obj)
			return ;
		i++;
	}
}

void			init_scene(t_scene *scene, int argc, char **argv)
{
	json_value	*value;
	char		*contents;
	size_t		len;

	scene->cur_obj = 0;
	parse_scene(argc, argv, &contents, &len);
	value = json_parse(contents, len);
	if (value == NULL)
	{
		error_fedun("Unable to parse data");
		free(contents);
		exit(1);
	}
	fillthescene(value, scene);
	rotate_scene_by_cam(scene);
	json_value_free(value);
	free(contents);
}
