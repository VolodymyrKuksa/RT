/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:14:39 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/27 16:14:39 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				draw_controler(SDL_Renderer *renderer,
					t_val_control *my_control)
{
	SDL_RenderCopy(renderer, my_control->texture,
		NULL, &my_control->my_rect);
	my_control->change_buttons[0].draw(renderer,
		&my_control->change_buttons[0]);
	my_control->change_buttons[1].draw(renderer,
		&my_control->change_buttons[1]);
	my_control->output.draw(renderer, &my_control->output);
}

t_gui_obj			*check_contol_collision(int x, int y, t_gui_obj *gui_obj)
{
	t_val_control	*my_control;
	t_gui_obj		*temp;

	temp = NULL;
	if (check_click(x, y, gui_obj))
	{
		my_control = (t_val_control *)gui_obj;
		if ((temp = my_control->change_buttons[0].collision(x,
				y, (t_gui_obj *)&my_control->change_buttons[0])))
			return (temp);
		if ((temp = my_control->change_buttons[1].collision(x,
				y, (t_gui_obj *)&my_control->change_buttons[1])))
			return (temp);
	}
	return (temp);
}

void				plus_action(void *some_shit, SDL_Renderer *renderer)
{
	t_val_control	*my_control;
	char			*accur;
	char			str[10];

	my_control = (t_val_control *)some_shit;
	if (*(my_control->value) + 0.0001 < my_control->max_val)
	{
		*(my_control->value) += my_control->step;
		if (*(my_control->value) > my_control->max_val)
			*(my_control->value) = my_control->max_val;
		sprintf(str, "%f", *(my_control->value));
		accur = ft_strchr(str, '.');
		accur += 4;
		*accur = '\0';
		my_control->output.text = ft_strcpy(my_control->output.text, str);
		my_control->update(my_control, 0, renderer, 1);
	}
}

void				minus_action(void *some_shit, SDL_Renderer *renderer)
{
	t_val_control	*my_control;
	char			*accur;
	char			str[10];

	my_control = (t_val_control *)some_shit;
	if (*(my_control->value) - 0.0001 > my_control->min_val)
	{
		*(my_control->value) -= my_control->step;
		if (*(my_control->value) < my_control->min_val)
			*(my_control->value) = my_control->min_val;
		sprintf(str, "%f", *(my_control->value));
		accur = ft_strchr(str, '.');
		accur += 4;
		*accur = '\0';
		my_control->output.text = ft_strcpy(my_control->output.text, str);
		my_control->update(my_control, 0, renderer, 1);
	}
}

void				destroy_controller(t_val_control *my_control)
{
	SDL_DestroyTexture(my_control->texture);
	destroy_label(&my_control->output);
	destroy_button(&my_control->change_buttons[0]);
	destroy_button(&my_control->change_buttons[1]);
	free(my_control->source);
}
