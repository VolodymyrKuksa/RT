/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 22:42:51 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/31 22:42:52 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				fill_glob_but_2(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
	my_menu->controls[4] = create_controller(init_rect(166, 237, 160, 56),
	(t_gui_obj *)my_menu,
	"gui_textures/Button.png", &my_menu->env->scene.cam.brightness);
	more_controler_settings(&my_menu->controls[4], 10, 0);
	controller_settings(&my_menu->controls[4], renderer, 1);
	my_menu->controls[5] = create_controller(init_rect(166, 321, 160, 56),
	(t_gui_obj *)my_menu,
	"gui_textures/Button.png", &my_menu->env->scene.cam.refr_coef);
	more_controler_settings(&my_menu->controls[5], 2, 1);
	controller_settings(&my_menu->controls[5], renderer, 0.1);
}

void				fill_glob_but(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
	my_menu->controls = (t_val_control *)malloc(sizeof(t_val_control)
	* my_menu->numb_of_control);
	my_menu->controls[0] = create_controller(init_rect(3, 63, 160, 56),
	(t_gui_obj *)my_menu, "gui_textures/Button.png",
	&my_menu->env->scene.cam.filter.x);
	more_controler_settings(&my_menu->controls[0], 1.0, 0.0);
	controller_settings(&my_menu->controls[0], renderer, 0.1);
	my_menu->controls[1] = create_controller(init_rect(166, 63, 160, 56),
	(t_gui_obj *)my_menu,
	"gui_textures/Button.png", &my_menu->env->scene.cam.filter.y);
	more_controler_settings(&my_menu->controls[1], 1.0, 0.0);
	controller_settings(&my_menu->controls[1], renderer, 0.1);
	my_menu->controls[2] = create_controller(init_rect(331, 63, 160, 56),
	(t_gui_obj *)my_menu,
	"gui_textures/Button.png", &my_menu->env->scene.cam.filter.z);
	more_controler_settings(&my_menu->controls[2], 1.0, 0.0);
	controller_settings(&my_menu->controls[2], renderer, 0.1);
	my_menu->controls[3] = create_controller(init_rect(166, 150, 160, 56),
	(t_gui_obj *)my_menu,
	"gui_textures/Button.png", &my_menu->env->scene.cam.dust);
	more_controler_settings(&my_menu->controls[3], 0.1, 0);
	controller_settings(&my_menu->controls[3], renderer, 0.001);
	fill_glob_but_2(my_menu, renderer);
}

void				fill_glob_labels(t_gui_menu *my_menu,
	SDL_Renderer *renderer)
{
	my_menu->labels = (t_label *)malloc(sizeof(t_label)
	* my_menu->numb_of_labels);
	my_menu->labels[0] = create_label(2, 36, "filter_x_y_z",
	(t_gui_obj *)my_menu);
	my_menu->labels[0].width = 115;
	my_menu->labels[0].height = 25;
	label_settings(128, renderer, &my_menu->labels[0], 0);
	my_menu->labels[1] = create_label(2, 122, "dust",
	(t_gui_obj *)my_menu);
	my_menu->labels[1].width = 115;
	my_menu->labels[1].height = 25;
	label_settings(128, renderer, &my_menu->labels[1], 0);
	my_menu->labels[2] = create_label(2, 209, "brightness",
	(t_gui_obj *)my_menu);
	my_menu->labels[2].width = 115;
	my_menu->labels[2].height = 25;
	label_settings(128, renderer, &my_menu->labels[2], 0);
	my_menu->labels[3] = create_label(2, 296, "refr coef",
	(t_gui_obj *)my_menu);
	my_menu->labels[3].width = 115;
	my_menu->labels[3].height = 25;
	label_settings(128, renderer, &my_menu->labels[3], 0);
}

void				fill_global_menu(t_gui_menu *my_menu,
				SDL_Renderer *renderer)
{
	my_menu->main_button = create_button(init_rect(3, 3, 100, 30),
	(t_gui_obj *)my_menu, "gui_textures/Button.png");
	button_settings(renderer, &my_menu->main_button);
	button_set_label("RT menu", 128, renderer, &my_menu->main_button);
	my_menu->main_button.action = &hide_menu;
	my_menu->numb_of_control = 6;
	fill_glob_but(my_menu, renderer);
	my_menu->numb_of_radio = 1;
	my_menu->radio = (t_radio_button *)malloc(sizeof(t_radio_button)
	* my_menu->numb_of_radio);
	my_menu->radio[0] = create_radio(init_rect(32, 400, 430, 150),
	(t_gui_obj *)my_menu,
	"gui_textures/Button.png", &my_menu->env->scene.cam.effect);
	radio_settings(&my_menu->radio[0], renderer, 5, "NO EFFECT",
	"B_N_W", "NEGATIVE", "SEPIA", "KUKSA_PEDR");
	my_menu->numb_of_labels = 4;
	fill_glob_labels(my_menu, renderer);
	my_menu->my_rect.w = 495;
	my_menu->my_rect.h = 600;
	my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2)
	/ g_win_width;
	my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2)
	/ g_win_height;
	menu_own_set(renderer, my_menu);
	hide_menu(my_menu, renderer);
}

void				we_control(t_gui_obj *gui_obj,
			SDL_Renderer *renderer)
{
	t_gui_menu		*my_menu;
	int				i;

	my_menu = (t_gui_menu *)gui_obj;
	if (my_menu->m_type == OBJECTS_MENU)
	{
		my_menu->env->num_samples = 0;
		nm(&my_menu->env->scene.obj[my_menu->env->scene.last_obj]);
		i = -1;
		while (++i < my_menu->numb_of_control)
			my_menu->controls[i].update(&my_menu->controls[i], 0, renderer, 1);
		write_scene_to_kernel(my_menu->env);
	}
	else if (my_menu->m_type == GLOBAL_MENU)
	{
		my_menu->env->num_samples = 0;
		clSetKernelArg(my_menu->env->cl.kernel, 3,
		sizeof(my_menu->env->scene.cam), &my_menu->env->scene.cam);
	}
}
