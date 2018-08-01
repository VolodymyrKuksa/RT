/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 22:42:59 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/31 22:42:59 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				super_update(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
	int				i;
	int				flag;

	i = -1;
	flag = 0;
	if (my_menu->main_button.action != &hide_menu)
	{
		my_menu->main_button.action(my_menu, renderer);
		flag = 1;
	}
	while (++i < my_menu->numb_of_control)
		destroy_controller(&my_menu->controls[i]);
	fill_buttons(my_menu, renderer);
	fill_buttons_one(my_menu, renderer);
	if (flag)
		my_menu->main_button.action(my_menu, renderer);
}

void				updater(t_gui_menu *my_menu, char with_text,
						SDL_Renderer *renderer)
{
	int				i;

	i = -1;
	while (++i < my_menu->numb_of_labels)
		my_menu->labels[i].update(&my_menu->labels[i],
		with_text, renderer, 0);
	i = -1;
	while (++i < my_menu->numb_of_control)
		my_menu->controls[i].update(&my_menu->controls[i],
		with_text, renderer, 0);
	i = -1;
	while (++i < my_menu->numb_of_radio)
		my_menu->radio[i].update(&my_menu->radio[i], with_text, renderer);
}

void				update_menu(t_gui_menu *my_menu, char with_text,
						SDL_Renderer *renderer, char hide)
{
	int				help;

	if (with_text)
		menu_own_set(renderer, my_menu);
	my_menu->my_rect.x = my_menu->x * g_win_width
	- (float)my_menu->my_rect.w / 2;
	my_menu->my_rect.y = my_menu->y * g_win_height
	- (float)my_menu->my_rect.h / 2;
	if (!hide)
	{
		help = 0;
		if (my_menu->main_button.action != &hide_menu)
		{
			my_menu->main_button.action(my_menu, renderer);
			help = 1;
		}
		my_menu->main_button.update(&my_menu->main_button,
		with_text, renderer, 0);
		updater(my_menu, with_text, renderer);
		if (help)
			my_menu->main_button.action(my_menu, renderer);
	}
}

void				draw_menu(SDL_Renderer *renderer,
		t_gui_menu *my_menu)
{
	int				i;

	SDL_RenderCopy(renderer, my_menu->texture, NULL, &my_menu->my_rect);
	my_menu->main_button.draw(renderer, &my_menu->main_button);
	i = -1;
	while (++i < my_menu->numb_of_labels)
		my_menu->labels[i].draw(renderer, &my_menu->labels[i]);
	i = -1;
	while (++i < my_menu->numb_of_control)
		my_menu->controls[i].draw(renderer, &my_menu->controls[i]);
	i = -1;
	while (++i < my_menu->numb_of_radio)
		my_menu->radio[i].draw(renderer, &my_menu->radio[i]);
}
