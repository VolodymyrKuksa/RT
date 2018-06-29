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

void	window_event(SDL_Event e, t_env *env)
{
	if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		g_win_width = (unsigned int)e.window.data1;
		g_win_height = (unsigned int)e.window.data2;
		env->sc.cam.pr_pl_w = g_win_width;
		env->sc.cam.pr_pl_h = g_win_height;
		cl_free(&env->cl);
		cl_setup(env);
		get_work_group_size(&env->cl);
		env->num_samples = 0;
		SDL_FreeSurface(env->screen.surface);
		env->screen.surface = SDL_GetWindowSurface(env->screen.window);
		env->screen.surf_arr = (t_rgb *)env->screen.surface->pixels;
	}
}
