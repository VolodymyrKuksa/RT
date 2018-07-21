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

#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "server_client.h"

void		tpool_kick_client(t_thread *thread)
{
	ft_putstr(thread->client_hostname);
	ft_putendl(" got kicked by server for not responding");
	thread->status = FREE;
}

void		delete_message(t_message_queue **message)
{
	t_message_queue		*tmp;

	if (!*message)
		return ;
	pthread_mutex_destroy(&(*message)->message_queue_lock);
	tmp = (*message)->next;
	if ((*message)->dest_size)
		free((*message)->destinations);
	if ((*message)->size)
		free((*message)->message);
	free(*message);
	*message = tmp;
	printf("message entry deleted from queue\n");
}

void		send_message(t_thread *thread)
{
	ssize_t		n;

	n = write(thread->client_fd, (*thread->message_out)->message,
		(*thread->message_out)->size);
	if (n > 0)
		printf("Message sent to %s\n", thread->client_hostname);
}

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

//============================================================================//
//============================================================================//

void		send_starting_data(t_thread *thread)
{
	unsigned int	size;
	void			*data;

	size = sizeof(t_cam);
	data = compose_message(&thread->env->scene.cam, CAM, &size);
	write(thread->client_fd, data, size);
	free(data);
	size = sizeof(t_obj) * thread->env->scene.num_obj;
	data = compose_message(thread->env->scene.obj, OBJ, &size);
	write(thread->client_fd, data, size);
	free(data);
	size = (unsigned int)thread->env->textures.total_size * sizeof(t_rgb);
	data = compose_message(thread->env->textures.tx, TEXTURES, &size);
	write(thread->client_fd, data, size);
	free(data);
	size = sizeof(t_txdata) * thread->env->textures.tx_count;
	data = compose_message(thread->env->textures.txdata, TEX_DATA, &size);
	write(thread->client_fd, data, size);
	free(data);
}

void		tpool_execute_logic(t_thread *this)
{
	time_t			t;
	int				type;
	unsigned int	size;
	void			*data;

	size = 8;
	type = STRING;
	data = compose_message("Hello!\n", type, &size);
	write(this->client_fd, data, size);
	free(data);

	send_starting_data(this);

	t = time(NULL);
	while (this->status == BUSY)
	{
		data = read_message(this->client_fd, &type, &size);
		if (data)
		{
			if (type == STRING)
				printf("%s: %s", this->client_hostname, (char*)data);
			else if (type == QUIT)
			{
				this->status = FREE;
				printf("client %s left\n", this->client_hostname);
			}
			free(data);
			t = time(NULL);
		}
		if (*(this->message_out) &&
			!pthread_mutex_trylock(&(*this->message_out)->message_queue_lock))
			check_message_out(this);
		if (time(NULL) - t > 15)
			tpool_kick_client(this);
	}
}

//============================================================================//
//============================================================================//

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
	printf("%s\n", host->h_name);
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

void	clear_client_queue(t_client_queue *cq)
{
	t_client_queue	*tmp;

	if (!cq)
		return ;
	while (cq)
	{
		tmp = cq->next;
		pthread_mutex_destroy(&cq->client_queue_lock);
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
		pthread_mutex_destroy(&mq->message_queue_lock);
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
	clear_message_queue(tpool->message_out);
	free(tpool);
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

int			push_client(t_tpool *tpool, int client_fd) //mutex
{
	t_client_queue	*new;

	if (!(new = new_client(client_fd)))
		return (-1);
	new->next = tpool->client_queue;
	tpool->client_queue = new;
	return (0);
}

void	fill_destinations(t_tpool *tpool, int *destinations)
{
	int		i;

	i = -1;
	while (++i < tpool->total_threads)
	{
		if (tpool->threads[i].status == BUSY)
			destinations[i] = tpool->threads[i].thread_id;
		else
			destinations[i] = -1;
	}
}

void	*read_message(int fd, int *type, unsigned int *size)
{
	unsigned int	head[2];
	static size_t	head_size = sizeof(head[0]) * 2;
	ssize_t			n;
	void			*msg;

	*type = -1;
	*size = 0;
	n = read(fd, head, head_size);
	if (n <= 0 || !(msg = malloc(head[1])))
		return (NULL);
	printf("read_message: type: %d; size: %u\n", head[0], head[1]);
	n = read(fd, msg, head[1]);
	if (n <= 0 && head[1])
	{
		free(msg);
		return (NULL);
	}
	*type = head[0];
	*size = head[1];
	printf("read message success\n");
	return (msg);
}

void	*compose_message(void *message, int type, unsigned int *size)
{
	void	*res;
	int		tmp;

	tmp = sizeof(type) * 2;
	if (!(res = malloc(*size + tmp)))
		return (NULL);
	printf("type: %d\n", type);
	ft_memcpy(res, &type, sizeof(type));
	printf("size: %u\n", *size);
	ft_memcpy(res + sizeof(type), size, sizeof(unsigned int));
	if (message)
		ft_memcpy(res + tmp, message, *size);
	*size += tmp;
	return (res);
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
	if (!(new->message = compose_message(message, type, &new->size))
		|| (pthread_mutex_init(&new->message_queue_lock, NULL) != 0))
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

int		push_message_for_all(t_tpool *tpool, void *message,
	unsigned int message_size, enum e_message type)
{
	t_message_queue	*new;

	if (!(new = new_message(tpool, message, message_size, type)))
		return (-1);
	new->next = tpool->message_out;
	tpool->message_out = new;
	return (0);
}
