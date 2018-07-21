/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afedun <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 13:07:40 by afedun            #+#    #+#             */
/*   Updated: 2018/07/18 13:07:42 by afedun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"

void		error_fedun(char *er)
{
	ft_putendl(er);
	system("leaks -q RT");
	exit(-1);
}

void		parse_scene(int argc, char **argv, char **contents, size_t *len)
{
	int			fd;

	if (argc != 2)
		error_fedun("second arg must be file");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_fedun("Unable to open file");
	*contents = read_file(fd, len);
	if (*contents == NULL)
		error_fedun("Cant read file");
	printf("--------------------------------\n\n");
}

char		*read_file(int fd, size_t *size)
{
	char	*tmp;
	char	*res;
	ssize_t	num;
	char	buf[256];

	res = (char *)malloc(sizeof(char));
	res[0] = '\0';
	if (res < 0)
		return (NULL);
	while ((num = read(fd, buf, 255)) > 0)
	{
		buf[num] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
	}
	if (size)
		*size = ft_strlen(res);
	return (res);
}
