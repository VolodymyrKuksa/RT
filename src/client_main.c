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
unsigned int	g_win_width = 1080;
unsigned int	g_win_height = 720;

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
}

int		main(int argc, char **argv)
{
	t_env	env;

	parse_client_data(&env.client, argc, argv);
	init_client(&env.client);
	set_nonblock(STDIN_FILENO);
//	execute_logic(env.client.socket_fd);

	void			*msg;
	int				type;
	unsigned int	size;

	env.scene.num_obj = 0;

	while (1)
	{
		msg = read_message(env.client.socket_fd, &type, &size);
		if (type == STRING && msg)
		{
			ft_putstr((char *) msg);
			free(msg);
		}
		else if (type == CAM && msg)
		{
			ft_putendl("Got CAM");
			env.scene.cam = *(t_cam*)msg;
			free(msg);
//			print_scene(&env.scene);
		}
		else if (type == OBJ && msg)
		{
			env.scene.obj = (t_obj*)malloc(size);
			ft_memcpy(env.scene.obj, msg, size);
			env.scene.num_obj = size / (int)sizeof(t_obj);
			ft_putendl("Got OBJ");
//			print_scene(&env.scene);
			free(msg);
		}
		else if (type == TEXTURES)
		{
			env.textures.tx = (t_rgb*)malloc(size);
			ft_memcpy(env.textures.tx, msg, size);
			env.textures.total_size = size / (int)sizeof(t_rgb);
			ft_putendl("Got textures");
			free(msg);
		}
		else if (type == TEX_DATA)
		{
			env.textures.txdata = (t_txdata*)malloc(size);
			ft_memcpy(env.textures.txdata, msg, size);
			env.textures.tx_count = size / (int)sizeof(t_txdata);
//			printf("%d\n", env.textures.tx_count);
			ft_putendl("Got TEX_DATA");
			free(msg);
			break ;
		}
	}

	printf("tx count: %d\n", env.textures.tx_count);
	printf("tx size: %d\n", env.textures.total_size);

	init_opencl(&env.cl);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	init_defaults(&env);
	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen);
	main_loop(&env);
	close_sdl(&env.screen);
	IMG_Quit();
	system("leaks -q RT"); //DEBUG

	return (0);
}
