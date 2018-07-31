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

#include "rt_types.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

t_gui_menu          create_menu(int x, int y, char *text, t_mouse *mouse) //не трогать
{
    t_gui_menu      my_menu;

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

void                menu_own_set(SDL_Renderer *renderer, t_gui_menu *my_menu) //не трогать
{
    SDL_Surface     *surface;

    surface = IMG_Load(my_menu->source);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF));
    if (my_menu->texture)
        SDL_DestroyTexture(my_menu->texture);
    my_menu->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void               menu_settings(t_gui_menu *my_menu, SDL_Renderer *renderer, menu_type type, t_scene *scene) //не трогать
{
    my_menu->scene = scene;
    my_menu->m_type = type;
    if (type == GLOBAL_MENU)
        fill_global_menu(my_menu, renderer);
    else if (type == OBJECTS_MENU)
        fill_objects_menu(my_menu, renderer);
}

void                unhide_global_menu(void *some_shit, SDL_Renderer *renderer) //подстроить под меню всего
{
    t_gui_menu      *my_menu;

    my_menu = (t_gui_menu *)some_shit;
    /*        изменяемая часть       */
    my_menu->numb_of_control = 6;
    my_menu->numb_of_labels = 4;
    my_menu->numb_of_radio = 1;
    my_menu->my_rect.w = 495;
    my_menu->my_rect.h = 600;
    /*                              */
    my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2) / g_win_width;
    my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2) / g_win_height;
    my_menu->main_button.action = &hide_menu;
    my_menu->update(my_menu, 1, renderer, 1);
}

void                unhide_objects_menu(void *some_shit, SDL_Renderer *renderer) //подстроить под меню объектов
{
    t_gui_menu      *my_menu;

    my_menu = (t_gui_menu *)some_shit;
    /*        изменяемая часть       */
    my_menu->numb_of_control = 7;
    my_menu->numb_of_labels = 3;
    my_menu->numb_of_radio = 0;
    my_menu->my_rect.w = 495;
    my_menu->my_rect.h = 500;
    /*                              */
    my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2) / g_win_width;
    my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2) / g_win_height;
    my_menu->main_button.action = &hide_menu;
    my_menu->update(my_menu, 1, renderer, 1);
    return ; //fill
}

