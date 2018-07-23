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


t_tpool		*init_tpool(unsigned int count, t_env *env);
int			push_client(t_tpool *tpool, int client_fd);
int			push_message_for_all(t_tpool *tpo, void *message,
	unsigned int message_size, enum e_message type);
void		destroy_tpool(t_tpool *tpool);
void		*read_message(int fd, atomic_int *id, int *type, unsigned int *size);
void		*compose_message(void *message, int id, int type, unsigned int *size);

#endif
