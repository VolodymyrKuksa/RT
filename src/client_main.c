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
//	set_nonblock(client->socket_fd);
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

	msg = read_message(env.client.socket_fd, &type, &size);
	if (type == STRING && msg)
	{
		ft_putstr((char*)msg);
		free(msg);
	}

	return (0);
}
