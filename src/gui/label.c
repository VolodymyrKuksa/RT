/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_label.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 13:50:47 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/25 13:50:47 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

extern unsigned int g_win_width;
extern unsigned int g_win_height;

SDL_Color       set_default_text_color(void) //можно менять значения
{
    SDL_Color   that;

    that.r = 198;
    that.g = 157;
    that.b = 5;
    that.a = 170;
    return (that);
}

t_label     create_label(unsigned short int x, unsigned short int y, //не трогать
                            char *text, t_gui_obj *father)
{
    t_label my_label;

    my_label.x = x;
    my_label.y = y;
    my_label.text = (char *)malloc(sizeof(char) * 10);
    my_label.text = ft_strcpy(my_label.text, text);
    my_label.father = father;
    my_label.font = NULL;
    my_label.texture = NULL;
    my_label.draw = &draw_label;
    my_label.update = &update_label;
    my_label.width = 1;
    my_label.height = 1;
    return (my_label);
}

void     label_settings(int font_size, SDL_Renderer *renderer, //не трогать
                        t_label *my_label, int set_wh)
{
    SDL_Surface         *surface;
    SDL_Color           my_color;

    my_color = set_default_text_color();
    my_label->font = TTF_OpenFont(FONT, font_size);
    surface = TTF_RenderText_Solid(my_label->font, my_label->text, my_color);
    my_label->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (set_wh)
        SDL_QueryTexture(my_label->texture, NULL, NULL,
                         (int *)&my_label->width, (int *)&my_label->height);
    if (my_label->father)
    {
        my_label->dstrect.x = my_label->father->my_rect.x + my_label->x;
        my_label->dstrect.y = my_label->father->my_rect.y + my_label->y;
    } else {
        my_label->x = (my_label->x + (float)my_label->width / 2) / g_win_width;
        my_label->y = (my_label->y + (float)my_label->height / 2) / g_win_height;
        my_label->dstrect.x = (int)(my_label->x * g_win_width - (float)my_label->width / 2);
        my_label->dstrect.y = (int)(my_label->y * g_win_height - (float)my_label->height / 2);
    }
    my_label->dstrect.w = my_label->width;
    my_label->dstrect.h = my_label->height;
}

void        update_texture(SDL_Renderer *renderer, t_label *my_label) //не трогать
{
    SDL_Surface         *surface;
    SDL_Color           my_color;

    my_color = set_default_text_color();
    surface = TTF_RenderText_Solid(my_label->font, my_label->text, my_color);
    if (my_label->texture)
        SDL_DestroyTexture(my_label->texture);
    my_label->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void        update_label(t_label *my_label, char with_text, SDL_Renderer *renderer, char with_alph) //не трогать
{
    if (with_text || with_alph)
        update_texture(renderer, my_label);
    if (!with_alph || with_text)
    {
        if (my_label->father)
        {
            my_label->dstrect.x = my_label->x + my_label->father->my_rect.x;
            my_label->dstrect.y = my_label->y + my_label->father->my_rect.y;
        } else {
            my_label->dstrect.x = my_label->x * g_win_width;
            my_label->dstrect.y = my_label->y * g_win_height;
        }
    }
}

void      draw_label(SDL_Renderer *renderer, t_label *label) //не трогать
{
    SDL_RenderCopy(renderer, label->texture, NULL, &label->dstrect);
}

void      destroy_label(t_label *my_label) //не трогать
{
    SDL_DestroyTexture(my_label->texture);
    TTF_CloseFont(my_label->font);
    free(my_label->text);
}
