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
#define NORMAL(a) (cl_float3){a.x/LENGTH(a), a.y/LENGTH(a), a.z/LENGTH(a)}
#define ABS3(a) (cl_float3){fabs(a.x), fabs(a.y), fabs(a.z)}

void	error_fedun(char *er)
{
	ft_putendl(er);
	exit(-1);
}

void		minus_camera(cl_float3 *pos, cl_float3 cam_pos)
{
	pos->x -= cam_pos.x;
	pos->y -= cam_pos.y;
	pos->z -= cam_pos.z;
}

/*
void fill_u(char *s, float value, cl_float3 *u)
{
	if (ft_strcmp(s, "rot x") == 0)
	{u->x = value;
		printf("uuuuu xxxx = %f\n", u->x);}
	if (ft_strcmp(s, "rot y") == 0)
	{u->y = value;
		printf("uuuuu yyyy = %f\n", u->y);}
	if (ft_strcmp(s, "rot z") == 0)
	{u->z = value;
		printf("uuuuu zzzz = %f\n", u->z);}
}
*/

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

void	print_cylinder(t_obj obj)
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
		printf("texture id= %d\n", obj.tex_id);
}

void	print_cone(t_obj obj)
{
	printf("-----------------------cone---------------------------\n");
	printf("pos x = %f\n", obj.primitive.cone.pos.x);
	printf("pos y = %f\n", obj.primitive.cone.pos.y);
	printf("pos z = %f\n", obj.primitive.cone.pos.z);
	//printf("rot x = %f\n", obj.primitive.cone.rot.x);
	//printf("rot y = %f\n", obj.primitive.cone.rot.y);
	//printf("rot z = %f\n", obj.primitive.cone.rot.z);
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
void	print_plane(t_obj obj)
{
	printf("--------------------plane-----------------------------\n");
	printf("pos x = %f\n", obj.primitive.plane.pos.x);
	printf("pos y = %f\n", obj.primitive.plane.pos.y);
	printf("pos z = %f\n", obj.primitive.plane.pos.z);
	//printf("rot x = %f\n", obj.primitive.plane.rot.x);
	//printf("rot y = %f\n", obj.primitive.plane.rot.y);
	//printf("rot z = %f\n", obj.primitive.plane.rot.z);
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

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.sphere.pos.x = -5;
	tmp.primitive.sphere.pos.y = -5;
	tmp.primitive.sphere.pos.z = -5;
	tmp.primitive.sphere.r = 5;
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
	tmp.tex_id = -1;
	return (tmp);
}

t_obj	default_cone(void)
{
	t_obj	tmp;

	tmp.primitive.cone.pos.x = -2;
	tmp.primitive.cone.pos.y = -2;
	tmp.primitive.cone.pos.z = -2;
	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.cone.m1 = 0.0f;
	tmp.primitive.cone.m2 = 200.0f;
	//tmp.primitive.cone.rot.x = 0;
	//tmp.primitive.cone.rot.y = 0;
	//tmp.primitive.cone.rot.z = 0;
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
	tmp.tex_id = -1;
	return (tmp);
}

t_obj	default_cylinder(void)
{
	t_obj	tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
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
	tmp.tex_id = -1;
	//tmp.primitive.cylinder.rot.x = 0;
	//tmp.primitive.cylinder.rot.y = 1;
	//tmp.primitive.cylinder.rot.z = 0;
	tmp.type = cylinder;
	return (tmp);
}

t_obj	default_plane(void)
{
	t_obj	tmp;

	tmp.basis.u = (cl_float3){0.0, 1.0, 0.0};
	tmp.basis.v = (cl_float3){1.0, 0.0, 0.0};
	tmp.basis.w = (cl_float3){0.0, 0.0, 1.0};
	tmp.primitive.plane.pos.x = 10;
	tmp.primitive.plane.pos.y = 10;
	tmp.primitive.plane.pos.z = 10;
	//tmp.primitive.plane.rot.x = 0;
	//tmp.primitive.plane.rot.y = 0;
	//tmp.primitive.plane.rot.z = 0;
	//tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
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
	tmp.tex_id = -1;
	return (tmp);
}

void		init_rotate(t_basis *basis, cl_float3 rot)
{
	basis->u = clvec_rot_x(basis->u, DTR(rot.x));
	basis->u = clvec_rot_y(basis->u, DTR(rot.y));
	basis->u = clvec_rot_z(basis->u, DTR(rot.z));

	basis->v = clvec_rot_x(basis->v, DTR(rot.x));
	basis->v = clvec_rot_y(basis->v, DTR(rot.y));
	basis->v = clvec_rot_z(basis->v, DTR(rot.z));

	basis->w = clvec_rot_x(basis->w, DTR(rot.x));
	basis->w = clvec_rot_y(basis->w, DTR(rot.y));
	basis->w = clvec_rot_z(basis->w, DTR(rot.z));
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
	cl_float3	rot;

	i = 0;
	tmp = default_cylinder();
	l = value->u.object.length;
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < l)
	{
		v = *(value->u.object.values[i].value);
		//printf("%s   %f\n", value->u.object.values[i].name, value->u.object.values[i].value->u.dbl);
		fill_position(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.primitive.cylinder.pos));
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.cylinder.r = (cl_float)v.u.dbl;
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		fill_rotate(value->u.object.values[i].name, (cl_float)v.u.dbl, &(rot));
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "texture") == 0)
			tmp.tex_id = load_texture(v.u.string.ptr);
		//fill_u(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.basis.u));
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	tmp.type = cylinder;
	minus_camera(&(tmp.primitive.cylinder.pos), scene->cam.pos);
	//tmp.primitive.cylinder.rot = NORMAL(tmp.primitive.cylinder.rot);
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
	cl_float3	rot;

	i = 0;
	tmp = default_cone();
	l = value->u.object.length;
	rot = (cl_float3){0.0, 0.0, 0.0};
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
			(cl_float)v.u.dbl, &(rot));
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "texture") == 0)
			tmp.tex_id = load_texture(v.u.string.ptr);
		//fill_u(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.basis.u));
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.cone.pos), scene->cam.pos);
	tmp.type = cone;
	//tmp.primitive.cone.rot = NORMAL(tmp.primitive.cone.rot);
	scene->obj[scene->cur_obj++] = tmp;
	print_cone(tmp);


}

