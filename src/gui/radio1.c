/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 23:01:23 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/31 23:01:24 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

t_radio_button			create_radio(SDL_Rect my_rect,
						t_gui_obj *father, char *text, int *value)
{
	t_radio_button		my_radio;

	my_radio.my_rect = my_rect;
	my_radio.x = my_rect.x;
	my_radio.y = my_rect.y;
	my_radio.my_rect.x = my_radio.x + father->my_rect.x;
	my_radio.my_rect.y = my_radio.y + father->my_rect.y;
	my_radio.father = father;
	my_radio.texture = NULL;
	my_radio.source = (char *)malloc(sizeof(char) * ft_strlen(text));
	my_radio.source = ft_strcpy(my_radio.source, text);
	my_radio.value = value;
	my_radio.last_pressed = 0;
	my_radio.draw = &draw_radio;
	my_radio.update = &update_radio;
	my_radio.collision = &check_radio_collision;
	return (my_radio);
}

void					radio_own_set(SDL_Renderer *renderer,
	t_radio_button *my_radio)
{
	SDL_Surface			*surface;

	surface = IMG_Load(my_radio->source);
	SDL_SetColorKey(surface, SDL_TRUE,
				SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	if (my_radio->texture)
		SDL_DestroyTexture(my_radio->texture);
	my_radio->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void					radio_settings(t_radio_button *my_radio,
						SDL_Renderer *renderer, int number, ...)
{
	va_list				list;
	int					i;

	radio_own_set(renderer, my_radio);
	my_radio->num_of_buttons = number;
	my_radio->buttons = (t_button *)malloc(sizeof(t_button)
				* my_radio->num_of_buttons);
	i = -1;
	va_start(list, number);
	while (++i < my_radio->num_of_buttons)
	{
		my_radio->buttons[i] = create_button(init_rect(10 + (i % 4) * 104,
		8 + (i / 4) * 70, 100, 50), (t_gui_obj *)my_radio,
		"gui_textures/Button.png");
		button_settings(renderer, &my_radio->buttons[i]);
		button_set_label(va_arg(list, char *), 128,
		renderer, &my_radio->buttons[i]);
		my_radio->buttons[i].action = &radio_action;
	}
	va_end(list);
	my_radio->pointer = (t_label *)malloc(sizeof(t_label));
	radio_kek(my_radio);
	my_radio->pointer->width = 20;
	my_radio->pointer->height = 20;
	label_settings(128, renderer, my_radio->pointer, 0);
}

void					update_radio(t_radio_button *my_radio,
				char with_text, SDL_Renderer *renderer)
{
	int					i;

	if (with_text)
		radio_own_set(renderer, my_radio);
	my_radio->my_rect.x = my_radio->x + my_radio->father->my_rect.x;
	my_radio->my_rect.y = my_radio->y + my_radio->father->my_rect.y;
	i = -1;
	while (++i < my_radio->num_of_buttons)
		my_radio->buttons[i].update(&my_radio->buttons[i],
				with_text, renderer, 0);
	my_radio->pointer->update(my_radio->pointer, with_text, renderer, 0);
}
