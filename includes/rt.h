/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 18:47:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/22 18:47:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <OpenCL/opencl.h>
# include "libft.h"
# include "get_next_line.h"
# include "rt_types.h"

/*
**	returns a string with file content and writes it`s in the size variable
**	returns NULL and writes 0 to size in case of an error
*/

char	*read_file(const char *filename, size_t *size);

#endif
