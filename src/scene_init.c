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

#include "rt.h"
extern int	g_win_width;
extern int	g_win_height;
#define	LENGTH(a) sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
#define NORMAL(a) (cl_float3){a.x/LENGTH(a), a.y/LENGTH(a), a.z/LENGTH(a)}//just for test
#define ABS3(a) (cl_float3){fabs(a.x), fabs(a.y), fabs(a.z)}

void	error_fedun(char *er)
{
	ft_putstr(er);
	exit(-1);
}

char		*read_file(int fd, size_t *size)
{
	char	*tmp;
	char	*res;
	ssize_t	num;
	char	buf[256];

	res = (char *)malloc(sizeof(char));
	res[0] = '\0';
	if (res < 0)
		return (NULL);
	while ((num = read(fd, buf, 255)) > 0)
	{
		buf[num] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
	}
	if (size)
		*size = ft_strlen(res);
	return (res);
}

void	print_sphere(t_obj obj)
{
	printf("----------------------shpere---------------------------\n");
	printf("pos x = %f\n", obj.primitive.sphere.pos.x);
	printf("pos y = %f\n", obj.primitive.sphere.pos.y);
	printf("pos z = %f\n", obj.primitive.sphere.pos.z);
	printf("radius = %f\n", obj.primitive.sphere.r);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
}

void	print_cylinder(t_obj obj)
{
	printf("-----------------------cylinder------------------------\n");
	printf("pos x = %f\n", obj.primitive.cylinder.pos.x);
	printf("pos y = %f\n", obj.primitive.cylinder.pos.y);
	printf("pos z = %f\n", obj.primitive.cylinder.pos.z);
	printf("rot x = %f\n", obj.primitive.cylinder.rot.x);
	printf("rot y = %f\n", obj.primitive.cylinder.rot.y);
	printf("rot z = %f\n", obj.primitive.cylinder.rot.z);
	printf("radius = %f\n", obj.primitive.cylinder.r);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
}

void	print_cone(t_obj obj)
{
	printf("-----------------------cone---------------------------\n");
	printf("pos x = %f\n", obj.primitive.cone.pos.x);
	printf("pos y = %f\n", obj.primitive.cone.pos.y);
	printf("pos z = %f\n", obj.primitive.cone.pos.z);
	printf("rot x = %f\n", obj.primitive.cone.rot.x);
	printf("rot y = %f\n", obj.primitive.cone.rot.y);
	printf("rot z = %f\n", obj.primitive.cone.rot.z);
	printf("tng = %f\n", obj.primitive.cone.tng);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
}
void	print_plane(t_obj obj)
{
	printf("--------------------plane-----------------------------\n");
	printf("pos x = %f\n", obj.primitive.plane.pos.x);
	printf("pos y = %f\n", obj.primitive.plane.pos.y);
	printf("pos z = %f\n", obj.primitive.plane.pos.z);
	printf("rot x = %f\n", obj.primitive.plane.rot.x);
	printf("rot y = %f\n", obj.primitive.plane.rot.y);
	printf("rot z = %f\n", obj.primitive.plane.rot.z);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
}

void	fill_position(char *name, cl_float value, cl_float3 *pos)
{
	if (ft_strcmp(name, "pos x") == 0)
		pos->x = value;
	if (ft_strcmp(name, "pos y") == 0)
		pos->y = value;
	if (ft_strcmp(name, "pos z") == 0)
		pos->z = value;
}

void	fill_color(char *name, cl_float value, t_obj *tmp)
{
	if (ft_strcmp(name, "color x") == 0)
		tmp->color.x = value;
	if (ft_strcmp(name, "color y") == 0)
		tmp->color.y = value;
	if (ft_strcmp(name, "color z") == 0)
		tmp->color.z = value;
	if (tmp->color.x < 0 || tmp->color.x > 1)
		error_fedun("0 <= color x <= 1");
	if (tmp->color.y < 0 || tmp->color.y > 1)
		error_fedun("0 <= color y <= 1");
	if (tmp->color.z < 0 || tmp->color.z > 1)
		error_fedun("0 <= color z <= 1");
}

void	fill_rotate(char *name, cl_float value, cl_float3 *rot)
{
	if (ft_strcmp(name, "rot x") == 0)
		rot->x = value;
	if (ft_strcmp(name, "rot y") == 0)
		rot->y = value;
	if (ft_strcmp(name, "rot z") == 0)
		rot->z = value;
}

