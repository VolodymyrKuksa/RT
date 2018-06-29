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

void	keyboard_event(SDL_Event e, t_env *env)
{
	if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		env->mv_data.move_keys |= KEY_ESC;
	else if (e.type == SDL_KEYDOWN)
		key_down_event(e, env);
	else
		key_up_event(e, env);
}

int		movement_key_down_event(SDL_Event e, t_env *env)
{
	if (e.key.keysym.sym == SDLK_w)
		env->mv_data.move_keys |= KEY_W;
	else if (e.key.keysym.sym == SDLK_s)
		env->mv_data.move_keys |= KEY_S;
	else if (e.key.keysym.sym == SDLK_a)
		env->mv_data.move_keys |= KEY_A;
	else if (e.key.keysym.sym == SDLK_d)
		env->mv_data.move_keys |= KEY_D;
	else if (e.key.keysym.sym == SDLK_q)
		env->mv_data.move_keys |= KEY_Q;
	else if (e.key.keysym.sym == SDLK_e)
		env->mv_data.move_keys |= KEY_E;
	else if (e.key.keysym.sym == SDLK_UP)
		env->mv_data.move_keys |= KEY_UP;
	else if (e.key.keysym.sym == SDLK_DOWN)
		env->mv_data.move_keys |= KEY_DOWN;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		env->mv_data.move_keys |= KEY_RIGHT;
	else if (e.key.keysym.sym == SDLK_LEFT)
		env->mv_data.move_keys |= KEY_LEFT;
	else if (e.key.keysym.sym == SDLK_SPACE)
		env->mv_data.move_keys |= KEY_SPACE;
	else if (e.key.keysym.sym == SDLK_LSHIFT)
		env->mv_data.move_keys |= KEY_LSHIFT;
	else
		return (0);
	return (1);
}

void	key_down_event(SDL_Event e, t_env *env)
{
	if (movement_key_down_event(e, env))
		return ;
	if (e.key.keysym.sym == SDLK_p)
		write_png(env);
}

void	key_up_event(SDL_Event e, t_env *env)
{
	if (e.key.keysym.sym == SDLK_w)
		env->mv_data.move_keys ^= KEY_W;
	else if (e.key.keysym.sym == SDLK_s)
		env->mv_data.move_keys ^= KEY_S;
	else if (e.key.keysym.sym == SDLK_a)
		env->mv_data.move_keys ^= KEY_A;
	else if (e.key.keysym.sym == SDLK_d)
		env->mv_data.move_keys ^= KEY_D;
	else if (e.key.keysym.sym == SDLK_q)
		env->mv_data.move_keys ^= KEY_Q;
	else if (e.key.keysym.sym == SDLK_e)
		env->mv_data.move_keys ^= KEY_E;
	else if (e.key.keysym.sym == SDLK_UP)
		env->mv_data.move_keys ^= KEY_UP;
	else if (e.key.keysym.sym == SDLK_DOWN)
		env->mv_data.move_keys ^= KEY_DOWN;
	else if (e.key.keysym.sym == SDLK_RIGHT)
		env->mv_data.move_keys ^= KEY_RIGHT;
	else if (e.key.keysym.sym == SDLK_LEFT)
		env->mv_data.move_keys ^= KEY_LEFT;
	else if (e.key.keysym.sym == SDLK_SPACE)
		env->mv_data.move_keys ^= KEY_SPACE;
	else if (e.key.keysym.sym == SDLK_LSHIFT)
		env->mv_data.move_keys ^= KEY_LSHIFT;
}
