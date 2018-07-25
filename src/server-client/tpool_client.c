/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_new_client.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 10:00:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/25 10:00:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			tpool_kick_client(t_thread *thread)
{
	put_host_log(thread->client_hostname,
		"got kicked by server for not responding.");
	thread->status = FREE;
}

t_client_queue	*new_client(int client_fd)
{
	t_client_queue	*new;

	if (!(new = (t_client_queue*)malloc(sizeof(t_client_queue))))
		return (NULL);
	new->next = NULL;
	new->client_fd = client_fd;
	if (pthread_mutex_init(&new->client_queue_lock, NULL) != 0)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

int				push_client(t_tpool *tpool, int client_fd) //mutex
{
	t_client_queue	*new;

	if (!(new = new_client(client_fd)))
		return (-1);
	new->next = tpool->client_queue;
	tpool->client_queue = new;
	return (0);
}
