/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 19:27:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/07/31 19:27:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int		g_win_width;
extern unsigned int		g_win_height;

void	init_seeds(t_seeds *s)
{
	size_t		i;

	s->size = (uint)(g_win_height * g_win_width * 2);
	s->seeds = (uint*)malloc(sizeof(uint) * s->size);
	srand((uint)clock());
	i = 0;
	while (i < s->size)
		s->seeds[i++] = (uint)rand();
}

void	print_log(t_cldata *cl)
{
	char	*build_log;
	size_t	size;

	clGetProgramBuildInfo(cl->program, cl->dev_id, CL_PROGRAM_BUILD_LOG, 0, 0,
						  &size);
	build_log = (char*)malloc(sizeof(char) * size);
	clGetProgramBuildInfo(cl->program, cl->dev_id, CL_PROGRAM_BUILD_LOG, size,
						  build_log, 0);
	write(1, build_log, ft_strlen(build_log));
	exit(EXIT_FAILURE);
}

void	init_defaults(t_env *env)
{
	env->num_samples = 0;
	env->mv_data.move_keys = NOKEY;
	env->mv_data.move_spd = 1.f;
	env->mv_data.turn_a = 2.5;
	env->mv_data.cosine_a = cos(DTR(env->mv_data.turn_a));
	env->mv_data.sine_a = sin(DTR(env->mv_data.turn_a));
	env->client.active = 0;
	env->server.active = 0;
}