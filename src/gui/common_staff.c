/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_staff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkushche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 14:39:31 by dkushche          #+#    #+#             */
/*   Updated: 2018/07/27 14:39:32 by dkushche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

SDL_Rect                init_rect(int x, int y, int w, int h) //не трогать
{
    SDL_Rect            some_rect;

    some_rect.x = x;
    some_rect.y = y;
    some_rect.w = w;
    some_rect.h = h;
    return (some_rect);
}

int        check_click(int x, int y, t_gui_obj *gui_obj) //не трогать
{
    if (x >= gui_obj->my_rect.x &&
        x <= (gui_obj->my_rect.x + gui_obj->my_rect.w) &&
        y >= gui_obj->my_rect.y &&
        y <= (gui_obj->my_rect.y + gui_obj->my_rect.h))
        return (1);
    return (0);
}
