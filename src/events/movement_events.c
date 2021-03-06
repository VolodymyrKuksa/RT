/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 19:27:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 19:27:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int		g_win_width;
extern unsigned int		g_win_height;

void	clear_pixels(t_cldata *cl)
{
	unsigned int i;
	unsigned int size;

	i = 0;
	size = g_win_height * g_win_width;
	while (i < size)
	{
		cl->pixels[i].x = 0;
		cl->pixels[i].y = 0;
		cl->pixels[i].z = 0;
		i++;
	}
}

void	write_scene_to_kernel(t_env *env)
{
	clEnqueueWriteBuffer(env->cl.command_queue, env->cl.obj_gpu, CL_TRUE, 0,
		sizeof(t_obj) * env->scene.num_obj, env->scene.obj, 0, 0, 0);
}

void	turn(float d, t_env *env, cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	static void	(*rt[10])(float, t_obj *,
		t_mvdata, cl_float3 (*fun)(float, cl_float3, t_mvdata)) = {rot_sphere,
		rot_plane, rot_cylinder, rot_cone, rot_torus, rot_disk, rot_rectangle,
		rot_parallelogram, rot_triangle, rot_paraboloid};
	int			i;

	i = -1;
	while (++i < env->scene.num_obj)
	{
		rt[env->scene.obj[i].type](d, &env->scene.obj[i], env->mv_data, f);
		env->scene.obj[i].basis.u = f(d, env->scene.obj[i].basis.u,
			env->mv_data);
		env->scene.obj[i].basis.v = f(d, env->scene.obj[i].basis.v,
			env->mv_data);
		env->scene.obj[i].basis.w = f(d, env->scene.obj[i].basis.w,
			env->mv_data);
	}
	env->num_samples = 0;
	clear_pixels(&env->cl);
	write_scene_to_kernel(env);
}

void	move(t_env *env, float x, float y, float z)
{
	static void	(*mv[10])(cl_float3, t_obj *, t_mvdata) = {mv_sphere, mv_plane,
		mv_cylinder, mv_cone, mv_torus, mv_disk, mv_rectangle, mv_parallelogram,
		mv_triangle, mv_paraboloid};
	int			i;
	cl_float3	d;

	d.x = x;
	d.y = y;
	d.z = z;
	i = -1;
	while (++i < env->scene.num_obj)
		mv[env->scene.obj[i].type](d, &env->scene.obj[i], env->mv_data);
	env->num_samples = 0;
	clear_pixels(&env->cl);
	write_scene_to_kernel(env);
}

void	movement_events(t_env *env)
{
	if (env->mv_data.move_keys & KEY_W)
		turn(-1, env, rotate_x);
	if (env->mv_data.move_keys & KEY_S)
		turn(1, env, rotate_x);
	if (env->mv_data.move_keys & KEY_A)
		turn(-1, env, rotate_y);
	if (env->mv_data.move_keys & KEY_D)
		turn(1, env, rotate_y);
	if (env->mv_data.move_keys & KEY_Q)
		turn(-1, env, rotate_z);
	if (env->mv_data.move_keys & KEY_E)
		turn(1, env, rotate_z);
	if (env->mv_data.move_keys & KEY_UP)
		move(env, 0, 0, 1);
	if (env->mv_data.move_keys & KEY_DOWN)
		move(env, 0, 0, -1);
	if (env->mv_data.move_keys & KEY_RIGHT)
		move(env, -1, 0, 0);
	if (env->mv_data.move_keys & KEY_LEFT)
		move(env, 1, 0, 0);
	if (env->mv_data.move_keys & KEY_SPACE)
		move(env, 0, -1, 0);
	if (env->mv_data.move_keys & KEY_LSHIFT)
		move(env, 0, 1, 0);
}
