/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikorchah <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 16:38:25 by ikorchah          #+#    #+#             */
/*   Updated: 2018/07/31 16:38:29 by ikorchah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	handle_mousebuttondown(SDL_Event *e, t_env *env, t_gui_obj **temp)
{
	env->gui.mouse->x = e->button.x;
	env->gui.mouse->y = e->button.y;
	*temp = env->gui.collision(e->button.x, e->button.y,
							   (t_gui_obj *)&env->gui);
	if (!(*temp))
	{
		get_mouse_intersection(env, *e);
		env->scene.last_obj = *env->cl.id_host;
		printf("id: %d, type: %d, kuksa_suka = %d\n", *env->cl.id_host,
			   env->scene.obj[*env->cl.id_host].type, env->scene.last_obj);
		env->gui.duper(&env->gui, env->screen.renderer);
	}
}

void	handle_mousemotion(SDL_Event *e, t_env *env, t_gui_obj *temp)
{
	if (temp && temp->type == 1)
	{
		env->gui.mouse->dx = e->motion.x - env->gui.mouse->x;
		env->gui.mouse->dy = e->motion.y - env->gui.mouse->y;
		env->gui.mouse->x = e->motion.x;
		env->gui.mouse->y = e->motion.y;
		temp->action((void *)temp, env->screen.renderer);
	}
}

void	handle_mousebuttonup(SDL_Event *e, t_env *env, t_gui_obj **temp)
{
	if (*temp == env->gui.collision(e->button.x, e->button.y,
									(t_gui_obj *)&env->gui) && *temp)
	{
		if ((*temp)->type == 0)
		{
			if ((*temp)->father)
			{
				(*temp)->action((void *)(*temp)->father, env->screen.renderer);
				if ((*temp)->father->father)
							we_control((t_gui_obj *)(*temp)->father->father);
			}
			else
				(*temp)->action((void *)(*temp), env->screen.renderer);
		}
		else if ((*temp)->type == 2)
			(*temp)->action(&env->scene, NULL);
		else if ((*temp)->type == 3)
			(*temp)->action(env, NULL);
	}
	*temp = NULL;
}

void	handle_events(t_env *env)
{
	SDL_Event			e;
	static t_gui_obj	*temp;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			env->mv_data.move_keys |= KEY_ESC;
		else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
			keyboard_event(e, env);
		else if (e.type == SDL_WINDOWEVENT)
			window_event(e, env);
		else if (e.type == SDL_MOUSEWHEEL)
			mouse_wheel_event(e, env);
		else if (e.type == SDL_MOUSEBUTTONDOWN)
			handle_mousebuttondown(&e, env, &temp);
		else if (e.type == SDL_MOUSEMOTION)
			handle_mousemotion(&e, env, temp);
		else if (e.type == SDL_MOUSEBUTTONUP)
			handle_mousebuttonup(&e, env, &temp);
	}
}

void	handle_events_client(t_env *env)
{
	SDL_Event	e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
			env->mv_data.move_keys |= KEY_ESC;
		else if (e.type == SDL_WINDOWEVENT)
			window_event(e, env);
		else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
			env->mv_data.move_keys |= KEY_ESC;
	}
}