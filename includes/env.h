/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 12:02:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/08/01 12:02:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <OpenCL/opencl.h>
# include <SDL.h>
# include <SDL_image.h>
# include <time.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "libvec.h"
# include "get_next_line.h"
# include "rt_textures.h"
# include <netinet/in.h>
# include "server_client.h"
# include "rt_types.h"
# include "keys.h"
# include "parser.h"
# include "json.h"

# define KERNEL_PATH0 "src/cl_files/kernel_source.cl"
# define KERNEL_PATH1 "src/cl_files/intersections_and_normals.cl"
# define KERNEL_PATH2 "src/cl_files/texture_mapping.cl"
# define KERNEL_PATH3 "src/cl_files/material.cl"
# define KERNEL_INC_DIR "-I includes"

# define DEVICE_TYPE CL_DEVICE_TYPE_GPU
# define CLIENT_WORK_SIZE 100

# define MIN_WIN_WIDTH 500
# define MIN_WIN_HEIGHT 500

typedef struct		s_env
{
	t_cldata			cl;
	t_gui				gui;
	t_scrn				screen;
	t_scene				scene;
	t_mvdata			mv_data;
	t_txgpu				textures;
	t_server			server;
	t_client			client;
	unsigned int		num_samples;
}					t_env;

#endif
