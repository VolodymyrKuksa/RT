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
	ft_putendl(" [server hostname] [port no] [-v]");
	exit(1);
}

void	parse_client_data(t_client *client, int ac, char **av)
{
	client->visual = 0;
	if (ac != 3 && ac != 4)
		print_usage(av[0]);
	client->server = gethostbyname(av[1]);
	if (!client->server)
		put_error("Could not find server");
	client->portno = ft_atoi(av[2]);
	if (ac == 4 && ft_strequ(av[3], "-v"))
	{
		client->visual = 1;
		ft_putendl("visual on");
	}
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

int		main(int argc, char **argv)
{
	t_env	env;

	env.server.active = 0;
	parse_client_data(&env.client, argc, argv);
	init_client(&env.client);
	env.scene.num_obj = 0;
	env.textures.tx = NULL;
	read_scene(&env);
	set_nonblock(STDIN_FILENO);
	init_opencl(&env.cl);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	init_defaults(&env);
	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen, 0, env.client.visual);
	if (!env.client.visual)
		SDL_HideWindow(env.screen.window);
	main_loop_client(&env);
	close(env.client.socket_fd);
	close_sdl(&env.screen);
	IMG_Quit();
	return (0);
}
