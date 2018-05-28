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
#include <time.h>

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

	build_log_size = 4096;
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
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_CPU, 1, &cl->dev_id, 0);
	assert (err == CL_SUCCESS);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, &err);
	assert (err == CL_SUCCESS);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, &err);
	assert (err == CL_SUCCESS);
	cl->source = (char**)malloc(sizeof(char*));
	*cl->source = read_file(KERNEL_PATH, &cl->source_size);
	assert(*cl->source != NULL);
	cl->program = clCreateProgramWithSource(cl->context, 1,
		(const char **)cl->source, &cl->source_size, &err);
	assert (err == CL_SUCCESS);
	err = clBuildProgram(cl->program, 0, 0, options, 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("BUILD ERROR: %d\n", err);
		print_log(cl);
	}
	cl->kernel = clCreateKernel(cl->program, "render_pixel", &err);
	assert (err == CL_SUCCESS);
}

void	init_seeds(t_seeds *s)
{
	int		i;

	s->size = (uint)(g_win_height * g_win_width * 2);
	s->seeds = (int*)malloc(sizeof(uint) * s->size);
	srand((uint)clock());
	i = -1;
	while (++i < s->size)
		s->seeds[i] = rand(); // NOLINT
}

int		main(void)
{
	t_cldata	cl;
	cl_mem		px_gpu;
	cl_mem		obj_gpu;
	t_seeds		seeds_host;
	cl_mem		seed_gpu;
	cl_float3	*px_host;
	int			err;
	t_scrn		screen;
	t_scene		scene;

	init_openCL(&cl);
	init_scene(&scene);
	init_seeds(&seeds_host);
	px_host = (cl_float3*)malloc(sizeof(cl_float3) * g_win_width * g_win_height);

	//get size of the buffer
	cl.global_size = g_win_height * g_win_width;

	//allocate memory on context for buffers
	px_gpu = clCreateBuffer(cl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		sizeof(cl_float3) * g_win_width * g_win_height, 0, &err);
	assert (err == CL_SUCCESS);
	obj_gpu = clCreateBuffer(cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
		sizeof(t_sphere) * scene.num_obj, scene.obj, &err);
	assert (err == CL_SUCCESS);
	seed_gpu = clCreateBuffer(cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
		sizeof(int) * seeds_host.size, seeds_host.seeds, &err);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(cl.kernel, 0, sizeof(px_gpu), &px_gpu);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 1, sizeof(obj_gpu), &obj_gpu);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 2, sizeof(scene.num_obj), &scene.num_obj);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 3, sizeof(scene.cam), &scene.cam);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 4, sizeof(g_win_width), &g_win_width);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 5, sizeof(g_win_height), &g_win_height);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl.kernel, 6, sizeof(seed_gpu), &seed_gpu);
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
	printf("local size: %lu\n", cl.local_size);

	//push task to the command queue
	err = clEnqueueNDRangeKernel(cl.command_queue, cl.kernel, 1, 0,
		&cl.global_size, &cl.local_size, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(cl.command_queue, px_gpu, CL_FALSE, 0,
		sizeof(cl_float3) * g_win_width * g_win_height, px_host, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//wait while the task is being processed AND BUFFER IS BEING READ
	//this way reading is a bit faster
	clFinish(cl.command_queue);

	init_win(&screen);
	for(int i = 0; i < cl.global_size; ++i)
	{
		screen.surf_arr[i].bgra[0] = (u_char) (px_host[i].z * 0xff);
		screen.surf_arr[i].bgra[1] = (u_char) (px_host[i].y * 0xff);
		screen.surf_arr[i].bgra[2] = (u_char) (px_host[i].x * 0xff);
	}
	main_loop(&screen);
	close_sdl(&screen);

	return (0);
}
