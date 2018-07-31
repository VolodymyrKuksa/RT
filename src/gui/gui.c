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

void                save_func(void *some_shit, SDL_Renderer *renderer)
{
    t_scene         *scene;

    scene = (t_scene *)some_shit;
	(void)renderer;
    write_scene(scene);
}

t_gui               init_gui(SDL_Renderer *renderer, t_scene *scene)
{
    t_gui           my_gui;

    my_gui.numb_of_menus = 2;
    my_gui.numb_of_labels = 0;
    my_gui.numb_of_buttons = 1;
    my_gui.mouse = (t_mouse *)malloc(sizeof(t_mouse));
    /* menu */
    my_gui.menu = (t_gui_menu *)malloc(sizeof(t_gui_menu) * my_gui.numb_of_menus);
    my_gui.menu[0] = create_menu(100, 200, "gui_textures/kuksa_pidor.jpg", my_gui.mouse);
    menu_settings(&my_gui.menu[0], renderer, GLOBAL_MENU, scene);
    my_gui.menu[1] = create_menu(400, 200, "gui_textures/kuksa_pidor.jpg", my_gui.mouse);
    menu_settings(&my_gui.menu[1], renderer, OBJECTS_MENU, scene);
    /* menu */
    /* labels */
    my_gui.label = (t_label *)malloc(sizeof(t_label) * my_gui.numb_of_labels);
    /* labels */
    /* buttons */
    my_gui.button = (t_button *)malloc(sizeof(t_button) * my_gui.numb_of_buttons);
    my_gui.button[0] = create_button(init_rect(10, 10, 60, 60), NULL, "gui_textures/save.png");
    button_settings(renderer, &my_gui.button[0]);
    button_set_label("", 128, renderer, &my_gui.button[0]);
    my_gui.button[0].action = &save_func;
    my_gui.button[0].type = 2;
    /* buttons */
    my_gui.draw = &draw_gui;
    my_gui.collision = &check_gui_collision;
    my_gui.update = &update_gui;
    my_gui.duper = &super_duper;
    return (my_gui);
}

void                draw_gui(SDL_Renderer *renderer, t_gui *my_gui)
{
    int             i;

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

t_gui_obj           *check_gui_collision(int x, int y, t_gui_obj *gui_obj)
{
    t_gui           *my_gui;
    t_gui_obj       *temp;
    int             i;

    my_gui = (t_gui *)gui_obj;
    temp = NULL;
    i = -1;
    while (++i < my_gui->numb_of_menus)
    {
        if ((temp = my_gui->menu[i].collision(x, y, (t_gui_obj *)&my_gui->menu[i])))
            return (temp);
    }
    i = -1;
    while (++i < my_gui->numb_of_buttons)
    {
        if ((temp = my_gui->button[i].collision(x, y, (t_gui_obj *)&my_gui->button[i])))
            return (temp);
    }
    return (temp);
}

void                super_duper(t_gui *my_gui, SDL_Renderer *renderer)
{
    super_update(&my_gui->menu[1], renderer);
}

void                update_gui(t_gui *my_gui, SDL_Renderer *renderer)
{
    int             i;

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

void                destroy_gui(t_gui *my_gui, SDL_Renderer *renderer)
{
    int             i;

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