/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 21:02:43 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/31 21:02:50 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

t_gui_obj			*check_gui_collision(int x, int y, t_gui_obj *gui_obj)
{
	t_gui			*my_gui;
	t_gui_obj		*temp;
	int				i;

	my_gui = (t_gui *)gui_obj;
	temp = NULL;
	i = my_gui->numb_of_buttons;
	while (--i >= 0)
	{
		if ((temp = my_gui->button[i].collision(x, y,
				(t_gui_obj *)&my_gui->button[i])))
			return (temp);
	}
	i = my_gui->numb_of_menus;
	while (--i >= 0)
	{
		if ((temp = my_gui->menu[i].collision(x, y,
				(t_gui_obj *)&my_gui->menu[i])))
			return (temp);
	}
	return (temp);
}

void				super_duper(t_gui *my_gui, SDL_Renderer *renderer)
{
	super_update(&my_gui->menu[1], renderer);
}

void				update_gui(t_gui *my_gui, SDL_Renderer *renderer)
{
	int				i;

	i = -1;
	while (++i < my_gui->numb_of_menus)
		my_gui->menu[i].update(&my_gui->menu[i], 1, renderer, 0);
	i = -1;
	while (++i < my_gui->numb_of_labels)
		my_gui->label[i].update(&my_gui->label[i], 1, renderer, 0);
	i = -1;
	while (++i < my_gui->numb_of_buttons)
		my_gui->button[i].update(&my_gui->button[i], 1, renderer, 0);
}

void				destroy_gui(t_gui *my_gui, SDL_Renderer *renderer)
{
	int				i;

	i = -1;
	while (++i < my_gui->numb_of_menus)
		destroy_menu(&my_gui->menu[i], renderer);
	i = -1;
	while (++i < my_gui->numb_of_labels)
		destroy_label(&my_gui->label[i]);
	i = -1;
	while (++i < my_gui->numb_of_buttons)
		destroy_button(&my_gui->button[i]);
}
