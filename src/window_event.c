/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:24:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/29 18:24:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void	cl_free(t_cldata *cl)
{
	cl->global_size = g_win_height * g_win_width;
	free(cl->pixels);
	free(cl->px_host);
	clReleaseMemObject(cl->px_gpu);
	free(cl->seeds.seeds);
	init_seeds(&cl->seeds);
	clReleaseMemObject(cl->seed_gpu);
	clReleaseMemObject(cl->obj_gpu);
}

void	handle_resize(t_env *env)
{
	env->sc.cam.pr_pl_w = g_win_width;
	env->sc.cam.pr_pl_h = g_win_height;
	env->sc.cam.ratio = env->sc.cam.f_length / calculate_ppd(env->sc.cam.fov);
	cl_free(&env->cl);
	cl_setup(env);
	get_work_group_size(&env->cl);
	env->num_samples = 0;
	SDL_FreeSurface(env->screen.surface);
	env->screen.surface = SDL_GetWindowSurface(env->screen.window);
	env->screen.surf_arr = (t_rgb *)env->screen.surface->pixels;
}

/*
**	if the work group is too small (render speed drops rapidly)
**	the window gets one pixel wider
*/

void	window_event(SDL_Event e, t_env *env)
{
	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		g_win_width = (unsigned int)e.window.data1;
		g_win_height = (unsigned int)e.window.data2;
		handle_resize(env);
		if (env->cl.local_size < 50)
			SDL_SetWindowSize(env->screen.window, ++g_win_width, g_win_height);
	}
}
