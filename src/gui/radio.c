/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 13:26:57 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/28 13:26:59 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

t_radio_button          create_radio(SDL_Rect my_rect, t_gui_obj *father, char *text, int *value)
{
    t_radio_button      my_radio;

    my_radio.x = my_rect.x;
    my_radio.y = my_rect.y;
    my_radio.my_rect = my_rect;
    my_radio.father = father;
    my_radio.texture = NULL;
    my_radio.source = text;
    my_radio.value = value;
    my_radio.last_pressed = 0;
    my_radio.draw = &draw_radio;
    my_radio.update = &update_radio;
    my_radio.collision = &check_radio_collision;
    return (my_radio);
}

void                    radio_own_set(SDL_Renderer *renderer, t_radio_button *my_radio)
{
    SDL_Surface         *surface;

    surface = IMG_Load(my_radio->source);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
    if (my_radio->texture)
        SDL_DestroyTexture(my_radio->texture);
    my_radio->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);       
}

void                     radio_settings(t_radio_button *my_radio, SDL_Renderer *renderer, int number, ...)
{
    va_list               list;
    int                   i;

    radio_own_set(renderer, my_radio);
    my_radio->num_of_buttons = number;
    my_radio->buttons = (t_button *)malloc(sizeof(t_button) * my_radio->num_of_buttons);
    i = -1;
    while (++i < my_radio->num_of_buttons)
    {
        my_radio->buttons[i] = create_button(init_rect(i * 20, i * 20, 20, 20), (t_gui_obj *)my_radio, "gui_textures/images.png"); //настроить
        button_settings(renderer, &my_radio->buttons[i]);
        button_set_label(va_arg(list, char *), 128, renderer, &my_radio->buttons[i]);
        my_radio->buttons[i].action = &radio_action;
    }
    va_end(list);
    my_radio->pointer.width = 40; //настроить
    my_radio->pointer.height = 40; //настроить
    my_radio->pointer = create_label(my_radio->buttons[*(my_radio->value)].my_rect.x + my_radio->buttons[*(my_radio->value)].my_rect.w / 2 - my_radio->pointer.width / 2,
            my_radio->buttons[*(my_radio->value)].my_rect.y + my_radio->buttons[*(my_radio->value)].my_rect.h, "^", (t_gui_obj *)my_radio);
}

void                        update_radio(t_radio_button *my_radio, char with_text, SDL_Renderer *renderer)
{
    int                     i;

    if (with_text)
        radio_own_set(renderer, my_radio);
    my_radio->my_rect.x = my_radio->x + my_radio->father->my_rect.x;
    my_radio->my_rect.y = my_radio->y + my_radio->father->my_rect.y;
    i = -1;
    while(++i < my_radio->num_of_buttons)
        my_radio->buttons[i].update(&my_radio->buttons[i], with_text, renderer, 0);
    my_radio->pointer.update(&my_radio->pointer, with_text, renderer, 0);
}

void                        draw_radio(SDL_Renderer *renderer, t_radio_button *my_radio)
{
    int                     i;

    SDL_RenderCopy(renderer, my_radio->texture, NULL, &my_radio->my_rect);
    i = -1;
    while(++i < my_radio->num_of_buttons)
        my_radio->buttons[i].draw(renderer, &my_radio->buttons[i]);
    my_radio->pointer.draw(renderer, &my_radio->pointer);
    
}

t_gui_obj                   *check_radio_collision(int x, int y, t_gui_obj *gui_obj)
{
    t_radio_button          *my_radio;
    t_gui_obj               *temp;
    int                     i;

    temp = NULL;
    if (check_click(x, y, gui_obj))
    {
        i = -1;
        my_radio = (t_radio_button *)gui_obj;
        while (++i < my_radio->num_of_buttons)
        {
            if ((temp = my_radio->buttons[i].collision(x, y, (t_gui_obj *)&my_radio->buttons[i])))
            {
                my_radio->last_pressed = i;
                return (temp);
            }
        }
    }
    return (temp);
}

void                        radio_action(void *some_shit, SDL_Renderer *renderer)
{
    t_radio_button          *my_radio;

    my_radio = (t_radio_button *)some_shit;
    *(my_radio->value) = my_radio->last_pressed;
    my_radio->pointer.x = my_radio->buttons[my_radio->last_pressed].my_rect.x +
                                  my_radio->buttons[my_radio->last_pressed].my_rect.w / 2 -
                                  my_radio->pointer.width / 2;
    my_radio->pointer.y = my_radio->buttons[my_radio->last_pressed].my_rect.y +
                                  my_radio->buttons[my_radio->last_pressed].my_rect.h;
}