t_obj	default_sphere(void)
{
	t_obj	tmp;

	tmp.primitive.sphere.pos.x = -5;
	tmp.primitive.sphere.pos.y = -5;
	tmp.primitive.sphere.pos.z = -5;
	tmp.primitive.sphere.r= 5;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 0.0f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	return (tmp);
}

t_obj	default_cone(void)
{
	t_obj	tmp;

	tmp.primitive.cone.pos.x = -2;
	tmp.primitive.cone.pos.y = -2;
	tmp.primitive.cone.pos.z = -2;
	tmp.primitive.cone.rot.x = 0;
	tmp.primitive.cone.rot.y = 0;
	tmp.primitive.cone.rot.z = 0;
	tmp.primitive.cone.tng = 0.1;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = cone;
	return (tmp);
}

t_obj	default_cylinder(void)
{
	t_obj	tmp;

	tmp.primitive.cylinder.pos.x = -5;
	tmp.primitive.cylinder.pos.y = -5;
	tmp.primitive.cylinder.pos.z = -5;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.primitive.cylinder.r = 2;
	tmp.primitive.cylinder.rot.x = 0;
	tmp.primitive.cylinder.rot.y = 1;
	tmp.primitive.cylinder.rot.z = 0;
	tmp.type = cylinder;
	return (tmp);
}

t_obj	default_plane(void)
{
	t_obj	tmp;

	tmp.primitive.plane.pos.x = 10;
	tmp.primitive.plane.pos.y = 10;
	tmp.primitive.plane.pos.z = 10;
	tmp.primitive.plane.rot.x = 0;
	tmp.primitive.plane.rot.y = 0;
	tmp.primitive.plane.rot.z = 0;
	tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 1;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = plane;
	return (tmp);
}

void	checksumandemiss(t_obj *tmp)
{
	float	sum;

	tmp->diffuse = fabs(tmp->diffuse);
	tmp->specular = fabs(tmp->specular);
	tmp->refraction = fabs(tmp->refraction);
	if (tmp->diffuse == 0 && tmp->specular == 0 && tmp->refraction == 0)
		error_fedun("cannot be all zeros");
	sum = tmp->diffuse + tmp->specular + tmp->refraction;
	tmp->diffuse = tmp->diffuse / sum;
	tmp->specular = tmp->specular / sum;
	tmp->refraction = tmp->refraction / sum;
	if ((tmp->emission.x == 0.0f || tmp->emission.x >= 1.0f) &&
		(tmp->emission.y == 0.0f || tmp->emission.y >= 1.0f) &&
		(tmp->emission.z == 0.0f || tmp->emission.z >= 1.0f))
		return ;
	else
		error_fedun("emission > 1 or == 0");
	if (tmp->emission.x > 5.0f || tmp->emission.y > 5.0f ||
		tmp->emission.z > 5.0f)
		error_fedun("emission < 5");
}

void	parselight(json_value *value, t_obj *tmp)
{
	int		i;
	json_value 	v;

	i = 0;
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
		//printf("  %s   %f    \n ", pars->light[i], value->u.object.values[i].value->u.dbl);
		if (!ft_strcmp(value->u.object.values[i].name, "emission x"))
			tmp->emission.x = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "emission y"))
			tmp->emission.y = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "emission z"))
			tmp->emission.z = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "roughness"))
			tmp->roughness = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "diffuse"))
			tmp->diffuse = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "specular"))
			tmp->specular = (cl_float)v.u.dbl;
		if (!ft_strcmp(value->u.object.values[i].name, "refraction"))
			tmp->refraction = (cl_float)v.u.dbl;
		i++;
	}
	checksumandemiss(tmp);
}
void	fillthecylind(json_value *value, t_scene *scene)
{
	int		i;
	int l;
	t_obj	tmp;
	json_value v;

	i = 0;
	tmp = default_cylinder();
	l = value->u.object.length;
	while (i < l)
	{
		v = *(value->u.object.values[i].value);
		//printf("%s   %f\n", value->u.object.values[i].name, value->u.object.values[i].value->u.dbl);
		fill_position(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.primitive.cylinder.pos));
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.cylinder.r = (cl_float)v.u.dbl;
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		fill_rotate(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.primitive.cylinder.rot));
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		i++;
	}
	tmp.type = cylinder;
	tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	if (SUKA(tmp.primitive.sphere.r, 0) == 0)
		error_fedun("radius of cylinder is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_cylinder(tmp);


}
void	fillthecone(json_value *value, t_scene *scene)
{
	int		i;
	int l;
	t_obj	tmp;
	json_value v;

	i = 0;
	tmp = default_cone();
	l = value->u.object.length;
	while (i < l)
	{
		v = *(value->u.object.values[i].value);
		//printf("%s   %f\n", value->u.object.values[i].name, value->u.object.values[i].value->u.dbl);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.cone.pos));
		if (ft_strcmp(value->u.object.values[i].name, "tng") == 0)
			tmp.primitive.cone.tng = (cl_float)v.u.dbl;
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		fill_rotate(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.cone.rot));
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		i++;
	}
	tmp.type = cone;
	tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	scene->obj[scene->cur_obj++] = tmp;
	print_cone(tmp);


}

