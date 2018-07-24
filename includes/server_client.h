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
# include "rt_types.h"


t_tpool			*init_tpool(unsigned int count, t_env *env);
int				push_client(t_tpool *tpool, int client_fd);
int				push_message_for_all(t_tpool *tpo, void *message,
	unsigned int message_size, enum e_message type);
void			destroy_tpool(t_tpool *tpool);
void			*read_message(int, atomic_int *, int *, unsigned int *);
void			*compose_message(void *, int, int, unsigned int *);
t_message_queue	*new_message(t_tpool *, void *, unsigned int, enum e_message);
void			send_message(t_thread *thread);

#endif
