/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 13:26:57 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/28 13:26:59 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void					radio_kek(t_radio_button *my_radio)
{
	*(my_radio->pointer) = create_label(my_radio->buttons[*(my_radio->value)].x
	+ my_radio->buttons[*(my_radio->value)].my_rect.w / 2
	- my_radio->pointer->width / 2, my_radio->buttons[*(my_radio->value)].y +
	my_radio->buttons[*(my_radio->value)].my_rect.h, "^",
	(t_gui_obj *)my_radio);
}

void					draw_radio(SDL_Renderer *renderer,
						t_radio_button *my_radio)
{
	int					i;

	SDL_RenderCopy(renderer, my_radio->texture, NULL, &my_radio->my_rect);
	i = -1;
	while (++i < my_radio->num_of_buttons)
		my_radio->buttons[i].draw(renderer, &my_radio->buttons[i]);
	my_radio->pointer->draw(renderer, my_radio->pointer);
}

t_gui_obj				*check_radio_collision(int x, int y, t_gui_obj *gui_obj)
{
	t_radio_button		*my_radio;
	t_gui_obj			*temp;
	int					i;

	temp = NULL;
	if (check_click(x, y, gui_obj))
	{
		i = -1;
		my_radio = (t_radio_button *)gui_obj;
		while (++i < my_radio->num_of_buttons)
		{
			if ((temp = my_radio->buttons[i].collision(x, y,
					(t_gui_obj *)&my_radio->buttons[i])))
			{
				my_radio->last_pressed = i;
				return (temp);
			}
		}
	}
	return (temp);
}

void					radio_action(void *some_shit, SDL_Renderer *renderer)
{
	t_radio_button		*my_radio;

	my_radio = (t_radio_button *)some_shit;
	*(my_radio->value) = my_radio->last_pressed;
	my_radio->pointer->x = my_radio->buttons[my_radio->last_pressed].x +
			my_radio->buttons[my_radio->last_pressed].my_rect.w / 2 -
			my_radio->pointer->width / 2;
	my_radio->pointer->y = my_radio->buttons[my_radio->last_pressed].y +
			my_radio->buttons[my_radio->last_pressed].my_rect.h;
	my_radio->pointer->update(my_radio->pointer, 0, renderer, 0);
}

void					destroy_radio(t_radio_button *my_radio)
{
	int					i;

	SDL_DestroyTexture(my_radio->texture);
	destroy_label(my_radio->pointer);
	i = -1;
	while (++i < my_radio->num_of_buttons)
		destroy_button(&my_radio->buttons[i]);
	free(my_radio->buttons);
	free(my_radio->source);
	free(my_radio->pointer);
}
