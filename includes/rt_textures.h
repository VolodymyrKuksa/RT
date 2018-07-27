/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_textures.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 15:29:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/10 15:29:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_TEXTURES_H
# define RT_TEXTURES_H

# include <OpenCL/opencl.h>
# include <SDL.h>
# include <SDL_image.h>
# include "libft.h"

typedef union		u_rgb
{
	unsigned int	c;
	unsigned char	bgra[4];
}					t_rgb;

typedef struct		s_txlst
{
	SDL_Surface		*surf;
	char			*filename;
	int				id;
	struct s_txlst	*next;
}					t_txlst;

typedef struct		s_txdata
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	start;
}					t_txdata;

typedef struct		s_txgpu
{
	t_txdata		*txdata;
	t_rgb			*tx;
	int				tx_count;
	int				total_size;
}					t_txgpu;

/*
**	load_texture.c
*/

int					load_texture(char *filename);
SDL_Surface			*get_texture(int id);
char				*get_texture_name(int id);

/*
**	compress_texture.c
*/

int					compress_texture(t_txgpu *txg);
void				free_txlst(void);

#endif
