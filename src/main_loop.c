/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 20:57:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/21 20:57:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void	clamp(cl_float3 *px)
{
	px->x = px->x < 0.f ? 0.f : px->x;
	px->y = px->y < 0.f ? 0.f : px->y;
	px->z = px->z < 0.f ? 0.f : px->z;
	px->x = px->x > 1.f ? 1.f : px->x;
	px->y = px->y > 1.f ? 1.f : px->y;
	px->z = px->z > 1.f ? 1.f : px->z;
}

void	update_window(t_env *env)
{
	float			sample_influence;
	unsigned int	i;

	sample_influence = (1.0f / (++env->num_samples));
	i = (unsigned int)(-1);
	while (++i < env->cl.global_size)
	{
		env->cl.pixels[i].x *= 1.0f - sample_influence;
		env->cl.pixels[i].y *= 1.0f - sample_influence;
		env->cl.pixels[i].z *= 1.0f - sample_influence;
		env->cl.pixels[i].x += env->cl.px_host[i].x * sample_influence;
		env->cl.pixels[i].y += env->cl.px_host[i].y * sample_influence;
		env->cl.pixels[i].z += env->cl.px_host[i].z * sample_influence;
		clamp(env->cl.pixels + i);
		env->screen.surf_arr[i].bgra[0] = (u_char)(env->cl.pixels[i].z * 0xff);
		env->screen.surf_arr[i].bgra[1] = (u_char)(env->cl.pixels[i].y * 0xff);
		env->screen.surf_arr[i].bgra[2] = (u_char)(env->cl.pixels[i].x * 0xff);
	}
	if (!env->client.active)
	{
		env->gui.update(&env->gui, env->screen.renderer);
		env->gui.draw(env->screen.renderer, &env->gui);
	}
	SDL_RenderPresent(env->screen.renderer);
	SDL_UpdateWindowSurface(env->screen.window);
}

int		get_mouse_intersection(t_env *env, SDL_Event e)
{
	size_t		global_size;

	global_size = 1;
	clSetKernelArg(env->cl.kr_intersect, 0, sizeof(int), &e.button.x);
	clSetKernelArg(env->cl.kr_intersect, 1, sizeof(int), &e.button.y);
	clEnqueueNDRangeKernel(env->cl.command_queue, env->cl.kr_intersect,
		1, 0, &global_size, 0, 0, 0, 0);
	clEnqueueReadBuffer(env->cl.command_queue, env->cl.id_gpu, CL_FALSE,
		0, sizeof(int), env->cl.id_host, 0, 0, 0);
	clFinish(env->cl.command_queue);
	return (*env->cl.id_host);
}

void	main_loop_server(t_env *env)
{
	cl_setup(env);
	while (!(env->mv_data.move_keys & KEY_ESC))
	{
		handle_events(env);
		if (env->mv_data.move_keys)
		{
			movement_events(env);
			if (env->server.active)
				push_message_for_all(env->server.tpool, env->scene.obj,
					env->scene.num_obj * sizeof(t_obj), OBJ);
		}
		cl_exec(&env->cl);
		while (pthread_mutex_trylock(&env->cl.pixel_lock) != 0)
			;
		update_window(env);
		pthread_mutex_unlock(&env->cl.pixel_lock);
	}
}

void	main_loop_client(t_env *env)
{
	time_t			t;

	cl_setup(env);
	t = time(NULL);
	while (!(env->mv_data.move_keys & KEY_ESC))
	{
		handle_events_client(env);
		handle_message(env);
		cl_exec(&env->cl);
		update_window(env);
		if (env->num_samples == CLIENT_WORK_SIZE)
		{
			send_pixels(env);
			t = time(NULL);
		}
		else if (time(NULL) - t > 10)
			send_connection_msg(env, &t);
	}
	send_quit_msg(env);
}
