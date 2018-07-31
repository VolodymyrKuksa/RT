/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 22:42:55 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/31 22:42:55 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				fill_buttons(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
	my_menu->controls[0] = create_controller(init_rect(3, 63, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].color.x);
	more_controler_settings(&my_menu->controls[0], 1.0, 0.0);
	controller_settings(&my_menu->controls[0], renderer, 0.1);
	my_menu->controls[1] = create_controller(init_rect(166, 63, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].color.y);
	more_controler_settings(&my_menu->controls[1], 1.0, 0.0);
	controller_settings(&my_menu->controls[1], renderer, 0.1);
	my_menu->controls[2] = create_controller(init_rect(331, 63, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].color.z);
	more_controler_settings(&my_menu->controls[2], 1.0, 0.0);
	controller_settings(&my_menu->controls[2], renderer, 0.1);
	my_menu->controls[3] = create_controller(init_rect(3, 150, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].emission.x);
	more_controler_settings(&my_menu->controls[3], 100.0, 0.0);
	controller_settings(&my_menu->controls[3], renderer, 1.0);
	my_menu->controls[4] = create_controller(init_rect(166, 150, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].emission.y);
	more_controler_settings(&my_menu->controls[4], 100.0, 0.0);
	controller_settings(&my_menu->controls[4], renderer, 1.0);
}

void				fill_buttons_one(t_gui_menu *my_menu,
				SDL_Renderer *renderer)
{
	my_menu->controls[5] = create_controller(init_rect(331, 150, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].emission.z);
	more_controler_settings(&my_menu->controls[5], 100.0, 0.0);
	controller_settings(&my_menu->controls[5], renderer, 1.0);
	my_menu->controls[6] = create_controller(init_rect(166, 237, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].roughness);
	more_controler_settings(&my_menu->controls[6], 1, 0);
	controller_settings(&my_menu->controls[6], renderer, 0.01);
	my_menu->controls[7] = create_controller(init_rect(3, 321, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].diffuse);
	more_controler_settings(&my_menu->controls[7], 1.0, 0.0);
	controller_settings(&my_menu->controls[7], renderer, 0.1);
	my_menu->controls[8] = create_controller(init_rect(166, 321, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].specular);
	more_controler_settings(&my_menu->controls[8], 1.0, 0.0);
	controller_settings(&my_menu->controls[8], renderer, 0.1);
	my_menu->controls[9] = create_controller(init_rect(331, 321, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.obj[my_menu->env->scene.last_obj].refraction);
	more_controler_settings(&my_menu->controls[9], 1.0, 0.0);
	controller_settings(&my_menu->controls[9], renderer, 0.1);
}

void				fill_labels(t_gui_menu *my_menu,
			SDL_Renderer *renderer)
{
	my_menu->labels = (t_label *)malloc(sizeof(t_label)
	* my_menu->numb_of_labels);
	my_menu->labels[0] = create_label(2, 36, "color_r_g_b",
	(t_gui_obj *)my_menu);
	my_menu->labels[0].width = 115;
	my_menu->labels[0].height = 25;
	label_settings(128, renderer, &my_menu->labels[0], 0);
	my_menu->labels[1] = create_label(2, 122, "emission_x_y_z",
	(t_gui_obj *)my_menu);
	my_menu->labels[1].width = 115;
	my_menu->labels[1].height = 25;
	label_settings(128, renderer, &my_menu->labels[1], 0);
	my_menu->labels[2] = create_label(2, 209, "roughness",
	(t_gui_obj *)my_menu);
	my_menu->labels[2].width = 115;
	my_menu->labels[2].height = 25;
	label_settings(128, renderer, &my_menu->labels[2], 0);
	my_menu->labels[3] = create_label(2, 296, "def spec refr",
	(t_gui_obj *)my_menu);
	my_menu->labels[3].width = 115;
	my_menu->labels[3].height = 25;
	label_settings(128, renderer, &my_menu->labels[3], 0);
	my_menu->numb_of_radio = 0;
	my_menu->my_rect.w = 495;
	my_menu->my_rect.h = 500;
}

void				fill_objects_menu(t_gui_menu *my_menu,
	SDL_Renderer *renderer)
{
	my_menu->main_button = create_button(init_rect(3, 3, 100, 30),
	(t_gui_obj *)my_menu, "gui_textures/Button.png");
	button_settings(renderer, &my_menu->main_button);
	button_set_label("Objs menu", 128, renderer, &my_menu->main_button);
	my_menu->main_button.action = &hide_menu;
	my_menu->numb_of_control = 10;
	my_menu->controls = (t_val_control *)malloc(sizeof(t_val_control)
	* my_menu->numb_of_control);
	fill_buttons(my_menu, renderer);
	fill_buttons_one(my_menu, renderer);
	my_menu->numb_of_labels = 4;
	fill_labels(my_menu, renderer);
	my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2)
	/ g_win_width;
	my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2)
	/ g_win_height;
	menu_own_set(renderer, my_menu);
	hide_menu(my_menu, renderer);
}