void	filltheplane(json_value *value, t_scene *scene)
{
	int		i;
	int l;
	t_obj	tmp;
	json_value v;
	cl_float3	rot;

	i = 0;
	tmp = default_plane();
	rot = (cl_float3){0.0, 0.0, 0.0};
	l = value->u.object.length;
	while (i < l)
	{
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.plane.pos));
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		fill_rotate(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &rot);
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "texture") == 0)
			tmp.tex_id = load_texture(v.u.string.ptr);
		//fill_u(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.basis.u));
		i++;
	}
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.plane.pos), scene->cam.pos);
	//tmp.primitive.plane.rot = NORMAL(tmp.primitive.plane.rot);
	tmp.type = plane;
	scene->obj[scene->cur_obj++] = tmp;
	print_plane(tmp);
}

void			fillthesphere(json_value *value, t_scene *scene)
{
	int			i;
	int			l;
	t_obj		tmp;
	json_value	v;
	cl_float3	rot;

	i = 0;
	tmp = default_sphere();
	l = value->u.object.length;
	rot = (cl_float3){0.0, 0.0, 0.0};
	while (i < l)
	{
		//printf("%s\n", value->u.object.values[i].name);
		v = *(value->u.object.values[i].value);
		fill_position(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &(tmp.primitive.sphere.pos));
		if (ft_strcmp(value->u.object.values[i].name, "radius") == 0)
			tmp.primitive.sphere.r = (cl_float)v.u.dbl;
		fill_color(value->u.object.values[i].name, (cl_float)v.u.dbl, &tmp);
		if (ft_strcmp(value->u.object.values[i].name, "light") == 0)
			parselight(&v, &tmp);
		fill_rotate(value->u.object.values[i].name,
			(cl_float)v.u.dbl, &rot);
		if (ft_strcmp(value->u.object.values[i].name, "texture") == 0)
			tmp.tex_id = load_texture(v.u.string.ptr);
		//fill_u(value->u.object.values[i].name, (cl_float)v.u.dbl, &(tmp.basis.u));
		i++;
	}
	tmp.type = sphere;
	init_rotate(&(tmp.basis), rot);
	minus_camera(&(tmp.primitive.sphere.pos), scene->cam.pos);
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
	{
		ft_putstr("fov of camera is wrong. setting to default 90..\n");
		printf("\n%f\n", cam->fov);
		cam->fov = 90.0;
	}
	if (cam->aperture < 0.f || cam->aperture >= 100.0)
	{
		ft_putstr("aperture of camera is wrong. setting to def n0.00001..\n");
		cam->aperture = 0.00001f;
	}
	cam->updir.x = 0;
	cam->updir.y = 1;
	cam->updir.z = 0;
	cam->ldir.x = -1;
	cam->ldir.y = 0;
	cam->ldir.z = 0;
	cam->ratio = cam->f_length / calculate_ppd(cam->fov);
	cam->pr_pl_w = g_win_width;
	cam->pr_pl_h = g_win_height;
}

void			get_camera_params(json_value *value, t_scene *scene)
{
	int			l;
	int			i;
	json_value	v;

	l = value->u.object.length;
	i = 0;
	if (l != 10)
		error_fedun("wrong number of parameters in scene");
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
			scene->cam.aperture = (float)v.u.dbl;
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
		if (ft_strcmp("sphere", value->u.object.values[i].name) == 0)
			fillthesphere(value->u.object.values[i].value, scene);
		else if (ft_strcmp("cone", value->u.object.values[i].name) == 0)
			fillthecone(value->u.object.values[i].value, scene);
		else if (ft_strcmp("plane", value->u.object.values[i].name) == 0)
			filltheplane(value->u.object.values[i].value, scene);
		else if (ft_strcmp("cylinder", value->u.object.values[i].name) == 0)
			fillthecylind(value->u.object.values[i].value, scene);
		else
			error_fedun("wrong key in root");
		if (scene->cur_obj >= scene->num_obj)
			return ;
		i++;
	}
}

void		parse_scene(int argc, char **argv, char **contents, size_t *len)
{
	int		fd;

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

void			init_scene(t_scene *scene, int argc, char **argv)
{
	json_value*	value;
	char*		contents;
	size_t		len;

	scene->cur_obj = 0;
	parse_scene(argc, argv, &contents, &len);
	value = json_parse(contents,len);
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
