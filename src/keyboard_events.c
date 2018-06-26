/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:35:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 16:35:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <assert.h>

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
	int err;

	err = clEnqueueWriteBuffer(cl->command_queue, cl->obj_gpu, CL_TRUE, 0,
		sizeof(t_sphere) * cl->sc.num_obj, cl->sc.obj, 0, 0, 0);
	assert(err == CL_SUCCESS);
}

void	turn(double degree, t_cldata *cl, cl_float3 (*f)(cl_float3, double))
{
	int i;

	i = -1;
	while (++i < cl->sc.num_obj)
		cl->sc.obj[i].pos = f(cl->sc.obj[i].pos, DTR(degree));
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
		cl->sc.obj[i].pos.x += x;
		cl->sc.obj[i].pos.y += y;
		cl->sc.obj[i].pos.z += z;
	}
	cl->num_samples = 0;
	clear_pixels(cl);
	write_scene_to_kernel(cl);
}

int		keyboard_event(SDL_Event e, t_cldata *cl)
{
	if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		return (1);
	else if (e.key.keysym.sym == SDLK_w)
		turn(-2.5, cl, clvec_rot_x);
	else if (e.key.keysym.sym == SDLK_s)
		turn(2.5, cl, clvec_rot_x);
	else if (e.key.keysym.sym == SDLK_a)
		turn(-2.5, cl, clvec_rot_y);
	else if (e.key.keysym.sym == SDLK_d)
		turn(2.5, cl, clvec_rot_y);
	else if (e.key.keysym.sym == SDLK_q)
		turn(-2.5, cl, clvec_rot_z);
	else if (e.key.keysym.sym == SDLK_e)
		turn(2.5, cl, clvec_rot_z);
	else if (e.key.keysym.sym == SDLK_UP)
		move(cl, 0, 0, 1);
	else if (e.key.keysym.sym == SDLK_DOWN)
		move(cl, 0, 0, -1);
	else if (e.key.keysym.sym == SDLK_RIGHT)
		move(cl, -1, 0, 0);
	else if (e.key.keysym.sym == SDLK_LEFT)
		move(cl, 1, 0, 0);
	else if (e.key.keysym.sym == SDLK_SPACE)
		move(cl, 0, -1, 0);
	else if (e.key.keysym.sym == SDLK_c)
		move(cl, 0, 1, 0);
	return (0);
}