void                fill_global_menu(t_gui_menu *my_menu, SDL_Renderer *renderer) //заполняем меню всего
{
    /* обязательная часть */
    my_menu->main_button = create_button(init_rect(3, 3, 100, 30), (t_gui_obj *)my_menu, "gui_textures/Button.png");
    button_settings(renderer, &my_menu->main_button);
    button_set_label("RT menu", 128, renderer, &my_menu->main_button);
    my_menu->main_button.action = &hide_menu;
    /*                    */
    my_menu->numb_of_control = 6; // указываем кол-во
    /*  init controls */ // заполняем
    my_menu->controls = (t_val_control *)malloc(sizeof(t_val_control) * my_menu->numb_of_control);
    my_menu->controls[0] = create_controller(init_rect(3, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.filter.x);
    more_controler_settings(&my_menu->controls[0], 1.0, 0.0);
    controller_settings(&my_menu->controls[0], renderer, 0.1);

    my_menu->controls[1] = create_controller(init_rect(166, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.filter.y);
    more_controler_settings(&my_menu->controls[1], 1.0, 0.0);
    controller_settings(&my_menu->controls[1], renderer, 0.1);

    my_menu->controls[2] = create_controller(init_rect(331, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.filter.z);
    more_controler_settings(&my_menu->controls[2], 1.0, 0.0);
    controller_settings(&my_menu->controls[2], renderer, 0.1);

    my_menu->controls[3] = create_controller(init_rect(166, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.dust);
    more_controler_settings(&my_menu->controls[3], 0.1, 0);
    controller_settings(&my_menu->controls[3], renderer, 0.01);

    my_menu->controls[4] = create_controller(init_rect(166, 237, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.brightness);
    more_controler_settings(&my_menu->controls[4], 10, 0);
    controller_settings(&my_menu->controls[4], renderer, 1);

    my_menu->controls[5] = create_controller(init_rect(166, 321, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.refr_coef);
    more_controler_settings(&my_menu->controls[5], 2, 1);
    controller_settings(&my_menu->controls[5], renderer, 0.1);
    /*               */
    my_menu->numb_of_radio = 1; //указываем кол-во 
    /*  init radio   */ //заполняем
    my_menu->radio = (t_radio_button *)malloc(sizeof(t_radio_button) * my_menu->numb_of_radio);
    my_menu->radio[0] = create_radio(init_rect(2, 380, 430, 150), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->cam.effect);
    radio_settings(&my_menu->radio[0], renderer, 5, "NO EFFECT", "B_N_W", "NEGATIVE", "SEPIA", "KUKSA_PEDR");
    /*               */ 
    my_menu->numb_of_labels = 4; // 6 указываем кол-во
    my_menu->labels = (t_label *)malloc(sizeof(t_label) * my_menu->numb_of_labels);
    my_menu->labels[0] = create_label(2, 36, "filter_x_y_z", (t_gui_obj *)my_menu);
    my_menu->labels[0].width = 115;
    my_menu->labels[0].height = 25;
    label_settings(128, renderer, &my_menu->labels[0], 0);

    my_menu->labels[1] = create_label(2, 122, "dust", (t_gui_obj *)my_menu);
    my_menu->labels[1].width = 115;
    my_menu->labels[1].height = 25;
    label_settings(128, renderer, &my_menu->labels[1], 0);

    my_menu->labels[2] = create_label(2, 209, "brightness", (t_gui_obj *)my_menu);
    my_menu->labels[2].width = 115;
    my_menu->labels[2].height = 25;
    label_settings(128, renderer, &my_menu->labels[2], 0);

    my_menu->labels[3] = create_label(2, 296, "refr coef", (t_gui_obj *)my_menu);
    my_menu->labels[3].width = 115;
    my_menu->labels[3].height = 25;
    label_settings(128, renderer, &my_menu->labels[3], 0);
    /*  init labels  */ //заполняем

    /*               */
    my_menu->my_rect.w = 495; //ширина меню
    my_menu->my_rect.h = 600; //высота меню
    //штуки на отношения
    my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2) / g_win_width;
    my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2) / g_win_height;
    menu_own_set(renderer, my_menu); //тестурки
    return ; //fill
}

void                fill_objects_menu(t_gui_menu *my_menu, SDL_Renderer *renderer) //заполнение меню объектов
{
    my_menu->main_button = create_button(init_rect(3, 3, 100, 30), (t_gui_obj *)my_menu, "gui_textures/Button.png");
    button_settings(renderer, &my_menu->main_button);
    button_set_label("Objs menu", 128, renderer, &my_menu->main_button);
    my_menu->main_button.action = &hide_menu;

    my_menu->numb_of_control = 7;

    my_menu->controls = (t_val_control *)malloc(sizeof(t_val_control) * my_menu->numb_of_control);
    my_menu->controls[0] = create_controller(init_rect(3, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].color.x);
    more_controler_settings(&my_menu->controls[0], 1.0, 0.0);
    controller_settings(&my_menu->controls[0], renderer, 0.1);

    my_menu->controls[1] = create_controller(init_rect(166, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].color.y);
    more_controler_settings(&my_menu->controls[1], 1.0, 0.0);
    controller_settings(&my_menu->controls[1], renderer, 0.1);

    my_menu->controls[2] = create_controller(init_rect(331, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].color.z);
    more_controler_settings(&my_menu->controls[2], 1.0, 0.0);
    controller_settings(&my_menu->controls[2], renderer, 0.1);

    my_menu->controls[3] = create_controller(init_rect(3, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].emission.x);
    more_controler_settings(&my_menu->controls[3], 100.0, 0.0);
    controller_settings(&my_menu->controls[3], renderer, 1.0);

    my_menu->controls[4] = create_controller(init_rect(166, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].emission.y);
    more_controler_settings(&my_menu->controls[4], 100.0, 0.0);
    controller_settings(&my_menu->controls[4], renderer, 1.0);

    my_menu->controls[5] = create_controller(init_rect(331, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].emission.z);
    more_controler_settings(&my_menu->controls[5], 100.0, 0.0);
    controller_settings(&my_menu->controls[5], renderer, 1.0);

    my_menu->controls[6] = create_controller(init_rect(166, 237, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].roughness);
    more_controler_settings(&my_menu->controls[6], 1, 0);
    controller_settings(&my_menu->controls[6], renderer, 0.1);

    my_menu->numb_of_labels = 3;

    my_menu->labels = (t_label *)malloc(sizeof(t_label) * my_menu->numb_of_labels);
    my_menu->labels[0] = create_label(2, 36, "color_r_g_b", (t_gui_obj *)my_menu);
    my_menu->labels[0].width = 115;
    my_menu->labels[0].height = 25;
    label_settings(128, renderer, &my_menu->labels[0], 0);

    my_menu->labels[1] = create_label(2, 122, "emission_x_y_z", (t_gui_obj *)my_menu);
    my_menu->labels[1].width = 115;
    my_menu->labels[1].height = 25;
    label_settings(128, renderer, &my_menu->labels[1], 0);

    my_menu->labels[2] = create_label(2, 209, "roughness", (t_gui_obj *)my_menu);
    my_menu->labels[2].width = 115;
    my_menu->labels[2].height = 25;
    label_settings(128, renderer, &my_menu->labels[2], 0);

    my_menu->numb_of_radio = 0;

    my_menu->my_rect.w = 495; //ширина меню
    my_menu->my_rect.h = 500; //высота меню

    my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2) / g_win_width;
    my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2) / g_win_height;
    menu_own_set(renderer, my_menu); //тестурки
    return ; //fill
}

void                super_update(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
    int             i;

    i = -1;
    while (++i < my_menu->numb_of_control)
        destroy_controller(&my_menu->controls[i]);

    my_menu->controls[0] = create_controller(init_rect(3, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].color.x);
    more_controler_settings(&my_menu->controls[0], 1.0, 0.0);
    controller_settings(&my_menu->controls[0], renderer, 0.1);

    my_menu->controls[1] = create_controller(init_rect(166, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].color.y);
    more_controler_settings(&my_menu->controls[1], 1.0, 0.0);
    controller_settings(&my_menu->controls[1], renderer, 0.1);

    my_menu->controls[2] = create_controller(init_rect(331, 63, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].color.z);
    more_controler_settings(&my_menu->controls[2], 1.0, 0.0);
    controller_settings(&my_menu->controls[2], renderer, 0.1);

    my_menu->controls[3] = create_controller(init_rect(3, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].emission.x);
    more_controler_settings(&my_menu->controls[3], 1.0, 0.0);
    controller_settings(&my_menu->controls[3], renderer, 0.1);

    my_menu->controls[4] = create_controller(init_rect(166, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].emission.y);
    more_controler_settings(&my_menu->controls[4], 1.0, 0.0);
    controller_settings(&my_menu->controls[4], renderer, 0.1);

    my_menu->controls[5] = create_controller(init_rect(331, 150, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].emission.z);
    more_controler_settings(&my_menu->controls[5], 1.0, 0.0);
    controller_settings(&my_menu->controls[5], renderer, 0.1);

    my_menu->controls[6] = create_controller(init_rect(166, 237, 160, 56), (t_gui_obj *)my_menu, "gui_textures/Button.png", &my_menu->scene->obj[my_menu->scene->last_obj].roughness);
    more_controler_settings(&my_menu->controls[6], 1, 0);
    controller_settings(&my_menu->controls[6], renderer, 0.1);
}

void                update_menu(t_gui_menu *my_menu, char with_text, SDL_Renderer *renderer, char hide) //не трогать
{
    int             i;
    int             help;

    if (with_text)
        menu_own_set(renderer, my_menu);
    my_menu->my_rect.x = my_menu->x * g_win_width - (float)my_menu->my_rect.w / 2;
    my_menu->my_rect.y = my_menu->y * g_win_height - (float)my_menu->my_rect.h / 2;
    if (!hide)
    {
        help = 0;
        if (my_menu->main_button.action != &hide_menu)
        {
            my_menu->main_button.action(my_menu, renderer);
            help = 1;
        }
        my_menu->main_button.update(&my_menu->main_button, with_text, renderer, 0);
        i = -1;
        while (++i < my_menu->numb_of_labels)
            my_menu->labels[i].update(&my_menu->labels[i], with_text, renderer, 0);
        i = -1;
        while (++i < my_menu->numb_of_control)
            my_menu->controls[i].update(&my_menu->controls[i], with_text, renderer, 0);
        i = -1;
        while (++i < my_menu->numb_of_radio)
            my_menu->radio[i].update(&my_menu->radio[i], with_text, renderer);
        if (help)
            my_menu->main_button.action(my_menu,renderer);
    }
}

void                draw_menu(SDL_Renderer *renderer, t_gui_menu *my_menu) //не трогать
{
    int             i;

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

t_gui_obj           *check_menu_collision(int x, int y, t_gui_obj *gui_obj) //не трогать
{
    t_gui_menu      *my_menu;
    t_gui_obj       *temp;
    int             i;

    temp = NULL;
    if (check_click(x, y, gui_obj))
    {
        my_menu = (t_gui_menu *)gui_obj;
        i = -1;
        if ((temp = my_menu->main_button.collision(x, y, (t_gui_obj *)&my_menu->main_button)))
            return (temp);
        while (++i < my_menu->numb_of_control)
        {
            if ((temp = my_menu->controls[i].collision(x, y, (t_gui_obj *)&my_menu->controls[i])))
                return (temp);
        }
        i = -1;
        while (++i < my_menu->numb_of_radio)
        {
            if ((temp = my_menu->radio[i].collision(x, y, (t_gui_obj *)&my_menu->radio[i])))
                return (temp);
        }
        temp = gui_obj;
    }
    return (temp);
}

void            menu_action(void *some_shit, SDL_Renderer *renderer) //не трогать
{
    t_gui_menu  *my_menu;

    my_menu = (t_gui_menu *)some_shit;
    my_menu->my_rect.x += my_menu->mouse->dx;
    my_menu->mouse->dx = 0;
    my_menu->my_rect.y += my_menu->mouse->dy;
    my_menu->mouse->dy = 0;
    my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2) / g_win_width;
    my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2) / g_win_height;
    my_menu->update(my_menu, 0, renderer, 0);
}

void            hide_menu(void *some_shit, SDL_Renderer *renderer) //можно трогать только высоту окна или менять его ширину
{
    t_gui_menu  *my_menu;

    my_menu = (t_gui_menu *)some_shit;
    /* уменьшить высоту окна */
    my_menu->my_rect.h = 36;
    my_menu->my_rect.w = 120;
    /*                       */
    my_menu->x = (float)(my_menu->my_rect.x + (float)my_menu->my_rect.w / 2) / g_win_width;
    my_menu->y = (float)(my_menu->my_rect.y + (float)my_menu->my_rect.h / 2) / g_win_height;
    my_menu->numb_of_labels = 0;
    my_menu->numb_of_control = 0;
    my_menu->numb_of_radio = 0;
    if (my_menu->m_type == GLOBAL_MENU)
        my_menu->main_button.action = &unhide_global_menu;
    else if (my_menu->m_type == OBJECTS_MENU)
        my_menu->main_button.action = &unhide_objects_menu;
    my_menu->update(my_menu, 1, renderer, 1);
}

void             destroy_menu(t_gui_menu *my_menu, SDL_Renderer *renderer) //не трогать
{
    int          i;

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