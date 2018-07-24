/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 20:40:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/24 20:40:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	put_error(char *str)
{
	perror(str);
	exit(1);
}

void	set_nonblock(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL, 0);
	flags |= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}

void	set_block(int fd)
{
	int flags;

	flags = fcntl(fd, F_GETFL, 0);
	flags ^= O_NONBLOCK;
	fcntl(fd, F_SETFL, flags);
}