void	filltheplane(json_value *value, t_scene *scene)
{
	int		i;
	int l;
	t_obj	tmp;
	json_value v;

	i = 0;
	tmp = default_plane();
	l = value->u.object.length;
	while (i < l)
	{
		v = *(value->u.object.values[i].value);
		//printf("%s   %f\n", value->u.object.values[i].name, value->u.object.values[i].value->u.dbl);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.plane.pos));
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		fill_rotate(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.plane.rot));
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		i++;
	}
	tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	tmp.type = plane;
	//check_color(tmp);
	scene->obj[scene->cur_obj++] = tmp;
	print_plane(tmp);
}

void	fillthesphere(json_value *value, t_scene *scene)
{
	int		i;
	int l;
	t_obj	tmp;
	json_value v;

	i = 0;
	tmp = default_sphere();
	l = value->u.object.length;
	while (i < l)
	{
		v = *(value->u.object.values[i].value);
		//printf("%s   %f\n", value->u.object.values[i].name, value->u.object.values[i].value->u.dbl);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.sphere.pos));
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.sphere.r = (cl_float)v.u.dbl;
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		i++;
	}
	tmp.type = sphere;
	if (SUKA(tmp.primitive.sphere.r, 0) == 0)
		error_fedun("radius of sphere is bad");
	scene->obj[scene->cur_obj++] = tmp;
	print_sphere(tmp);


}



void	camera_default(t_cam *cam)
{
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 0;
	cam->dir.x = 0;
	cam->dir.y = 0;
	cam->dir.z = -1;
	cam->f_length = 60.0f;
	cam->aperture = 0.00001f;
	cam->fov = 90;
	cam->dust = 0.f;
}

void	check_camera(t_cam *cam)
{
	if (cam->fov <= 10.0 || cam->fov >= 160.0)
		camera_default(cam);
	if (cam->aperture <= 0.0000001f || cam->aperture >= 100.0)
		camera_default(cam);
	cam->updir.x = 0;
	cam->updir.y = 1;
	cam->updir.z = 0;
	cam->ldir.x = -1;
	cam->ldir.y = 0;
	cam->ldir.z = 0;
	cam->ratio = cam->f_length / calculate_ppd(cam->fov); //935.f for 60 degree fov
	cam->pr_pl_w = g_win_width;
	cam->pr_pl_h = g_win_height;
}

void	get_camera_params(json_value *value, t_scene *scene)
{
	int l;
	int i;
	json_value v;

	l = value->u.object.length;
	i = 0;
	if (l != 10)
		error_fedun("wrong number of parameters in scene");
	check_camera(&(scene->cam));
	while (i < l)
	{
		
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name, (cl_float)v.u.dbl, &(scene->cam.pos));
		if (ft_strcmp(value->u.object.values[i].name, "dir x") == 0)
			scene->cam.dir.x = (cl_float)SUKA(v.u.dbl, 0.0f);
		if (ft_strcmp(value->u.object.values[i].name, "dir y") == 0)
			scene->cam.dir.y = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "dir z") == 0)
			scene->cam.dir.z = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "f_length") == 0)
			scene->cam.f_length = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "dust") == 0)
			scene->cam.dust = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "fov") == 0)
			scene->cam.fov = (cl_float)v.u.dbl;
		if (ft_strcmp(value->u.object.values[i].name, "aperture") == 0)
			scene->cam.aperture = v.u.dbl;
		i++;
	}
	check_camera(&(scene->cam));
	printf(" cam pos x  %f\n", scene->cam.pos.x);
		printf(" cam pos y  %f\n", scene->cam.pos.y);
		printf(" cam pos z  %f\n", scene->cam.pos.z);
		printf(" cam dir x  %f\n", scene->cam.dir.x);
		printf(" cam dir y  %f\n", scene->cam.dir.y);
		printf(" cam dir z  %f\n", scene->cam.dir.z);
		printf(" cam f_length  %f\n", scene->cam.f_length);
		printf(" cam dust  %f\n", scene->cam.dust);
		printf(" cam fov  %f\n", scene->cam.fov);
		printf(" cam aperture  %f\n", scene->cam.aperture);

}

