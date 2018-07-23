/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 16:59:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/21 16:59:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
unsigned int		g_win_width = 1080;
unsigned int		g_win_height = 720;

void	print_usage(char *name)
{
	ft_putstr("USAGE: ");
	ft_putstr(name);
	ft_putendl(" [server hostname] [port no]");
	exit(1);
}

void	parse_client_data(t_client *client, int ac, char **av)
{
	if (ac != 3)
		print_usage(av[0]);
	client->server = gethostbyname(av[1]);
	if (!client->server)
		put_error("Could not find server");
	client->portno = ft_atoi(av[2]);
}

void	init_client(t_client *client)
{
	if ((client->socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		put_error("Could not create socket");
	ft_bzero(&client->server_addr, sizeof(client->server_addr));
	client->server_addr.sin_family = AF_INET;
	client->server_addr.sin_port = htons(client->portno);
	ft_memcpy(&client->server_addr.sin_addr, client->server->h_addr,
		(size_t)client->server->h_length);
	if ((connect(client->socket_fd, (struct sockaddr *)&client->server_addr,
		sizeof(client->server_addr))) < 0)
		put_error("Could not connect to server");
	set_nonblock(client->socket_fd);
	client->message_id = 0;
	client->active = 1;
}

void	read_scene(t_env *env)
{
	void			*msg;
	int				type;
	unsigned int	size;
	int				types_got;

	types_got = OBJ | CAM | TEXTURES | TEX_DATA;
	env->scene.num_obj = 0;//
	env->textures.tx = NULL;//
	while (types_got)
	{
		msg = read_message(env->client.socket_fd, &env->client.message_id, &type, &size);
		types_got ^= type;
		if (type == STRING && msg)
			ft_putstr((char *) msg);
		else if (type == CAM && msg)
			env->scene.cam = *(t_cam*)msg;
		else if (type == OBJ && msg)
		{
			if (!(env->scene.obj = (t_obj*)malloc(size)))
				put_error("Could not allocate memory for objects");
			ft_memcpy(env->scene.obj, msg, size);
			env->scene.num_obj = size / (int)sizeof(t_obj);
		}
		else if (type == TEXTURES)
		{
			if (!(env->textures.tx = (t_rgb*)malloc(size)))
				put_error("Could not allocate memory for textures");
			ft_memcpy(env->textures.tx, msg, size);
			env->textures.total_size = size / (int)sizeof(t_rgb);
		}
		else if (type == TEX_DATA)
		{
			if (!(env->textures.txdata = (t_txdata*)malloc(size)))
				put_error("Could not allocat memory for texture data");
			ft_memcpy(env->textures.txdata, msg, size);
			env->textures.tx_count = size / (int)sizeof(t_txdata);
		}
		free(msg);
	}
	printf("message id: %d\n", env->client.message_id);
}

int		main(int argc, char **argv)
{
	t_env	env;

	env.server.active = 0;
	parse_client_data(&env.client, argc, argv);
	init_client(&env.client);
	read_scene(&env);
	set_nonblock(STDIN_FILENO);
	init_opencl(&env.cl);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	init_defaults(&env);
	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen);
	main_loop_client(&env);
	close_sdl(&env.screen);
	IMG_Quit();
	system("leaks -q client"); //DEBUG

	return (0);
}
