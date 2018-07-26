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
# define LENGTH(a) sqrt(a.x * a.x + a.y * a.y + a.z * a.z)
# define NORMAL(a) (cl_float3){a.x/LENGTH(a), a.y/LENGTH(a), a.z/LENGTH(a)}
# define ABS3(a) (cl_float3){fabs(a.x), fabs(a.y), fabs(a.z)}

void			print_scene(t_scene *scene)
{
	int			i;

	printf("PRINTIN ALL THE SCENE >>>>>>>>\n\n");
	i = 0;
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
	while (i < scene->num_obj)
	{
		if (scene->obj[i].type == sphere)
			print_sphere(scene->obj[i]);
		else if (scene->obj[i].type == cylinder)
			print_cylinder(scene->obj[i]);
		else if (scene->obj[i].type == cone)
			print_cone(scene->obj[i]);
		else if (scene->obj[i].type == plane)
			print_plane(scene->obj[i]);
		else if (scene->obj[i].type == torus)
			print_torus(scene->obj[i]);
		else if (scene->obj[i].type == rectangle)
			print_rectangle(scene->obj[i]);
		else if (scene->obj[i].type == disk)
			print_disk(scene->obj[i]);
		else if (scene->obj[i].type == ellipse)
			print_ellipse(scene->obj[i]);
		else if (scene->obj[i].type == parallelogram)
			print_parallelogram(scene->obj[i]);
		else if (scene->obj[i].type == triangle)
			print_triangle(scene->obj[i]);
		i++;
	}
}

void			print_sphere(t_obj obj)
{
	printf("----------------------shpere---------------------------\n");
	printf("pos x = %f\n", obj.primitive.sphere.pos.x);
	printf("pos y = %f\n", obj.primitive.sphere.pos.y);
	printf("pos z = %f\n", obj.primitive.sphere.pos.z);
	printf("radius = %f\n", obj.primitive.sphere.r);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("u x = %f\n", obj.basis.u.x);
	printf("u y = %f\n", obj.basis.u.y);
	printf("u z = %f\n", obj.basis.u.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
	printf("texture id= %d\n", obj.tex_id);
}

void			print_ellipse(t_obj obj)
{
	printf("----------------------ellipse---------------------------\n");
	printf("c1 x = %f\n", obj.primitive.ellipse.c1.x);
	printf("c1 y = %f\n", obj.primitive.ellipse.c1.y);
	printf("c1 z = %f\n", obj.primitive.ellipse.c1.z);
	printf("c2 x = %f\n", obj.primitive.ellipse.c2.x);
	printf("c2 y = %f\n", obj.primitive.ellipse.c2.y);
	printf("c2 z = %f\n", obj.primitive.ellipse.c2.z);
	printf("radius = %f\n", obj.primitive.ellipse.r);
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
	printf("texture id= %d\n", obj.tex_id);
}

void			print_disk(t_obj obj)
{
	printf("----------------------disk---------------------------\n");
	printf("pos x = %f\n", obj.primitive.disk.pos.x);
	printf("pos y = %f\n", obj.primitive.disk.pos.y);
	printf("pos z = %f\n", obj.primitive.disk.pos.z);
	printf("radius = %f\n", obj.primitive.disk.r);
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
	printf("texture id= %d\n", obj.tex_id);
}

void			print_cylinder(t_obj obj)
{
	printf("-----------------------cylinder------------------------\n");
	printf("pos x = %f\n", obj.primitive.cylinder.pos.x);
	printf("pos y = %f\n", obj.primitive.cylinder.pos.y);
	printf("pos z = %f\n", obj.primitive.cylinder.pos.z);
	printf("u x = %f\n", obj.basis.u.x);
	printf("u y = %f\n", obj.basis.u.y);
	printf("u z = %f\n", obj.basis.u.z);
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
	printf("texture id= %d\n", obj.mater_tex_id);
}

void			print_torus(t_obj obj)
{
	printf("-----------------------torus------------------------\n");
	printf("pos x = %f\n", obj.primitive.torus.pos.x);
	printf("pos y = %f\n", obj.primitive.torus.pos.y);
	printf("pos z = %f\n", obj.primitive.torus.pos.z);
	printf("radius small = %f\n", obj.primitive.torus.r);
	printf("radius big = %f\n", obj.primitive.torus.R);
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
	printf("texture id= %d\n", obj.tex_id);
}

void			print_cone(t_obj obj)
{
	printf("-----------------------cone---------------------------\n");
	printf("pos x = %f\n", obj.primitive.cone.pos.x);
	printf("pos y = %f\n", obj.primitive.cone.pos.y);
	printf("pos z = %f\n", obj.primitive.cone.pos.z);
	printf("tng = %f\n", obj.primitive.cone.tng);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("u x = %f\n", obj.basis.u.x);
	printf("u y = %f\n", obj.basis.u.y);
	printf("u z = %f\n", obj.basis.u.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
	printf("texture id= %d\n", obj.tex_id);
}

void			print_plane(t_obj obj)
{
	printf("--------------------plane-----------------------------\n");
	printf("pos x = %f\n", obj.primitive.plane.pos.x);
	printf("pos y = %f\n", obj.primitive.plane.pos.y);
	printf("pos z = %f\n", obj.primitive.plane.pos.z);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("u x = %f\n", obj.basis.u.x);
	printf("u y = %f\n", obj.basis.u.y);
	printf("u z = %f\n", obj.basis.u.z);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
	printf("texture id= %d\n", obj.tex_id);
}

void			print_rectangle(t_obj obj)
{
	printf("--------------------rectangle-----------------------------\n");
	printf("pos x = %f\n", obj.primitive.rectangle.pos.x);
	printf("pos y = %f\n", obj.primitive.rectangle.pos.y);
	printf("pos z = %f\n", obj.primitive.rectangle.pos.z);
	printf("color x = %f\n", obj.color.x);
	printf("color y = %f\n", obj.color.y);
	printf("color z = %f\n", obj.color.z);
	printf("w = %f\n", obj.primitive.rectangle.w);
	printf("h = %f\n", obj.primitive.rectangle.h);
	printf("emission x = %f\n", obj.emission.x);
	printf("emission y = %f\n", obj.emission.y);
	printf("emission z = %f\n", obj.emission.z);
	printf("roughness = %f\n", obj.roughness);
	printf("diffuse = %f\n", obj.diffuse);
	printf("specular = %f\n", obj.specular);
	printf("refraction = %f\n", obj.refraction);
	printf("texture id= %d\n", obj.tex_id);
}

void			print_parallelogram(t_obj obj)
{
	printf("--------------------parallelogram---------------------------\n");
	printf("pos x = %f\n", obj.primitive.parallelogram.pos.x);
	printf("pos y = %f\n", obj.primitive.parallelogram.pos.y);
	printf("pos z = %f\n", obj.primitive.parallelogram.pos.z);
	printf("w = %f\n", obj.primitive.parallelogram.w);
	printf("h = %f\n", obj.primitive.parallelogram.h);
	printf("l = %f\n", obj.primitive.parallelogram.l);
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
	printf("texture id= %d\n", obj.tex_id);
}

void			print_triangle(t_obj obj)
{
	printf("--------------------triangle-----------------------------\n");
	printf("d1 x = %f\n", obj.primitive.triangle.d1.x);
	printf("d1 y = %f\n", obj.primitive.triangle.d1.y);
	printf("d1 z = %f\n", obj.primitive.triangle.d1.z);
	printf("d2 x = %f\n", obj.primitive.triangle.d2.x);
	printf("d2 y = %f\n", obj.primitive.triangle.d2.y);
	printf("d2 z = %f\n", obj.primitive.triangle.d2.z);
	printf("d3 x = %f\n", obj.primitive.triangle.d3.x);
	printf("d3 y = %f\n", obj.primitive.triangle.d3.y);
	printf("d3 z = %f\n", obj.primitive.triangle.d3.z);
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
	printf("texture id= %d\n", obj.tex_id);
}

void			parselight(json_value *value, t_obj *tmp)
{
	int			i;
	json_value	v;

	i = 0;
	while (i < value->u.object.length)
	{
		v = *(value->u.object.values[i].value);
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

void			fill_common(char *name, t_obj *tmp,
							json_value *v, cl_float3 *rot)
{
	fill_color(name, (cl_float)(v->u.dbl), tmp);
	if (ft_strcmp(name, "light") == 0)
		parselight(v, tmp);
	if (ft_strcmp(name, "texture") == 0)
		tmp->tex_id = load_texture(v->u.string.ptr);
	if (ft_strcmp(name, "material texture") == 0)
		tmp->mater_tex_id = load_texture(v->u.string.ptr);
	if (ft_strcmp(name, "rot x") == 0)
		rot->x = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "rot y") == 0)
		rot->y = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "rot z") == 0)
		rot->z = (cl_float)(v->u.dbl);
	tmp->col_disrupt = PERLIN_BLUE;	// <<<	cannot be applied to obj with emission
	tmp->tex_offs = (cl_float2){0.f, 0.f};	// 0 <= x <= 1.f // 0 <= y <= 1.f
}