void	fillthescene(json_value *value, t_scene *scene)
{
	int l;
	int i;

	l = value->u.object.length;
	if (l <= 1)
		error_fedun("objects are not defined");
	scene->num_obj = l;
	scene->obj = (t_obj *)malloc(sizeof(t_obj) * l);
	i = 0;
	if (ft_strcmp(value->u.object.values[i++].name, "scene"))
		error_fedun("scene must be first");
	get_camera_params(value->u.object.values[0].value, scene);
	while (i < l)
	{
		if (ft_strcmp("sphere", value->u.object.values[i].name) == 0)
		{
			fillthesphere(value->u.object.values[i].value, scene);
		}
		else if (ft_strcmp("cone", value->u.object.values[i].name) == 0)
		{
			fillthecone(value->u.object.values[i].value, scene);
		}
		else if (ft_strcmp("plane", value->u.object.values[i].name) == 0)
		{
			filltheplane(value->u.object.values[i].value, scene);
		}
		else if (ft_strcmp("cylinder", value->u.object.values[i].name) == 0)
		{
			fillthecylind(value->u.object.values[i].value, scene);
		}
		else
			error_fedun("wrong key in root");
		if (scene->cur_obj >= scene->num_obj)
			return ;
		i++;
	}

}

void	parse_scene(int argc, char **argv, char **contents, size_t *len)
{
	int fd;

	if (argc != 2)
		error_fedun("second arg must be file");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fedun("Unable to open file");
	*contents = read_file(fd, len);
	if (*contents == NULL)
		error_fedun("Cant read file");
	printf("%s %lu\n", *contents, *len);
	printf("--------------------------------\n\n");
}

void	init_scene(t_scene *scene, int argc, char **argv)
{
	json_value* value;
	char *contents;
	size_t leh;

    scene->cur_obj = 0;
    parse_scene(argc, argv, &contents, &leh);

	value = json_parse((json_char*)contents,leh);

	if (value == NULL)
	{
		error_fedun("Unable to parse data");
		free(contents);
		exit(1);
	}
	fillthescene(value, scene);
	json_value_free(value);
	free(contents);
}

