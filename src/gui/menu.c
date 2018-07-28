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

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

t_gui_menu          create_menu(SDL_Rect my_rect, char *text, t_mouse *mouse)
{
    t_gui_menu      my_menu;

    my_menu.x = (float)(my_rect.x + (float)my_rect.w / 2) / g_win_width;
    my_menu.y = (float)(my_rect.y + (float)my_rect.h / 2) / g_win_height;
    my_menu.my_rect = my_rect;
    my_menu.texture = NULL;
    my_menu.source = text;
    my_menu.father = NULL;
    my_menu.type = 1;
    my_menu.mouse = mouse;
    my_menu.draw = &draw_menu;
    my_menu.update = &update_menu;
    my_menu.collision = &check_menu_collision;
    my_menu.action = &menu_action;
    return (my_menu);
}

void                menu_own_set(SDL_Renderer *renderer, t_gui_menu *my_menu)
{
    SDL_Surface     *surface;

    surface = IMG_Load(my_menu->source);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF));
    if (my_menu->texture)
        SDL_DestroyTexture(my_menu->texture);
    my_menu->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void               menu_settings(t_gui_menu *my_menu, SDL_Renderer *renderer, menu_type type)
{
    if (type == GLOBAL_MENU)
        fill_global_menu(my_menu, renderer);
    else if (type == OBJECTS_MENU)
        fill_objects_menu(my_menu, renderer);
}

void                fill_global_menu(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
    return ; //fill
}

void                fill_objects_menu(t_gui_menu *my_menu, SDL_Renderer *renderer)
{
    return ; //fill
}

void                update_menu(t_gui_menu *my_menu, char with_text, SDL_Renderer *renderer)
{
    int             i;

    if (with_text)
        menu_own_set(renderer, my_menu);
    my_menu->my_rect.x = my_menu->x * g_win_width - (float)my_menu->my_rect.w / 2;
    my_menu->my_rect.y = my_menu->y * g_win_height - (float)my_menu->my_rect.h / 2;
    i = -1;
    while (++i < my_menu->numb_of_labels)
        my_menu->labels[i].update(&my_menu->labels[i], with_text, renderer, 0);
    i = -1;
    while (++i < my_menu->numb_of_control)
        my_menu->controls[i].update(&my_menu->controls[i], with_text, renderer, 0);
    i = -1;
    while (++i < my_menu->numb_of_radio)
        my_menu->radio[i].update(&my_menu->radio[i], with_text, renderer);
}

void                draw_menu(SDL_Renderer *renderer, t_gui_menu *my_menu)
{
    int             i;

    SDL_RenderCopy(renderer, my_menu->texture, NULL, &my_menu->my_rect);
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

t_gui_obj           *check_menu_collision(int x, int y, t_gui_obj *gui_obj)
{
    t_gui_menu      *my_menu;
    t_gui_obj       *temp;
    int             i;

    temp = NULL;
    if (check_click(x, y, gui_obj))
    {
        my_menu = (t_gui_menu *)gui_obj;
        i = -1;
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
    return temp;
}

void            menu_action(void *some_shit, SDL_Renderer *renderer)
{
    t_gui_menu  *my_menu;

    my_menu = (t_gui_menu *)some_shit;
    my_menu->my_rect.x += my_menu->mouse->dx;
    my_menu->mouse->dx = 0;
    my_menu->my_rect.y += my_menu->mouse->dy;
    my_menu->mouse->dy = 0;
    my_menu->update(my_menu, 0, renderer);   
}