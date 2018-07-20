/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_pool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:28:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/16 17:28:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLIENT_H
# define SERVER_CLIENT_H

# include <stdio.h>//
# include <stdlib.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/socket.h>
# include <netdb.h>
# include "libft.h"

enum				e_status
{
	BUSY,
	FREE
};

enum				e_message
{
	STRING,
	SCENE,
	QUIT,
	PIXELS,
	CONNECTION
};

typedef struct		s_client_queue
{
	pthread_mutex_t			client_queue_lock;
	int						client_fd;
	struct s_client_queue	*next;
}					t_client_queue;

typedef struct		s_message_queue
{
	pthread_mutex_t			message_queue_lock;
	enum e_message			type;
	unsigned int			size;
	void					*message;
	int						*destinations;
	size_t					dest_size;
	struct s_message_queue	*next;
}					t_message_queue;

typedef struct		s_thread
{
	int				thread_id;
	pthread_t		pid;
	unsigned int	status;
	unsigned int	alive;
	int				client_fd;
	char			*client_hostname;
	t_client_queue	**client_queue;
	t_message_queue	**message_out;
	t_message_queue	**message_in;
}					t_thread;

typedef struct		s_tpool
{
	unsigned int	total_threads;
	t_thread		*threads;
	t_client_queue	*client_queue;
	t_message_queue	*message_out;
	t_message_queue	*message_in;
}					t_tpool;

t_tpool		*init_tpool(unsigned int count);
int			push_client(t_tpool *tpool, int client_fd);
int			push_message_for_all(t_tpool *tpo, void *message,
	unsigned int message_size, enum e_message type);
void		destroy_tpool(t_tpool *tpool);
void		*read_message(int fd, int *type, unsigned int *size);
void		*compose_message(void *message, int type, unsigned int *size);

#endif
