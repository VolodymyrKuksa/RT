/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_read_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 12:48:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/30 12:48:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void	read_obj(t_env *env, void *msg, unsigned int size)
{
	if (!(env->scene.obj = (t_obj*)malloc(size)))
		put_error("Could not allocate memory for objects");
	ft_memcpy(env->scene.obj, msg, size);
	env->scene.num_obj = size / (int)sizeof(t_obj);
}

void	read_textures(t_env *env, void *msg, unsigned int size)
{
	if (!(env->textures.tx = (t_rgb*)malloc(size)))
		put_error("Could not allocate memory for textures");
	ft_memcpy(env->textures.tx, msg, size);
	env->textures.total_size = size / (int)sizeof(t_rgb);
}

void	read_tex_data(t_env *env, void *msg, unsigned int size)
{
	if (!(env->textures.txdata = (t_txdata*)malloc(size)))
		put_error("Could not allocate memory for texture data");
	ft_memcpy(env->textures.txdata, msg, size);
	env->textures.tx_count = size / (int)sizeof(t_txdata);
}

void	read_wnd_size(void *msg)
{
	g_win_width = ((unsigned int *)msg)[0];
	g_win_height = ((unsigned int *)msg)[1];
}

void	read_scene(t_env *env)
{
	void			*msg;
	int				type;
	unsigned int	size;
	int				types_got;

	types_got = OBJ | CAM | TEXTURES | TEX_DATA | WND_SIZE;
	while (types_got)
	{
		msg = read_message(env->client.socket_fd, &env->client.message_id,
			&type, &size);
		types_got ^= type;
		if (type == CAM && msg)
			env->scene.cam = *(t_cam*)msg;
		else if (type == OBJ && msg)
			read_obj(env, msg, size);
		else if (type == TEXTURES)
			read_textures(env, msg, size);
		else if (type == TEX_DATA)
			read_tex_data(env, msg, size);
		else if (type == WND_SIZE)
			read_wnd_size(msg);
		free(msg);
	}
}
