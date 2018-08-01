/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 11:59:12 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/26 11:59:13 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void			update_button(t_button *my_button, char with_text,
				SDL_Renderer *renderer, char with_alph)
{
	if (with_text)
		button_settings(renderer, my_button);
	if (!with_alph || with_text)
	{
		if (my_button->father)
		{
			my_button->my_rect.x = my_button->x + my_button->father->my_rect.x;
			my_button->my_rect.y = my_button->y + my_button->father->my_rect.y;
		}
		else
		{
			my_button->my_rect.x = my_button->x * g_win_width
					- (float)my_button->my_rect.w / 2;
			my_button->my_rect.y = my_button->y * g_win_height
					- (float)my_button->my_rect.h / 2;
		}
	}
	my_button->name.update(&my_button->name, with_text, renderer, with_alph);
}

void			draw_button(SDL_Renderer *renderer, t_button *my_button)
{
	SDL_RenderCopy(renderer, my_button->texture, NULL, &my_button->my_rect);
	my_button->name.draw(renderer, &(my_button->name));
}

t_gui_obj		*check_button_collision(int x, int y, t_gui_obj *gui_obj)
{
	if (check_click(x, y, gui_obj))
		return (gui_obj);
	return (NULL);
}

void			destroy_button(t_button *my_button)
{
	SDL_DestroyTexture(my_button->texture);
	destroy_label(&my_button->name);
	free(my_button->source);
}