void			fill_scene_obj(json_value *value, t_scene *scene, int i)
{
	if (ft_strcmp("sphere", value->u.object.values[i].name) == 0)
		fillthesphere(value->u.object.values[i].value, scene);
	else if (ft_strcmp("cone", value->u.object.values[i].name) == 0)
		fillthecone(value->u.object.values[i].value, scene);
	else if (ft_strcmp("plane", value->u.object.values[i].name) == 0)
		filltheplane(value->u.object.values[i].value, scene);
	else if (ft_strcmp("cylinder", value->u.object.values[i].name) == 0)
		fillthecylind(value->u.object.values[i].value, scene);
	else if (ft_strcmp("torus", value->u.object.values[i].name) == 0)
		filltorus(value->u.object.values[i].value, scene);
	else if (ft_strcmp("rectangle", value->u.object.values[i].name) == 0)
		fillrectangle(value->u.object.values[i].value, scene);
	else if (ft_strcmp("disk", value->u.object.values[i].name) == 0)
		filldisk(value->u.object.values[i].value, scene);
	else if (ft_strcmp("ellipse", value->u.object.values[i].name) == 0)
		fillellipse(value->u.object.values[i].value, scene);
	else if (ft_strcmp("triangle", value->u.object.values[i].name) == 0)
		filltriangle(value->u.object.values[i].value, scene);
	else if (ft_strcmp("parallelogram", value->u.object.values[i].name) == 0)
		fillparallelogram(value->u.object.values[i].value, scene);
	else
		error_fedun("wrong key in root");
}

void			fillthescene(json_value *value, t_scene *scene)
{
	int			l;
	int			i;

	l = value->u.object.length;
	if (l <= 1)
		error_fedun("objects are not defined");
	scene->num_obj = l - 1;
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
	//print_scene(scene);
	json_value_free(value);
	free(contents);
	//write_scene(scene);
}
