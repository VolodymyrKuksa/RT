/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 12:54:41 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/27 12:54:42 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				nm(t_obj *obj)
{
	float	sum;

	sum = obj->diffuse + obj->specular + obj->refraction;
	obj->diffuse /= sum;
	obj->specular /= sum;
	obj->refraction /= sum;
}

t_gui_obj			*check_menu_collision(int x, int y, t_gui_obj *gui_obj)
{
	t_gui_menu		*my_menu;
	t_gui_obj		*temp;
	int				i;

	temp = NULL;
	if (check_click(x, y, gui_obj))
	{
		my_menu = (t_gui_menu *)gui_obj;
		i = -1;
		if ((temp = my_menu->main_button.collision(x, y,
			(t_gui_obj *)&my_menu->main_button)))
			return (temp);
		while (++i < my_menu->numb_of_control)
			if ((temp = my_menu->controls[i].collision(x, y,
				(t_gui_obj *)&my_menu->controls[i])))
				return (temp);
		i = -1;
		while (++i < my_menu->numb_of_radio)
			if ((temp = my_menu->radio[i].collision(x, y,
				(t_gui_obj *)&my_menu->radio[i])))
				return (temp);
		temp = gui_obj;
	}
	return (temp);
}

void				menu_action(void *some_shit, SDL_Renderer *renderer)
{
	t_gui_menu		*my_menu;

	my_menu = (t_gui_menu *)some_shit;
	my_menu->my_rect.x += my_menu->mouse->dx;
	my_menu->mouse->dx = 0;
	my_menu->my_rect.y += my_menu->mouse->dy;
	my_menu->mouse->dy = 0;
	my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2)
	/ g_win_width;
	my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2)
	/ g_win_height;
	my_menu->update(my_menu, 0, renderer, 0);
}

void				hide_menu(void *some_shit, SDL_Renderer *renderer)
{
	t_gui_menu		*my_menu;

	my_menu = (t_gui_menu *)some_shit;
	my_menu->my_rect.h = 36;
	my_menu->my_rect.w = 120;
	my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2)
	/ g_win_width;
	my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2)
	/ g_win_height;
	my_menu->numb_of_labels = 0;
	my_menu->numb_of_control = 0;
	my_menu->numb_of_radio = 0;
	if (my_menu->m_type == GLOBAL_MENU)
		my_menu->main_button.action = &unhide_global_menu;
	else if (my_menu->m_type == OBJECTS_MENU)
		my_menu->main_button.action = &unhide_objects_menu;
	my_menu->update(my_menu, 1, renderer, 1);
}

void				destroy_menu(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
	int				i;

	SDL_DestroyTexture(my_menu->texture);
	if (my_menu->main_button.action != &hide_menu)
		my_menu->main_button.action(my_menu, renderer);
	i = -1;
	destroy_button(&my_menu->main_button);
	while (++i < my_menu->numb_of_labels)
		destroy_label(&my_menu->labels[i]);
	i = -1;
	while (++i < my_menu->numb_of_control)
		destroy_controller(&my_menu->controls[i]);
	i = -1;
	while (++i < my_menu->numb_of_radio)
		destroy_radio(&my_menu->radio[i]);
	my_menu->numb_of_labels = 0;
	my_menu->numb_of_control = 0;
	my_menu->numb_of_radio = 0;
	free(my_menu->labels);
	free(my_menu->controls);
	free(my_menu->radio);
	free(my_menu->source);
}
