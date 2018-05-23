/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 16:18:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/23 16:18:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	join_lines(char **res, char **line)
{
	char	*tmp;

	if (!*res)
	{
		*res = *line;
		return ;
	}
	tmp = *res;
	*res = ft_strjoin(*res, "\n");
	free(tmp);
	tmp = *res;
	*res = ft_strjoin(*res, *line);
	free(tmp);
	free(*line);
}

/*
**	DEBUG (add before `return (res);`):
**	system("leaks -q RT");
*/

char		*read_file(const char *filename, size_t *size)
{
	int		fd;
	int		gnlret;
	char	*res;
	char	*line;

	res = NULL;
	fd = open(filename, O_RDONLY);
	gnlret = get_next_line(fd, &line);
	while (gnlret > 0)
	{
		if (gnlret < 0)
		{
			free(res);
			*size = 0;
			return (NULL);
		}
		join_lines(&res, &line);
		gnlret = get_next_line(fd, &line);
	}
	*size = ft_strlen(res);
	return (res);
}
