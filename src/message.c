/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:56:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/31 16:56:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	send_pixels(t_env *env)
{
	void			*msg;
	unsigned int	size;

	size = (unsigned int)(sizeof(cl_float3) * env->cl.global_size);
	msg = compose_message(env->cl.pixels, env->client.message_id, PIXELS,
						  &size);
	set_block(env->client.socket_fd);
	if (write(env->client.socket_fd, msg, size) > 0)
		ft_putendl("sent pixels");
	set_nonblock(env->client.socket_fd);
	free(msg);
	ft_bzero(env->cl.pixels, env->cl.global_size * sizeof(cl_float3));
	env->num_samples = 0;
}

void	handle_message(t_env *env)
{
	void			*msg;
	int				type;
	unsigned int	size;

	if (!(msg = read_message(env->client.socket_fd, &env->client.message_id,
							 &type, &size)))
		return ;
	if (type == OBJ)
	{
		free(env->scene.obj);
		read_obj(env, msg, size);
		env->num_samples = 0;
		write_scene_to_kernel(env);
	}
	else if (type == CAM)
	{
		env->scene.cam = *(t_cam*)msg;
		env->num_samples = 0;
		clSetKernelArg(env->cl.kernel, 3, sizeof(t_cam), &env->scene.cam);
	}
	else if (type == WND_SIZE)
		SDL_SetWindowSize(env->screen.window, ((int*)msg)[0], ((int*)msg)[1]);
	else if (type == QUIT)
		env->mv_data.move_keys |= KEY_ESC;
	free(msg);
}

void	send_connection_msg(t_env *env, time_t *t)
{
	void			*msg;
	unsigned int	size;

	size = 0;
	msg = compose_message(NULL, env->client.message_id, CONNECTION, &size);
	write(env->client.socket_fd, msg, size);
	free(msg);
	*t = time(NULL);
	ft_putendl("connection message sent");
}

void	send_quit_msg(t_env *env)
{
	void			*msg;
	unsigned int	size;

	size = 0;
	msg = compose_message(NULL, env->client.message_id, QUIT, &size);
	write(env->client.socket_fd, msg, size);
	free(msg);
}