/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_client_logic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:32:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/25 10:32:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int	g_win_width;
extern unsigned int g_win_height;

void		send_starting_data_crutch(t_thread *thread)
{
	unsigned int	size;
	unsigned int	tmp[2];
	void			*data;

	size = sizeof(t_txdata) * thread->env->textures.tx_count;
	data = compose_message(thread->env->textures.txdata,
	++thread->env->server.message_id, TEX_DATA, &size);
	write(thread->client_fd, data, size);
	free(data);
	size = sizeof(tmp);
	tmp[0] = g_win_width;
	tmp[1] = g_win_height;
	data = compose_message(&tmp,
	++thread->env->server.message_id, WND_SIZE, &size);
	write(thread->client_fd, data, size);
	free(data);
}

void		send_starting_data(t_thread *thread)
{
	unsigned int	size;
	void			*data;

	set_block(thread->client_fd);
	size = sizeof(t_cam);
	data = compose_message(&thread->env->scene.cam,
	++thread->env->server.message_id, CAM, &size);
	write(thread->client_fd, data, size);
	free(data);
	size = sizeof(t_obj) * thread->env->scene.num_obj;
	data = compose_message(thread->env->scene.obj,
	++thread->env->server.message_id, OBJ, &size);
	write(thread->client_fd, data, size);
	free(data);
	size = (unsigned int)thread->env->textures.total_size * sizeof(t_rgb);
	data = compose_message(thread->env->textures.tx,
	++thread->env->server.message_id, TEXTURES, &size);
	write(thread->client_fd, data, size);
	free(data);
	send_starting_data_crutch(thread);
	set_nonblock(thread->client_fd);
}

void		combine_pixels(t_thread *thread, cl_float3 *client_px)
{
	float	sample_influence;
	int		i;
	t_env	*env;

	env = thread->env;
	sample_influence = (float)CLIENT_WORK_SIZE /
	(env->num_samples + CLIENT_WORK_SIZE);
	i = -1;
	while (pthread_mutex_trylock(&env->cl.pixel_lock) != 0)
		;
	while (++i < env->cl.global_size)
	{
		env->cl.pixels[i].x *= 1.0f - sample_influence;
		env->cl.pixels[i].y *= 1.0f - sample_influence;
		env->cl.pixels[i].z *= 1.0f - sample_influence;
		env->cl.pixels[i].x += client_px[i].x * sample_influence;
		env->cl.pixels[i].y += client_px[i].y * sample_influence;
		env->cl.pixels[i].z += client_px[i].z * sample_influence;
		clamp(env->cl.pixels + i);
		env->screen.surf_arr[i].bgra[0] = (u_char)(env->cl.pixels[i].z * 0xff);
		env->screen.surf_arr[i].bgra[1] = (u_char)(env->cl.pixels[i].y * 0xff);
		env->screen.surf_arr[i].bgra[2] = (u_char)(env->cl.pixels[i].x * 0xff);
	}
	env->num_samples += CLIENT_WORK_SIZE;
	pthread_mutex_unlock(&env->cl.pixel_lock);
}

void		process_client_input(t_thread *thread, time_t *t)
{
	int				type;
	unsigned int	size;
	void			*data;
	atomic_int		msid;

	data = read_message(thread->client_fd, &msid, &type, &size);
	if (data)
	{
		if (type == STRING)
			put_host_log(thread->client_hostname, (char*)data);
		else if (type == QUIT)
		{
			thread->status = FREE;
			put_host_log(thread->client_hostname, "left server.");
		}
		else if (type == PIXELS && msid == thread->env->server.message_id)
		{
			combine_pixels(thread, (cl_float3 *)data);
			put_host_log(thread->client_hostname, "delivered pixels");
		}
		free(data);
		*t = time(NULL);
	}
}
