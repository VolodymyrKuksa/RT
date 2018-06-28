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

void	write_scene_to_kernel(t_cldata *cl)
{
	clEnqueueWriteBuffer(cl->command_queue, cl->obj_gpu, CL_TRUE, 0,
		sizeof(t_obj) * cl->sc.num_obj, cl->sc.obj, 0, 0, 0);
}

void	turn(float d, t_cldata *cl, cl_float3 (*f)(float, cl_float3, t_mvdata))
{
	int i;

	i = -1;
	while (++i < cl->sc.num_obj)
	{
		cl->sc.obj[i].primitive.sphere.pos = f(d, cl->sc.obj[i].primitive.sphere.pos, cl->mv_data);
		cl->sc.obj[i].primitive.sphere.rot = f(d, cl->sc.obj[i].primitive.sphere.rot, cl->mv_data);
	}
	cl->num_samples = 0;
	clear_pixels(cl);
	write_scene_to_kernel(cl);
}

void	move(t_cldata *cl, float x, float y, float z)
{
	int i;

	i = -1;
	while (++i < cl->sc.num_obj)
	{
		cl->sc.obj[i].primitive.sphere.pos.x += x * cl->mv_data.move_spd;
		cl->sc.obj[i].primitive.sphere.pos.y += y * cl->mv_data.move_spd;
		cl->sc.obj[i].primitive.sphere.pos.z += z * cl->mv_data.move_spd;
	}
	cl->num_samples = 0;
	clear_pixels(cl);
	write_scene_to_kernel(cl);
}

void	movement_events(t_cldata *cl)
{
	if (cl->move_keys & KEY_W)
		turn(-1, cl, rotate_x);
	if (cl->move_keys & KEY_S)
		turn(1, cl, rotate_x);
	if (cl->move_keys & KEY_A)
		turn(-1, cl, rotate_y);
	if (cl->move_keys & KEY_D)
		turn(1, cl, rotate_y);
	if (cl->move_keys & KEY_Q)
		turn(-1, cl, rotate_z);
	if (cl->move_keys & KEY_E)
		turn(1, cl, rotate_z);
	if (cl->move_keys & KEY_UP)
		move(cl, 0, 0, 1);
	if (cl->move_keys & KEY_DOWN)
		move(cl, 0, 0, -1);
	if (cl->move_keys & KEY_RIGHT)
		move(cl, -1, 0, 0);
	if (cl->move_keys & KEY_LEFT)
		move(cl, 1, 0, 0);
	if (cl->move_keys & KEY_SPACE)
		move(cl, 0, -1, 0);
	if (cl->move_keys & KEY_LSHIFT)
		move(cl, 0, 1, 0);
}
