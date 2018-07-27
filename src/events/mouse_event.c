/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 18:01:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/24 18:01:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	mouse_wheel_event(SDL_Event e, t_env *env)
{
	float	ppd_spd;
	float	foc_spd;

	ppd_spd = 0.5;
	foc_spd = 0.01;
	if (e.wheel.y > 0)
		env->scene.cam.f_length -= ppd_spd;
	else if (e.wheel.y < 0)
		env->scene.cam.f_length += ppd_spd;
	else if (e.wheel.x > 0)
		env->scene.cam.aperture += foc_spd;
	else if (e.wheel.x < 0)
		env->scene.cam.aperture -= foc_spd;
	else
		return ;
	env->scene.cam.ratio = env->scene.cam.f_length /
		calculate_ppd(env->scene.cam.fov);
	clear_pixels(&env->cl);
	env->num_samples = 0;
	clSetKernelArg(env->cl.kernel, 3, sizeof(env->scene.cam), &env->scene.cam);
	if (env->server.active)
		push_message_for_all(env->server.tpool, &env->scene.cam,
			sizeof(env->scene.cam), CAM);
}
