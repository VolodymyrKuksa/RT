/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:24:18 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/30 13:24:19 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

void				save_func(void *some_shit, SDL_Renderer *renderer)
{
	t_scene			*scene;

	scene = (t_scene *)some_shit;
	(void)renderer;
	write_scene(scene);
}

void				print_png(void *some_shit, SDL_Renderer *renderer)
{
	t_env			*env;

	env = (t_env *)some_shit;
	(void)renderer;
	write_png(env);
}

void				create_gui_but(t_gui *my_gui, SDL_Renderer *renderer)
{
	my_gui->button[0] = create_button(init_rect(10, 10, 60, 60),
		NULL, "gui_textures/save.png");
	button_settings(renderer, &my_gui->button[0]);
	button_set_label("", 128, renderer, &my_gui->button[0]);
	my_gui->button[0].action = &save_func;
	my_gui->button[0].type = 2;
	my_gui->button[1] = create_button(init_rect(10, 75, 60, 60),
		NULL, "gui_textures/scrn.png");
	button_settings(renderer, &my_gui->button[1]);
	button_set_label("", 128, renderer, &my_gui->button[1]);
	my_gui->button[1].action = &print_png;
	my_gui->button[1].type = 3;
}

t_gui				init_gui(SDL_Renderer *renderer, t_env *env)
{
	t_gui			my_gui;

	my_gui.numb_of_menus = 2;
	my_gui.numb_of_labels = 0;
	my_gui.numb_of_buttons = 2;
	my_gui.mouse = (t_mouse *)malloc(sizeof(t_mouse));
	my_gui.menu = (t_gui_menu *)malloc(sizeof(t_gui_menu)
		* my_gui.numb_of_menus);
	my_gui.menu[0] = create_menu(75, 10,
		"gui_textures/menu_texture.png", my_gui.mouse);
	menu_settings(&my_gui.menu[0], renderer, GLOBAL_MENU, env);
	my_gui.menu[1] = create_menu(200, 10,
		"gui_textures/menu_texture.png", my_gui.mouse);
	menu_settings(&my_gui.menu[1], renderer, OBJECTS_MENU, env);
	my_gui.label = (t_label *)malloc(sizeof(t_label)
		* my_gui.numb_of_labels);
	my_gui.button = (t_button *)malloc(sizeof(t_button)
		* my_gui.numb_of_buttons);
	create_gui_but(&my_gui, renderer);
	my_gui.draw = &draw_gui;
	my_gui.collision = &check_gui_collision;
	my_gui.update = &update_gui;
	my_gui.duper = &super_duper;
	return (my_gui);
}

void				draw_gui(SDL_Renderer *renderer, t_gui *my_gui)
{
	int				i;

	i = -1;
	while (++i < my_gui->numb_of_menus)
		my_gui->menu[i].draw(renderer, &my_gui->menu[i]);
	i = -1;
	while (++i < my_gui->numb_of_labels)
		my_gui->label[i].draw(renderer, &my_gui->label[i]);
	i = -1;
	while (++i < my_gui->numb_of_buttons)
		my_gui->button[i].draw(renderer, &my_gui->button[i]);
}
