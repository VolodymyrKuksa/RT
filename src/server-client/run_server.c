/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_server.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 16:54:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/20 16:54:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_server(t_server *server, t_env *env)
{
	if ((server->serv_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		put_error("Cannot create server socket");
	ft_bzero(&server->serv_addr, sizeof(server->serv_addr));
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_addr.s_addr = INADDR_ANY;
	server->serv_addr.sin_port = htons(server->port_no);
	if ((bind(server->serv_socket_fd, (struct sockaddr*)&server->serv_addr,
		sizeof(server->serv_addr))) < 0)
		put_error("Cannot bind socket");
	listen(server->serv_socket_fd, 5);
	set_nonblock(server->serv_socket_fd);
	if (!(server->tpool = init_tpool(server->num_threads, env)))
		put_error("Cannot initialize thread pool");
	server->active = 1;
	server->message_id = 0;
}

void	*check_new_connection(void *data)
{
	t_server			*server;
	struct sockaddr_in	client_addr;
	socklen_t			client_size;
	int					client_socket_fd;

	server = (t_server*)data;
	client_size = sizeof(client_addr);
	while (server->active)
	{
		client_socket_fd = accept(server->serv_socket_fd,
			(struct sockaddr*)&client_addr, &client_size);
		if (client_socket_fd > 0)
		{
			set_nonblock(client_socket_fd);
			push_client(server->tpool, client_socket_fd);
		}
	}
	pthread_exit(0);
}

void	run_server(t_env *env)
{
	init_server(&env->server, env);
	ft_putendl("server init success");
	pthread_create(&env->server.pid, NULL, check_new_connection, &env->server);
}

void	quit_server(t_server *server)
{
	if (!server->active)
		return ;
	push_message_for_all(server->tpool, NULL, 0, QUIT);
	server->active = 0;
	pthread_join(server->pid, NULL);
	destroy_tpool(server->tpool);
	ft_putendl("Server quit");
}
