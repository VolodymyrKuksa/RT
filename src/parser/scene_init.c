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
		else if (scene->obj[i].type == elipsoid)
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
	printf("c1 x = %f\n", obj.primitive.elipsoid.c1.x);
	printf("c1 y = %f\n", obj.primitive.elipsoid.c1.y);
	printf("c1 z = %f\n", obj.primitive.elipsoid.c1.z);
	printf("c2 x = %f\n", obj.primitive.elipsoid.c2.x);
	printf("c2 y = %f\n", obj.primitive.elipsoid.c2.y);
	printf("c2 z = %f\n", obj.primitive.elipsoid.c2.z);
	printf("radius = %f\n", obj.primitive.elipsoid.r);
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
	printf("tex_scale = %f\n", obj.primitive.cylinder.tex_scale);
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
	printf("tex_scale = %f\n", obj.primitive.cone.tex_scale);
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
	printf("tex_scale = %f\n", obj.primitive.plane.tex_scale);
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

void			fill_basis(char *name, t_obj *tmp, cl_float v)
{
	if (ft_strcmp(name, "u x") == 0)
		tmp->basis.u.x = v;
	if (ft_strcmp(name, "u y") == 0)
		tmp->basis.u.y = v;
	if (ft_strcmp(name, "u z") == 0)
		tmp->basis.u.z = v;
	if (ft_strcmp(name, "v x") == 0)
		tmp->basis.v.x = v;
	if (ft_strcmp(name, "v y") == 0)
		tmp->basis.v.y = v;
	if (ft_strcmp(name, "v z") == 0)
		tmp->basis.v.z = v;
	if (ft_strcmp(name, "w x") == 0)
		tmp->basis.w.x = v;
	if (ft_strcmp(name, "w y") == 0)
		tmp->basis.w.y = v;
	if (ft_strcmp(name, "w z") == 0)
		tmp->basis.w.z = v;
}

void			check_tex_offs(cl_float2 tex_offs)
{
	if (tex_offs.x < 0 || tex_offs.x > 1)
		error_fedun("tex_offs x is not correct. 0 <= x <= 1");
	if (tex_offs.y < 0 || tex_offs.y > 1)
		error_fedun("tex_offs y is not correct. 0 <= y <= 1");
}

void			fill_col_distrupt(char *name, json_value v, t_obj *tmp)
{
	if (ft_strcmp(name, "col_disrupt") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("value is absent in key col_disrupt");
		if (ft_strcmp(v.u.string.ptr, "CHESS") == 0)
			tmp->col_disrupt = CHESS;
		if (ft_strcmp(v.u.string.ptr, "NODISTRUPT") == 0 ||
				ft_strcmp(v.u.string.ptr, "") == 0)
			tmp->col_disrupt = NODISRUPT;
		if (ft_strcmp(v.u.string.ptr, "COS") == 0)
			tmp->col_disrupt = COS;
		if (ft_strcmp(v.u.string.ptr, "CIRCLE") == 0)
			tmp->col_disrupt = CIRCLE;
		if (ft_strcmp(v.u.string.ptr, "PERLIN") == 0)
			tmp->col_disrupt = PERLIN;
		if (ft_strcmp(v.u.string.ptr, "PERLIN_BLUE") == 0)
			tmp->col_disrupt = PERLIN_BLUE;
		if (ft_strcmp(v.u.string.ptr, "PERLIN_RED") == 0)
			tmp->col_disrupt = PERLIN_RED;
		if (ft_strcmp(v.u.string.ptr, "PERLIN_GREEN") == 0)
			tmp->col_disrupt = PERLIN_GREEN;
	}
	if (tmp->emission.x != 0.0 || tmp->emission.y != 0.0 ||
		tmp->emission.z != 0.0)
		tmp->col_disrupt = NODISRUPT;
}

void			fill_textures(char *name, t_obj *tmp, json_value v)
{
	if (ft_strcmp(name, "texture") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("texture path is missing");
		tmp->tex_id = load_texture(v.u.string.ptr);
	}
	if (ft_strcmp(name, "material texture") == 0)
	{
		if (!v.u.string.ptr)
			error_fedun("material  texture path is missing");
		tmp->mater_tex_id = load_texture(v.u.string.ptr);
	}
}

void			fill_common(char *name, t_obj *tmp,
							json_value *v, cl_float3 *rot)
{
	fill_color(name, (cl_float)(v->u.dbl), tmp);
	fill_basis(name, tmp, (cl_float)(v->u.dbl));
	if (ft_strcmp(name, "light") == 0)
		parselight(v, tmp);
	fill_textures(name, tmp, *v);
	if (ft_strcmp(name, "rot x") == 0)
		rot->x = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "rot y") == 0)
		rot->y = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "rot z") == 0)
		rot->z = (cl_float)(v->u.dbl);
	if (ft_strcmp(name, "tex_offs x") == 0)
		tmp->tex_offs.x = (cl_float)v->u.dbl;
	if (ft_strcmp(name, "tex_offs y") == 0)
		tmp->tex_offs.y = (cl_float)v->u.dbl;
	fill_col_distrupt(name, *v, tmp);
	check_tex_offs(tmp->tex_offs);
}

void			rot_pos_cam(cl_float3 *pos, cl_float3 rot)
{
	*pos = clvec_rot_x(*pos, DTR(-rot.x));
	*pos = clvec_rot_y(*pos, DTR(-rot.y));
	*pos = clvec_rot_z(*pos, DTR(-rot.z));
}

void			rotate_obj_by_camera(t_obj *tmp, cl_float3 rot)
{
	if (tmp->type == elipsoid)
	{
		rot_pos_cam(&(tmp->primitive.elipsoid.c1), rot);
		rot_pos_cam(&(tmp->primitive.elipsoid.c2), rot);
	}
	else if (tmp->type == triangle)
	{
		rot_pos_cam(&(tmp->primitive.triangle.d1), rot);
		rot_pos_cam(&(tmp->primitive.triangle.d2), rot);
		rot_pos_cam(&(tmp->primitive.triangle.d3), rot);
	}
	else
	{
		rot_pos_cam(&(tmp->primitive.sphere.pos), rot);
	}
	init_rotate(&tmp->basis, (cl_float3){-rot.x, -rot.y, -rot.z});
}

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
	else if (ft_strcmp("elipsoid", value->u.object.values[i].name) == 0)
		fillellipse(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("triangle", value->u.object.values[i].name) == 0)
		filltriangle(value->u.object.values[i].value, scene, 0);
	else if (ft_strcmp("paralelepiped", value->u.object.values[i].name) == 0)
		fillparallelogram(value->u.object.values[i].value, scene, 0);
	else
		error_fedun("wrong key in root");
}

int				count_helping_obj(json_value *value)
{
	int			i;
	int			res;

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
	int			l;
	int			i;

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

void			rotate_scene_by_cam(t_scene *scene)
{
	int			i;

	i = 0;
	while (i < scene->num_obj)
	{
		rotate_obj_by_camera(&scene->obj[i], scene->cam.rot);
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
