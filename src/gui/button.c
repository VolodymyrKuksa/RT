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

t_button		create_button(SDL_Rect my_rect, t_gui_obj *father, char *text) //не трогать
{
	t_button	my_button;

	my_button.my_rect = my_rect;
	if (father)
	{
		my_button.x = my_rect.x;
		my_button.y = my_rect.y;
		my_button.my_rect.x = my_button.x + father->my_rect.x;
		my_button.my_rect.y = my_button.y + father->my_rect.y;
	} else {
		my_button.x = (float)(my_rect.x + (float)my_rect.w / 2) / g_win_width;
		my_button.y = (float)(my_rect.y + (float)my_rect.h / 2) / g_win_height;
	}
	my_button.father = father;
	my_button.texture = NULL;
	my_button.source = (char *)malloc(sizeof(char) * ft_strlen(text));
	my_button.source = ft_strcpy(my_button.source, text);
	my_button.type = 0;
	my_button.draw = &draw_button;
	my_button.update = &update_button;
	my_button.collision = &check_button_collision;
	return (my_button);
}

void			button_settings(SDL_Renderer *renderer, t_button *my_button) //не трогать
{
	SDL_Surface *surface;

	surface = IMG_Load(my_button->source);
	SDL_SetColorKey(surface, SDL_TRUE,
		SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	if (my_button->texture)
		SDL_DestroyTexture(my_button->texture);
	my_button->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void			button_set_label(char *text, int font_size,
								SDL_Renderer *renderer, t_button *my_button) //трогать только с Димкой
{
	my_button->name = create_label(1 + my_button->my_rect.w * 0.2,
		1 + my_button->my_rect.h * 0.1, text, (t_gui_obj *)my_button);
	my_button->name.width = my_button->my_rect.w - my_button->my_rect.w * 0.4;
	my_button->name.height = my_button->my_rect.h - my_button->my_rect.h * 0.2;
	label_settings(font_size, renderer, &my_button->name, 0);
}

void			update_button(t_button *my_button, char with_text,
				SDL_Renderer *renderer, char with_alph) //не трогать
{
	if (with_text)
		button_settings(renderer, my_button);
	if (!with_alph || with_text)
	{
		if (my_button->father)
		{
			my_button->my_rect.x = my_button->x + my_button->father->my_rect.x;
			my_button->my_rect.y = my_button->y + my_button->father->my_rect.y;
		} else {
			my_button->my_rect.x = my_button->x * g_win_width
					- (float)my_button->my_rect.w / 2;
			my_button->my_rect.y = my_button->y * g_win_height
					- (float)my_button->my_rect.h / 2;
		}
	}
	my_button->name.update(&my_button->name, with_text, renderer, with_alph);
}

void			draw_button(SDL_Renderer *renderer, t_button *my_button) //не трогать
{
	SDL_RenderCopy(renderer, my_button->texture, NULL, &my_button->my_rect);
	my_button->name.draw(renderer, &(my_button->name));
}

t_gui_obj		*check_button_collision(int x, int y, t_gui_obj *gui_obj) //не трогать
{
	if (check_click(x, y, gui_obj))
		return(gui_obj);
	return (NULL);
}

void			destroy_button(t_button *my_button) //не трогать
{
	SDL_DestroyTexture(my_button->texture);
	destroy_label(&my_button->name);
	free(my_button->source);
}
