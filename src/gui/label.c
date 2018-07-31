/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 13:50:47 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/25 13:50:47 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				update_texture(SDL_Renderer *renderer, t_label *my_label)
{
	SDL_Surface		*surface;
	SDL_Color		my_color;

	my_color = set_default_text_color();
	surface = TTF_RenderText_Solid(my_label->font, my_label->text, my_color);
	if (my_label->texture)
		SDL_DestroyTexture(my_label->texture);
	my_label->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void				update_label(t_label *my_label, char with_text,
					SDL_Renderer *renderer, char with_alph)
{
	if (with_text || with_alph)
		update_texture(renderer, my_label);
	if (!with_alph || with_text)
	{
		if (my_label->father)
		{
			my_label->dstrect.x = my_label->x + my_label->father->my_rect.x;
			my_label->dstrect.y = my_label->y + my_label->father->my_rect.y;
		}
		else
		{
			my_label->dstrect.x = my_label->x * g_win_width;
			my_label->dstrect.y = my_label->y * g_win_height;
		}
	}
}

void				draw_label(SDL_Renderer *renderer, t_label *label)
{
	SDL_RenderCopy(renderer, label->texture, NULL, &label->dstrect);
}

void				destroy_label(t_label *my_label)
{
	SDL_DestroyTexture(my_label->texture);
	TTF_CloseFont(my_label->font);
	free(my_label->text);
}
