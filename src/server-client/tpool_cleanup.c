/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tpool_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 09:54:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/25 09:54:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	clear_client_queue(t_client_queue *cq)
{
	t_client_queue	*tmp;

	if (!cq)
		return ;
	while (cq)
	{
		tmp = cq->next;
		free(cq);
		cq = tmp;
	}
}

void	clear_message_queue(t_message_queue *mq)
{
	t_message_queue	*tmp;

	if (!mq)
		return ;
	while (mq)
	{
		tmp = mq->next;
		free(mq->message);
		free(mq->destinations);
		free(mq);
		mq = tmp;
	}
}

void	destroy_tpool(t_tpool *tpool)
{
	int i;

	i = -1;
	while (++i < tpool->total_threads)
	{
		tpool->threads[i].status = FREE;
		tpool->threads[i].alive = 0;
		pthread_join(tpool->threads[i].pid, NULL);
	}
	free(tpool->threads);
	clear_client_queue(tpool->client_queue);
	pthread_mutex_destroy(&tpool->client_queue_lock);
	clear_message_queue(tpool->message_queue);
	pthread_mutex_destroy(&tpool->message_queue_lock);
	free(tpool);
}
