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
#include <assert.h>

#define KERNEL_PATH "/Users/vkuksa/projects/rt/src/kernel_source.cl"
//#define KERNEL_PATH "/Users/ikorchah/CLionProjects/RT/src/kernel_source.cl"

size_t		g_win_width = 1080;
size_t		g_win_height = 720;

void	main_loop(t_scrn *screen)
{
	SDL_Event	e;
	int			quit;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = 1;
			else if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					quit = 1;
			}
		}
		SDL_UpdateWindowSurface(screen->window);
	}
}

void	print_log(t_cldata *cl)
{
	int		err;
	size_t	build_log_size;
	char	*build_log;

	build_log_size = 2048;
	build_log = (char*)malloc(sizeof(char) * build_log_size);
	err = clGetProgramBuildInfo(cl->program, cl->dev_id, CL_PROGRAM_BUILD_LOG,
		build_log_size, build_log, 0);
	assert(err == CL_SUCCESS);
	printf("%s\n", build_log);
	exit(EXIT_FAILURE);
}

void	init_openCL(t_cldata *cl)
{
	int		err;
	char	*options;

	options = "-Werror";
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &cl->dev_id, 0);
	assert (err == CL_SUCCESS);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, &err);
	assert (err == CL_SUCCESS);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, &err);
	assert (err == CL_SUCCESS);
	cl->source = (char**)malloc(sizeof(char*));
	*cl->source = read_file(KERNEL_PATH, &cl->source_size);
	cl->program = clCreateProgramWithSource(cl->context, 1,
		(const char **)cl->source, &cl->source_size, &err);
	assert (err == CL_SUCCESS);
	err = clBuildProgram(cl->program, 0, 0, options, 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("BUILD ERROR: %d\n", err);
		print_log(cl);
	}
	cl->kernel = clCreateKernel(cl->program, "hello_world", &err);
	assert (err == CL_SUCCESS);
}

int		main(void) {

	t_cldata	cl;
	cl_mem		px_gpu;
	t_rgb		px_host[g_win_height * g_win_width];
	int			err;
	t_scrn		screen;

	init_openCL(&cl);

	//get size of the buffer
	cl.global_size = g_win_height * g_win_width;

	//allocate memory on context for buffers
	px_gpu = clCreateBuffer(cl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(px_host), 0, &err);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(cl.kernel, 0, sizeof(px_gpu), &px_gpu);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 1, sizeof(g_win_width), &g_win_width);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 2, sizeof(g_win_height), &g_win_height);
	assert (err == CL_SUCCESS);

	//getting max work group size for this task
	err = clGetKernelWorkGroupInfo(cl.kernel, cl.dev_id,
		CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl.local_size),
		&cl.local_size, 0);
	assert (err == CL_SUCCESS);
	cl.local_size = cl.local_size > cl.global_size ?
		cl.global_size : cl.local_size;
	while (cl.global_size % cl.local_size != 0)
		cl.local_size -= 1;
	printf("%lu\n", cl.local_size);

	//push task to the command queue
	err = clEnqueueNDRangeKernel(cl.command_queue, cl.kernel, 1, 0,
		&cl.global_size, &cl.local_size, 0, 0, 0);
	printf("%d\n", err);
	assert (err == CL_SUCCESS);

	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(cl.command_queue, px_gpu, CL_FALSE, 0,
							  sizeof(px_host), px_host, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//wait while the task is being processed AND BUFFER IS BEING READ
	//this way reading is a bit faster
	clFinish(cl.command_queue);

	init_win(&screen);
	for(int i = 0; i < cl.global_size; ++i)
		screen.surf_arr[i] = px_host[i];
	main_loop(&screen);
	close_sdl(&screen);

	return (0);
}
