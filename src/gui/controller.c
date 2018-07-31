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

t_val_control      create_controller(SDL_Rect my_rect, t_gui_obj *father, char *text, float *value) //не трогать
{
    t_val_control   my_control;

    my_control.my_rect = my_rect;
    my_control.x = my_rect.x;
    my_control.y = my_rect.y;
    my_control.my_rect.x = my_control.x + father->my_rect.x;
    my_control.my_rect.y = my_control.y + father->my_rect.y;
    my_control.father = father;
    my_control.texture = NULL;
    my_control.source = (char *)malloc(sizeof(char) * ft_strlen(text));
    my_control.source = ft_strcpy(my_control.source, text);
    my_control.value = value;
    my_control.draw = &draw_controler;
    my_control.update = &update_controler;
    my_control.collision = &check_contol_collision;
    return (my_control);
}

void               controller_own_set(SDL_Renderer *renderer, t_val_control *my_control) //не трогать
{
    SDL_Surface     *surface;

    surface = IMG_Load(my_control->source);
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF));
    if (my_control->texture)
        SDL_DestroyTexture(my_control->texture);
    my_control->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void                more_controler_settings(t_val_control *my_control, float max_val, float min_val, char *val_name) //не трогать
{
    my_control->max_val = max_val;
    my_control->min_val = min_val;
    my_control->val_name = val_name;
}

void               controller_settings(t_val_control *my_control, SDL_Renderer *renderer, float step)
{
    char           str[10];
    char           *accur;

    controller_own_set(renderer, my_control);
    my_control->step = step;
    my_control->change_buttons[0] = create_button(init_rect(3, 3, 50, 50), (t_gui_obj *)my_control, "gui_textures/images.png"); //настроить
    button_settings(renderer, &my_control->change_buttons[0]);
    button_set_label(my_control->val_name, 128, renderer, &my_control->change_buttons[0]);
    my_control->change_buttons[1] = create_button(init_rect(107, 3, 50, 50), (t_gui_obj *)my_control, "gui_textures/images.png");  //настроить
    button_settings(renderer, &my_control->change_buttons[1]);
    button_set_label(my_control->val_name, 128, renderer, &my_control->change_buttons[1]);
    my_control->change_buttons[0].action = &minus_action;
    my_control->change_buttons[1].action = &plus_action;
    sprintf(str, "%f", *(my_control->value));
    accur = ft_strchr(str, '.');
    accur += 4;
    *accur = '\0';
    my_control->output = create_label(55, 3, str, (t_gui_obj *)my_control); //настроить
    my_control->output.width = 50;
    my_control->output.height = 50;
    label_settings(128, renderer, &my_control->output, 0);
}

void                update_controler(t_val_control *my_control, char with_text, SDL_Renderer *renderer, char with_alph) //не трогать
{
    if (with_text)
        controller_own_set(renderer, my_control);
    if (!with_alph || with_text)
    {
        my_control->my_rect.x = my_control->x + my_control->father->my_rect.x;
        my_control->my_rect.y = my_control->y + my_control->father->my_rect.y;
    }
    my_control->change_buttons[0].update(&my_control->change_buttons[0], with_text, renderer, 0);
    my_control->change_buttons[1].update(&my_control->change_buttons[1], with_text, renderer, 0);
    my_control->output.update(&my_control->output, with_text, renderer, with_alph);
}

void                draw_controler(SDL_Renderer *renderer, t_val_control *my_control) //не трогать
{
    SDL_RenderCopy(renderer, my_control->texture, NULL, &my_control->my_rect);
    my_control->change_buttons[0].draw(renderer, &my_control->change_buttons[0]);
    my_control->change_buttons[1].draw(renderer, &my_control->change_buttons[1]);
    my_control->output.draw(renderer, &my_control->output);
}

t_gui_obj           *check_contol_collision(int x, int y, t_gui_obj *gui_obj) //не трогать
{
    t_val_control   *my_control;
    t_gui_obj       *temp;

    temp = NULL;
    if (check_click(x, y, gui_obj))
    {
        my_control = (t_val_control *)gui_obj;
        if ((temp = my_control->change_buttons[0].collision(x, y, (t_gui_obj *)&my_control->change_buttons[0])))
            return (temp);
        if ((temp = my_control->change_buttons[1].collision(x, y, (t_gui_obj *)&my_control->change_buttons[1])))
            return (temp);
    }
    return (temp);
}

void                plus_action(void *some_shit, SDL_Renderer *renderer) //не трогать
{
    t_val_control   *my_control;
    char            *accur;
    char            str[10];

    my_control = (t_val_control *)some_shit;
    if (*(my_control->value) < my_control->max_val)
    {
        *(my_control->value) += my_control->step;
        sprintf(str, "%f", *(my_control->value));
        accur = ft_strchr(str, '.');
        accur += 4;
        *accur = '\0';
        my_control->output.text = ft_strcpy(my_control->output.text, str);
        my_control->update(my_control, 0, renderer, 1);
    }
}

void                minus_action(void *some_shit, SDL_Renderer *renderer) //не трогать
{
    t_val_control   *my_control;
    char            *accur;
    char            str[10];

    my_control = (t_val_control *)some_shit;
    if (*(my_control->value) - 0.0009 > my_control->min_val)
    {
        *(my_control->value) -= my_control->step;
        sprintf(str, "%f", *(my_control->value));
        accur = ft_strchr(str, '.');
        accur += 4;
        *accur = '\0';
        my_control->output.text = ft_strcpy(my_control->output.text, str);
        my_control->update(my_control, 0, renderer, 1);
    }
}

void                destroy_controller(t_val_control *my_control) //не трогать
{
    SDL_DestroyTexture(my_control->texture);
    destroy_label(&my_control->output);
    destroy_button(&my_control->change_buttons[0]);
    destroy_button(&my_control->change_buttons[1]);
    free(my_control->source);
}