/*
void	init_scene(t_scene *scene, int argc, char **argv)
{
	t_obj	tmp;
	json_value *value;

	scene->num_obj = 15;
	scene->obj = (t_obj*)malloc(sizeof(t_obj) * scene->num_obj);

	tmp.primitive.sphere.pos.x = -5;
	tmp.primitive.sphere.pos.y = -3;
	tmp.primitive.sphere.pos.z = -50;
	tmp.primitive.sphere.r= 4;
	tmp.color.x = 1.f;
	tmp.color.y = 0.5f;
	tmp.color.z = 0.5f;
	tmp.emission.x = 0.f;
	tmp.emission.y = 0.f;
	tmp.emission.z = 0.f;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	scene->obj[0] = tmp;

	tmp.primitive.sphere.pos.x = -8;
	tmp.primitive.sphere.pos.y = -7;
	tmp.primitive.sphere.pos.z = -40;
	tmp.primitive.sphere.r= 3;
	tmp.color.x = 1.f;
	tmp.color.y = 0.9f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0;
	tmp.diffuse = 1.f;
	tmp.specular = 0;
	tmp.refraction = 0;
	tmp.type = sphere;
	scene->obj[1] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = -600;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.primitive.sphere.r= 490;
	tmp.type = sphere;
	scene->obj[2] = tmp;

	tmp.primitive.sphere.pos.x = 500;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 0.5f;
	tmp.color.y = 1.0f;
	tmp.color.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[3] = tmp;

	tmp.primitive.sphere.pos.x = -500;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 0.5f;
	tmp.color.y = 0.5f;
	tmp.color.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[4] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 500;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 1.0f;
	tmp.color.y = 1.0f;
	tmp.color.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[5] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = -500;
	tmp.primitive.sphere.pos.z = 0;
	tmp.color.x = 1.0f;
	tmp.color.y = 0.5f;
	tmp.color.z = 0.5f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[6] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = 5000;
	tmp.color.x = 1.0f;
	tmp.color.y = 0.0f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 490;
	scene->obj[7] = tmp;

	tmp.primitive.sphere.pos.x = 0;
	tmp.primitive.sphere.pos.y = 13;
	tmp.primitive.sphere.pos.z = -60;
	tmp.color.x = 1.0f;
	tmp.color.y = 1.0f;
	tmp.color.z = 1.0f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 4;
	scene->obj[8] = tmp;

	tmp.primitive.sphere.pos.x = 2.5;
	tmp.primitive.sphere.pos.y = 0;
	tmp.primitive.sphere.pos.z = -60;
	tmp.color.x = 0.f;
	tmp.color.y = 1.f;
	tmp.color.z = 0.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0.0f;
	tmp.diffuse = 0.f;
	tmp.specular = 1.f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 5;
	scene->obj[9] = tmp;

	tmp.primitive.sphere.pos.x = -2;
	tmp.primitive.sphere.pos.y = -2;
	tmp.primitive.sphere.pos.z = -40;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0.1f;
	tmp.diffuse = 0.9f;
	tmp.specular = 0.1f;
	tmp.refraction = 0.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 3;
	scene->obj[10] = tmp;

	tmp.primitive.sphere.pos.x = -5;
	tmp.primitive.sphere.pos.y = 3;
	tmp.primitive.sphere.pos.z = -60;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 0;
	tmp.emission.y = 0;
	tmp.emission.z = 0;
	tmp.roughness = 0.f;
	tmp.diffuse = 0.f;
	tmp.specular = 0.f;
	tmp.refraction = 1.f;
	tmp.type = sphere;
	tmp.primitive.sphere.r= 3.5;
	scene->obj[11] = tmp;

	tmp.primitive.cylinder.pos.x = -5;
	tmp.primitive.cylinder.pos.y = 3;
	tmp.primitive.cylinder.pos.z = -60;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 3;
	tmp.emission.y = 0;
	tmp.emission.z = 3;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.primitive.cylinder.r = 2;
	tmp.primitive.cylinder.rot.x = 0;
	tmp.primitive.cylinder.rot.y = 1;
	tmp.primitive.cylinder.rot.z = 0;
	tmp.type = cylinder;
	scene->obj[12] = tmp;

	tmp.primitive.cone.pos.x = -2;
	tmp.primitive.cone.pos.y = -2;
	tmp.primitive.cone.pos.z = -40;
	tmp.primitive.cone.rot.x = 1;
	tmp.primitive.cone.rot.y = 0;
	tmp.primitive.cone.rot.z = 0;
	tmp.primitive.cone.tng = 0.1;
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 3;
	tmp.emission.y = 3;
	tmp.emission.z = 3;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = cone;
	scene->obj[13] = tmp;

	tmp.primitive.plane.pos.x = 10;
	tmp.primitive.plane.pos.y = -10;
	tmp.primitive.plane.pos.z = 0;
	tmp.primitive.plane.rot.x = -1;
	tmp.primitive.plane.rot.y = 1;
	tmp.primitive.plane.rot.z = 0;
	tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	tmp.color.x = 1.f;
	tmp.color.y = 1.f;
	tmp.color.z = 1.f;
	tmp.emission.x = 1;
	tmp.emission.y = 1;
	tmp.emission.z = 1;
	tmp.roughness = 1.f;
	tmp.diffuse = 1.f;
	tmp.specular = 0.f;
	tmp.refraction = 0.f;
	tmp.type = plane;
	scene->obj[14] = tmp;

	scene->cam.pos.x = 0;
	scene->cam.pos.y = 0;
	scene->cam.pos.z = 0;
	scene->cam.dir.x = 0;
	scene->cam.dir.y = 0;
	scene->cam.dir.z = -1;
	scene->cam.updir.x = 0;
	scene->cam.updir.y = 1;
	scene->cam.updir.z = 0;
	scene->cam.ldir.x = -1;
	scene->cam.ldir.y = 0;
	scene->cam.ldir.z = 0;
	scene->cam.f_length = 60.f;
	scene->cam.aperture = 0.f;
	scene->cam.fov = 90;
	scene->cam.ratio = scene->cam.f_length / calculate_ppd(scene->cam.fov); //935.f for 60 degree fov
	scene->cam.pr_pl_w = g_win_width;
	scene->cam.pr_pl_h = g_win_height;
	scene->cam.dust = 0.f;
	printf("ratio: %f\n", scene->cam.ratio);
}
*/

