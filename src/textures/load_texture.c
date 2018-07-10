/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 14:52:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/10 14:52:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_textures.h"

t_txlst			*g_txlst = NULL;
unsigned int	g_tx_count = 0;

t_txlst			*new_txlst_node(SDL_Surface *surf, char *filename, int id)
{
	t_txlst	*new;

	if (!(new = (t_txlst*)malloc(sizeof(t_txlst))))
		return (NULL);
	new->surf = surf;
	if (!(new->filename = ft_strdup(filename)))
	{
		free(new);
		return (NULL);
	}
	new->id = id;
	new->next = NULL;
	return (new);
}

int				add_to_txlst(char *filename, t_txlst **ptr)
{
	SDL_Surface		*surf;

	if (!(surf = IMG_Load(filename)))
		return (-1);
	if (!(*ptr = new_txlst_node(surf, filename, g_tx_count)))
	{
		SDL_FreeSurface(surf);
		surf = NULL;
		return (-1);
	}
	++g_tx_count;
	return ((*ptr)->id);
}

/*
**	load_texture:
**		Loads texture from file if it has not been loaded yet
**		and returns it`s identifier.
**		If the texture has already been loaded -> returns the correct
**		identifier of the texture.
*/

int				load_texture(char *filename)
{
	t_txlst		*tmp;

	if (!g_txlst)
		return (add_to_txlst(filename, &g_txlst));
	tmp = g_txlst;
	while (tmp->next && !ft_strequ(tmp->filename, filename))
		tmp = tmp->next;
	if (ft_strequ(tmp->filename, filename))
		return (tmp->id);
	return (add_to_txlst(filename, &tmp->next));
}

SDL_Surface		*get_texture(int id)
{
	t_txlst	*tmp;

	if (id < 0 || id >= g_tx_count)
		return (NULL);
	tmp = g_txlst;
	while (tmp && tmp->id != id)
		tmp = tmp->next;
	if (tmp)
		return (tmp->surf);
	return (NULL);
}

void			print_txtlst(void)		//USES PRINTF (FOR DEBUG)
{
	t_txlst		*tmp;

	tmp = g_txlst;
	printf("g_txlst:\n>>>>>-----<<<<<\n");
	while (tmp)
	{
		printf("filename: %s\nid: %d\n>>>>>-----<<<<<\n",
			tmp->filename, tmp->id);
		tmp = tmp->next;
	}
}
