/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compress_texture.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:25:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/10 17:25:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt_types.h>

extern t_txlst		*g_txlst;
extern unsigned int	g_tx_count;

int			fill_txdata(t_txdata *txdata)
{
	int				i;
	unsigned int	start;
	t_txlst			*tmp;

	tmp = g_txlst;
	start = 0;
	i = -1;
	while (++i < g_tx_count)
	{
		if (!tmp)
			return (-1);
		txdata[i].height = (unsigned int)tmp->surf->h;
		txdata[i].width = (unsigned int)tmp->surf->w;
		txdata[i].start = start;
		start += txdata[i].width * txdata[i].height;
		tmp = tmp->next;
	}
	return (start);
}

void		write_tx(t_rgb *tx, SDL_Surface *surf)
{
	int		i;
	int		j;

	i = -1;
	while (++i < surf->h)
	{
		j = -1;
		while (++j < surf->w)
			tx[i * surf->w + j].c =
				((unsigned int *)surf->pixels)[i * surf->w + j];
	}
}

int			fill_tx(t_txgpu *txgpu)
{
	unsigned int	i;
	t_txlst			*tmp;

	tmp = g_txlst;
	i = (unsigned int)(-1);
	while (++i < g_tx_count)
	{
		if (!tmp)
			return (-1);
		write_tx(txgpu->tx + txgpu->txdata[i].start, tmp->surf);
		tmp = tmp->next;
	}
	return (1);
}

/*
**	compress_texture:
**		Files t_txgpu structure;
**		Writes all textures as an array of cl_float3 to t_txgpu.tx;
**		Writes info about all textures as an array of t_txdata to
**		t_txgpu.txdata;
**		t_xdata structure includes width, height and index of the first pixel
**		of texture in the t_txgpu.tx array
*/

int			compress_texture(t_txgpu *txg)
{
	txg->tx = NULL;
	txg->txdata = NULL;
	txg->total_size = 0;
	if (!(txg->tx_count = g_tx_count))
		return (-1);
	if (!(txg->txdata = (t_txdata*)malloc(sizeof(t_txdata) * txg->tx_count)))
		return (-1);
	if ((txg->total_size = fill_txdata(txg->txdata)) < 0)
	{
		free(txg->txdata);
		return (-1);
	}
	if (!(txg->tx = (t_rgb*)malloc(sizeof(t_rgb) * txg->total_size)))
	{
		free(txg->txdata);
		return (-1);
	}
	if (fill_tx(txg) != 1)
	{
		free(txg->txdata);
		free(txg->tx);
		return (-1);
	}
	return (1);
}

void		free_txlst(void)
{
	t_txlst		*tmp;
	t_txlst		*tmp1;

	tmp = g_txlst;
	while (tmp)
	{
		SDL_FreeSurface(tmp->surf);
		free(tmp->filename);
		tmp1 = tmp;
		tmp = tmp->next;
		free(tmp1);
	}
}
