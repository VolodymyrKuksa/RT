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
	n = write(thread->client_fd, (*thread->message_out)->message,
		(*thread->message_out)->size);
	if (n > 0)
		printf("Message sent to %s\n", thread->client_hostname);
	set_nonblock(thread->client_fd);
}
