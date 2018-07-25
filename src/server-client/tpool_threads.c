/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:07:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/25 10:07:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		thread_grab_client(t_thread *thread)
{
	struct hostent		*host;
	socklen_t			addr_size;
	t_client_queue		*tmp;
	struct sockaddr_in	client_addr;

	addr_size = sizeof(client_addr);
	thread->client_fd = (*thread->client_queue)->client_fd;
	getpeername(thread->client_fd, (struct sockaddr *)&client_addr, &addr_size);
	host = gethostbyaddr(&client_addr.sin_addr, client_addr.sin_len, AF_INET);
	thread->client_hostname = ft_strdup(host->h_name);
	thread->status = BUSY;
	tmp = (*thread->client_queue);
	(*thread->client_queue) = (*thread->client_queue)->next;
	pthread_mutex_destroy(&tmp->client_queue_lock);
	free(tmp);
	tpool_execute_logic(thread);
	free(thread->client_hostname);
	close(thread->client_fd);
	thread->client_hostname = NULL;
	thread->status = FREE;
}

void		*thread_do(void *data)
{
	t_thread			*this;

	this = (t_thread*)data;
	while (this->alive)
	{
		if (*(this->client_queue) != NULL &&
			!pthread_mutex_trylock(&(*this->client_queue)->client_queue_lock))
			thread_grab_client(this);
	}
	pthread_exit(0);
}

void		init_threads(t_tpool *tpool)
{
	int		i;

	i = -1;
	while (++i < tpool->total_threads)
	{
		tpool->threads[i].thread_id = i;
		tpool->threads[i].status = FREE;
		tpool->threads[i].client_fd = -1;
		tpool->threads[i].client_queue = &tpool->client_queue;
		tpool->threads[i].message_out = &tpool->message_out;
		tpool->threads[i].env = tpool->env;
		tpool->threads[i].alive = 1;
		tpool->threads[i].client_hostname = NULL;
		pthread_create(&tpool->threads[i].pid, NULL, (void*)thread_do,
		&tpool->threads[i]);
	}
}
