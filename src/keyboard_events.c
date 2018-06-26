/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:35:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/26 16:35:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	keyboard_event(SDL_Event e, t_cldata *cl)
{
	if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		cl->down_keys |= KEY_ESC;
	else if (e.type == SDL_KEYDOWN)
		key_down_event(e, cl);
	else
		key_up_event(e, cl);
}

void	key_down_event(SDL_Event e, t_cldata *cl)
{
	if (e.key.keysym.sym == SDLK_w)
		cl->down_keys |= KEY_W;
	else if (e.key.keysym.sym == SDLK_s)
		cl->down_keys |= KEY_S;
	else if (e.key.keysym.sym == SDLK_a)
		cl->down_keys |= KEY_A;
	else if (e.key.keysym.sym == SDLK_d)
		cl->down_keys |= KEY_D;
	else if (e.key.keysym.sym == SDLK_q)
		cl->down_keys |= KEY_Q;
	else if (e.key.keysym.sym == SDLK_e)
		cl->down_keys |= KEY_E;
	else if (e.key.keysym.sym == SDLK_UP)
		cl->down_keys |= KEY_UP;
	else if (e.key.keysym.sym == SDLK_DOWN)
		cl->down_keys |= KEY_DOWN;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		cl->down_keys |= KEY_RIGHT;
	else if (e.key.keysym.sym == SDLK_LEFT)
		cl->down_keys |= KEY_LEFT;
	else if (e.key.keysym.sym == SDLK_SPACE)
		cl->down_keys |= KEY_SPACE;
	else if (e.key.keysym.sym == SDLK_c)
		cl->down_keys |= KEY_C;
}

void	key_up_event(SDL_Event e, t_cldata *cl)
{
	if (e.key.keysym.sym == SDLK_w)
		cl->down_keys ^= KEY_W;
	else if (e.key.keysym.sym == SDLK_s)
		cl->down_keys ^= KEY_S;
	else if (e.key.keysym.sym == SDLK_a)
		cl->down_keys ^= KEY_A;
	else if (e.key.keysym.sym == SDLK_d)
		cl->down_keys ^= KEY_D;
	else if (e.key.keysym.sym == SDLK_q)
		cl->down_keys ^= KEY_Q;
	else if (e.key.keysym.sym == SDLK_e)
		cl->down_keys ^= KEY_E;
	else if (e.key.keysym.sym == SDLK_UP)
		cl->down_keys ^= KEY_UP;
	else if (e.key.keysym.sym == SDLK_DOWN)
		cl->down_keys ^= KEY_DOWN;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		cl->down_keys ^= KEY_RIGHT;
	else if (e.key.keysym.sym == SDLK_LEFT)
		cl->down_keys ^= KEY_LEFT;
	else if (e.key.keysym.sym == SDLK_SPACE)
		cl->down_keys ^= KEY_SPACE;
	else if (e.key.keysym.sym == SDLK_c)
		cl->down_keys ^= KEY_C;
}
