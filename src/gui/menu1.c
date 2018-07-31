/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 22:42:48 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/31 22:42:48 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

t_gui_menu			create_menu(int x, int y, char *text, t_mouse *mouse)
{
	t_gui_menu		my_menu;

	my_menu.my_rect.x = x;
	my_menu.my_rect.y = y;
	my_menu.texture = NULL;
	my_menu.source = (char *)malloc(sizeof(char) * ft_strlen(text));
	my_menu.source = ft_strcpy(my_menu.source, text);
	my_menu.father = NULL;
	my_menu.type = 1;
	my_menu.mouse = mouse;
	my_menu.draw = &draw_menu;
	my_menu.update = &update_menu;
	my_menu.collision = &check_menu_collision;
	my_menu.action = &menu_action;
	return (my_menu);
}

void				menu_own_set(SDL_Renderer *renderer, t_gui_menu *my_menu)
{
	SDL_Surface		*surface;

	surface = IMG_Load(my_menu->source);
	SDL_SetColorKey(surface, SDL_TRUE,
	SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	if (my_menu->texture)
		SDL_DestroyTexture(my_menu->texture);
	my_menu->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void				menu_settings(t_gui_menu *my_menu, SDL_Renderer *renderer,
									menu_type type, t_env *env)
{
	my_menu->env = env;
	my_menu->m_type = type;
	if (type == GLOBAL_MENU)
		fill_global_menu(my_menu, renderer);
	else if (type == OBJECTS_MENU)
		fill_objects_menu(my_menu, renderer);
}

void				unhide_global_menu(void *some_shit, SDL_Renderer *renderer)
{
	t_gui_menu		*my_menu;

	my_menu = (t_gui_menu *)some_shit;
	my_menu->numb_of_control = 6;
	my_menu->numb_of_labels = 4;
	my_menu->numb_of_radio = 1;
	my_menu->my_rect.w = 495;
	my_menu->my_rect.h = 600;
	my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2)
	/ g_win_width;
	my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2)
	/ g_win_height;
	my_menu->main_button.action = &hide_menu;
	my_menu->update(my_menu, 1, renderer, 1);
}

void				unhide_objects_menu(void *some_shit, SDL_Renderer *renderer)
{
	t_gui_menu		*my_menu;

	my_menu = (t_gui_menu *)some_shit;
	my_menu->numb_of_control = 10;
	my_menu->numb_of_labels = 4;
	my_menu->numb_of_radio = 0;
	my_menu->my_rect.w = 495;
	my_menu->my_rect.h = 500;
	my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2)
	/ g_win_width;
	my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2)
	/ g_win_height;
	my_menu->main_button.action = &hide_menu;
	my_menu->update(my_menu, 1, renderer, 1);
}
