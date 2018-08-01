/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_read_msg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:54:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/24 20:54:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

ssize_t		readn(int fd, void *data, size_t size)
{
	char			*ptr;
	ssize_t			n;
	size_t			n_left;

	ptr = data;
	n_left = size;
	while (n_left > 0)
	{
		if ((n = read(fd, ptr, n_left)) < 0)
		{
			n = 0;
		}
		else if (n == 0)
			break ;
		ptr += n;
		n_left -= n;
	}
	return (size - n_left);
}

void		*read_message(int fd, atomic_int *id, int *type, unsigned int *size)
{
	unsigned int	head[3];
	static size_t	head_size = sizeof(head[0]) * 3;
	ssize_t			n;
	void			*msg;

	*type = -1;
	*size = 0;
	n = read(fd, head, head_size);
	if (n <= 0 || !(msg = malloc(head[2])))
		return (NULL);
	if (readn(fd, msg, head[2]) < 0)
	{
		free(msg);
		perror("READ FAIL");
		return (NULL);
	}
	*id = head[0];
	*type = head[1];
	*size = head[2];
	return (msg);
}

void		send_message(t_thread *thread)
{
	ssize_t		n;

	set_block(thread->client_fd);
	n = write(thread->client_fd, (*thread->message_queue)->message,
		(*thread->message_queue)->size);
	if (n > 0)
	{
		ft_putstr(">server: sent message to ");
		ft_putendl(thread->client_hostname);
	}
	set_nonblock(thread->client_fd);
}

void		delete_message(t_message_queue **message)
{
	t_message_queue		*tmp;

	if (!*message)
		return ;
	tmp = (*message)->next;
	if ((*message)->dest_size)
		free((*message)->destinations);
	if ((*message)->size)
		free((*message)->message);
	free(*message);
	*message = tmp;
	write(1, "message entry deleted from queue\n", 33);
}

int			push_message_for_all(t_tpool *tpool, void *message,
								unsigned int message_size, enum e_message type)
{
	t_message_queue	*new;

	if (!(new = new_message(tpool, message, message_size, type)))
		return (-1);
	while (pthread_mutex_trylock(&tpool->message_queue_lock) != 0)
		;
	new->next = tpool->message_queue;
	tpool->message_queue = new;
	pthread_mutex_unlock(&tpool->message_queue_lock);
	return (0);
}
