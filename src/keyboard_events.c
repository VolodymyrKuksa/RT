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
	else if (movement_key_event(e, env))
		return ;
	else if (e.type == SDL_KEYDOWN)
		key_down_event(e, env);
}

int		movement_key_event(SDL_Event e, t_env *env)
{
	static int	key_map[13][2] = { {SDLK_w, KEY_W}, {SDLK_s, KEY_S},
		{SDLK_a, KEY_A}, {SDLK_d, KEY_D}, {SDLK_q, KEY_Q}, {SDLK_e, KEY_E},
		{SDLK_UP, KEY_UP}, {SDLK_DOWN, KEY_DOWN}, {SDLK_RIGHT, KEY_RIGHT},
		{SDLK_LEFT, KEY_LEFT}, {SDLK_SPACE, KEY_SPACE},
		{SDLK_LSHIFT, KEY_LSHIFT}, {SDLK_ESCAPE, KEY_ESC}};
	int			i;

	i = -1;
	while (++i < 13)
	{
		if (e.key.keysym.sym == key_map[i][0])
		{
			env->mv_data.move_keys = (e.type == SDL_KEYDOWN ?
			env->mv_data.move_keys | key_map[i][1] :
			env->mv_data.move_keys ^ key_map[i][1]);
			return (1);
		}
	}
	return (0);
}

int		key_down_event(SDL_Event e, t_env *env)
{
	if (e.key.keysym.sym == SDLK_p)
		write_png(env);
	else
		return (0);
	return (1);
}
