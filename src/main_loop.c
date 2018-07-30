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
	float		sample_influence;
	int			i;

	++(env->num_samples);
	sample_influence = (1.0f / env->num_samples);
	i = -1;
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
		/* draw */
		env->gui.draw(env->screen.renderer, &env->gui);
		/* draw */
	}
	SDL_RenderPresent(env->screen.renderer);
	SDL_UpdateWindowSurface(env->screen.window);
}

void	handle_events(t_env *env)
{
	SDL_Event			e;
	static t_gui_obj	*temp;
	static int			x;
	static int			y;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			env->mv_data.move_keys |= KEY_ESC;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			keyboard_event(e, env);
		else if (e.type == SDL_WINDOWEVENT)
			window_event(e, env);
		else if (e.type == SDL_MOUSEWHEEL)
			mouse_wheel_event(e, env);
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			/* collision */
			x = e.button.x;
			y = e.button.y;
			temp = env->gui.collision(e.button.x, e.button.y, (t_gui_obj *)&env->gui);
			/* collision */
			if (!temp)
			{
				size_t		global_size = 1;
				clSetKernelArg(env->cl.kr_intersect, 0, sizeof(int), &e.button.x);
				clSetKernelArg(env->cl.kr_intersect, 1, sizeof(int), &e.button.y);
				clEnqueueNDRangeKernel(env->cl.command_queue, env->cl.kr_intersect,
					1, 0, &global_size, 0, 0, 0, 0);
				clEnqueueReadBuffer(env->cl.command_queue, env->cl.id_gpu, CL_FALSE,
					0, sizeof(int), env->cl.id_host, 0, 0, 0);
				clFinish(env->cl.command_queue);
				printf("id: %d, type: %d\n", *env->cl.id_host,
				env->scene.obj[*env->cl.id_host].type);
			}
		}
		else if (e.type == SDL_MOUSEMOTION)
		{
			/* collision */
			if (temp && temp->type == 1)
			{
				env->gui.mouse->dx = e.motion.x - x;
				env->gui.mouse->dy = e.motion.y - y;
				x = e.motion.x;
				y = e.motion.y;
				if (temp == env->gui.collision(e.button.x, e.button.y, (t_gui_obj *)&env->gui))
					temp->action((void *)temp, env->screen.renderer);
			}
			/* collision */
		}
		else if (e.type == SDL_MOUSEBUTTONUP)
		{
			/* collision */
			if (temp == env->gui.collision(e.button.x, e.button.y, (t_gui_obj *)&env->gui) && temp && temp->type == 0)
			{
				if (temp->father)
					temp->action((void *)temp->father, env->screen.renderer);
				else
					temp->action((void *)temp, env->screen.renderer);
			}
			/* collisison */
			temp = NULL;
		}
	}
}

void	handle_events_client(t_env *env)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			env->mv_data.move_keys |= KEY_ESC;
		else if (e.type == SDL_WINDOWEVENT)
			window_event(e, env);
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			env->mv_data.move_keys |= KEY_ESC;
	}
}

void	main_loop_server(t_env *env)
{
	cl_setup(env);
	/* creation */
	env->gui = init_gui(env->screen.renderer, &env->scene);
	/* creation */
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
		while (pthread_mutex_trylock(&env->cl.pixel_lock) != 0);
		update_window(env);
		pthread_mutex_unlock(&env->cl.pixel_lock);
	}
}

void	send_pixels(t_env *env)
{
	void			*msg;
	unsigned int	size;

	size = (unsigned int)(sizeof(cl_float3) * env->cl.global_size);
	msg = compose_message(env->cl.pixels, env->client.message_id, PIXELS, &size);
	set_block(env->client.socket_fd);
	if (write(env->client.socket_fd, msg, size) > 0)
		printf("sent pixels\n");
	set_nonblock(env->client.socket_fd);
	free(msg);
	ft_bzero(env->cl.pixels, env->cl.global_size * sizeof(cl_float3));
	env->num_samples = 0;
}

void	main_loop_client(t_env *env)
{
	void			*msg;
	int				type;
	unsigned int	size;
	time_t			t;

	cl_setup(env);
	t = time(NULL);
	while (!(env->mv_data.move_keys & KEY_ESC))
	{
		handle_events_client(env);

		msg = read_message(env->client.socket_fd, &env->client.message_id, &type, &size);
		if (msg)
		{
			if (type == OBJ)
			{
				free(env->scene.obj);
				if (!(env->scene.obj = (t_obj *) malloc(size)))
					put_error("Could not allocate memory for objects");
				ft_memcpy(env->scene.obj, msg, size);
				env->scene.num_obj = size / (int) sizeof(t_obj);
				env->num_samples = 0;
				ft_bzero(env->cl.pixels, sizeof(cl_float3) * env->cl.global_size);
				write_scene_to_kernel(env);
			}
			else if (type == CAM)
			{
				ft_memcpy(&env->scene.cam, msg, size);
				env->num_samples = 0;
				clSetKernelArg(env->cl.kernel, 3, sizeof(env->scene.cam), &env->scene.cam);
			}
			else if (type == WND_SIZE)
			{
				printf("wndsize\n");
				SDL_SetWindowSize(env->screen.window, ((unsigned int*)msg)[0],
					((unsigned int*)msg)[1]);
				printf("yo\n");
			}
			else if (type == QUIT)
				env->mv_data.move_keys |= KEY_ESC;
			free(msg);
		}

		cl_exec(&env->cl);
		update_window(env);
		if (env->num_samples == CLIENT_WORK_SIZE)
		{
			send_pixels(env);
			t = time(NULL);
		}
		else if (time(NULL) - t > 10)
		{
			size = 0;
			msg = compose_message(NULL, env->client.message_id, CONNECTION, &size);
			write(env->client.socket_fd, msg, size);
			free(msg);
			t = time(NULL);
			printf("connection message sent\n");
		}
	}
	size = 0;
	msg = compose_message(NULL, env->client.message_id, QUIT, &size);
	write(env->client.socket_fd, msg, size);
	free(msg);
}
