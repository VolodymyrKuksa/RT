/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_new_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:46:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/24 20:46:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			*compose_message(void *message, int id, int type,
	unsigned int *size)
{
	void	*res;
	int		tmp;

	tmp = sizeof(type) * 3;
	if (!(res = malloc(*size + tmp)))
		return (NULL);
	ft_memcpy(res, &id, sizeof(id));
	ft_memcpy(res + sizeof(id), &type, sizeof(type));
	ft_memcpy(res + sizeof(id) + sizeof(type), size, sizeof(*size));
	if (message)
		ft_memcpy(res + tmp, message, *size);
	*size += tmp;
	return (res);
}

void			fill_destinations(t_tpool *tpool, int *destinations)
{
	unsigned int	i;

	i = (unsigned int)(-1);
	while (++i < tpool->total_threads)
	{
		if (tpool->threads[i].status == BUSY)
			destinations[i] = tpool->threads[i].thread_id;
		else
			destinations[i] = -1;
	}
}

t_message_queue	*new_message(t_tpool *tpool, void *message,
	unsigned int message_size, enum e_message type)
{
	t_message_queue	*new;

	if (!(new = (t_message_queue*)malloc(sizeof(t_message_queue))))
		return (NULL);
	if (!(new->destinations = (int*)malloc(sizeof(int) * tpool->total_threads)))
	{
		free(new);
		return (NULL);
	}
	new->size = message_size;
	if (!(new->message = compose_message(message,
		++tpool->env->server.message_id, type, &new->size)))
	{
		free(new->destinations);
		free(new);
		return (NULL);
	}
	new->dest_size = tpool->total_threads;
	new->type = type;
	new->next = NULL;
	fill_destinations(tpool, new->destinations);
	return (new);
}
