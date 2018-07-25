/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 16:07:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/16 16:07:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		check_message_out(t_thread *thread)
{
	int			i;
	int			to_del;

	to_del = 1;
	i = -1;
	while (++i < (*thread->message_out)->dest_size)
	{
		to_del = (*thread->message_out)->destinations[i] >= 0 &&
			(*thread->message_out)->destinations[i] != thread->thread_id &&
			to_del == 1 ? 0 : to_del;
		if ((*thread->message_out)->destinations[i] == thread->thread_id)
		{
			send_message(thread);
			(*thread->message_out)->destinations[i] = -1;
		}
	}
	if (to_del)
		delete_message(thread->message_out);
	else
		pthread_mutex_unlock(&(*thread->message_out)->message_queue_lock);
}

void		put_host_log(char *name, char *log)
{
	ft_putstr(name);
	ft_putstr(": ");
	ft_putendl(log);
}

void		tpool_execute_logic(t_thread *this)
{
	time_t			t;

	send_starting_data(this);
	t = time(NULL);
	while (this->status == BUSY)
	{
		process_client_input(this, &t);
		if (*(this->message_out) &&
			!pthread_mutex_trylock(&(*this->message_out)->message_queue_lock))
			check_message_out(this);
		if (time(NULL) - t > 15)
			tpool_kick_client(this);
	}
}

t_tpool		*init_tpool(unsigned int count, t_env *env)
{
	t_tpool		*tpool;

	if (!(tpool = (t_tpool *)malloc(sizeof(t_tpool))))
		return (NULL);
	if (!(tpool->threads = (t_thread *)malloc(sizeof(t_thread) * count)))
	{
		free(tpool);
		return (NULL);
	}
	tpool->total_threads = count;
	tpool->client_queue = NULL;
	tpool->message_out = NULL;
	tpool->env = env;
	init_threads(tpool);
	return (tpool);
}
