/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 17:02:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/05/22 17:02:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

unsigned int	g_win_width = 1080;
unsigned int	g_win_height = 720;

int		main(int argc, char **argv)
{
	t_env	env;

	init_opencl(&env.cl);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	init_defaults(&env);
	init_scene(&env.scene, argc, argv);
	compress_texture(&env.textures);
	env.scene.last_obj = 0;
	printf("tx count: %d\n", env.textures.tx_count);
	printf("tx size: %d\n", env.textures.total_size);
	if (parse_server_data(argc, argv, &env.server))
		run_server(&env);
	init_seeds(&env.cl.seeds);
	get_work_group_size(&env.cl);
	init_win(&env.screen, 1, 1);
	env.gui = init_gui(env.screen.renderer, &env.scene);
	main_loop_server(&env);
	quit_server(&env.server);
	close_sdl(&env.screen);
	IMG_Quit();
	//write_scene(&(env.scene));
	system("leaks -q RT"); //DEBUG
	return (0);
}
