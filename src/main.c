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

size_t		win_width = 1080;
size_t		win_height = 720;

int		init_win(t_scrn *screen)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putstr("SDL could not initialize! Error: ");
		ft_putendl(SDL_GetError());
		return (0);
	}
	else
	{
		screen->window = SDL_CreateWindow("CANCER RT", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, (int)win_width, (int)win_height,
			SDL_WINDOW_SHOWN);
		if (screen->window == NULL)
		{
			ft_putstr("Window could not be created! Error: ");
			ft_putendl(SDL_GetError());
			return (0);
		}
		else
			screen->surface = SDL_GetWindowSurface(screen->window);
	}
	screen->surf_arr = (t_rgb *)screen->surface->pixels;
	return (1);
}

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

void	close_sdl(t_scrn *screen)
{
	SDL_FreeSurface(screen->surface);
	SDL_DestroyWindow(screen->window);
	SDL_Quit();
}

void	init_openCL(t_cldata *cl)
{
	int		err;
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
	err = clBuildProgram(cl->program, 0, 0, 0, 0, 0);
//	printf("%d\n", err);
	assert (err == CL_SUCCESS);
	cl->kernel = clCreateKernel(cl->program, "hello_world", &err);
	assert (err == CL_SUCCESS);
}

int		main(void) {

	t_cldata	cldata;
	cl_mem		pixels;			//gpu memory for output colors
	cl_mem		width;
	cl_mem		height;
	t_rgb		px[win_height * win_width];		//host memory for output colors
	int			err;			//error code
	t_scrn		screen;

	init_openCL(&cldata);

	//get size of the buffer
	cldata.global_size = win_height * win_width;

	//allocate memory on context for buffers
	pixels = clCreateBuffer(cldata.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(px), 0, &err);
	assert (err == CL_SUCCESS);
	width = clCreateBuffer(cldata.context,
		CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY, sizeof(win_width), 0, &err);
	assert (err == CL_SUCCESS);
	height = clCreateBuffer(cldata.context,
		CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY, sizeof(win_height), 0, &err);
	assert (err == CL_SUCCESS);


	err = clEnqueueWriteBuffer(cldata.command_queue, width, CL_TRUE, 0,
		sizeof(win_width), &win_width, 0, 0, 0);
	assert (err == CL_SUCCESS);
	err = clEnqueueWriteBuffer(cldata.command_queue, height, CL_TRUE, 0,
		sizeof(win_height), &win_height, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(cldata.kernel, 0, sizeof(pixels), &pixels);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cldata.kernel, 1, sizeof(width), &width);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cldata.kernel, 2, sizeof(height), &height);
	assert (err == CL_SUCCESS);

	//getting max work group size for this task
	err = clGetKernelWorkGroupInfo(cldata.kernel, cldata.dev_id,
		CL_KERNEL_WORK_GROUP_SIZE, sizeof(cldata.local_size),
		&cldata.local_size, 0);
	assert (err == CL_SUCCESS);
	cldata.local_size = cldata.local_size > cldata.global_size ?
		cldata.global_size : cldata.local_size;
	while (cldata.global_size % cldata.local_size != 0)
		cldata.local_size -= 1;
	printf("%lu\n", cldata.local_size);

	//push task to the command queue
	err = clEnqueueNDRangeKernel(cldata.command_queue, cldata.kernel, 1, 0,
		&cldata.global_size, &cldata.local_size, 0, 0, 0);
	printf("%d\n", err);
	assert (err == CL_SUCCESS);

	//wait while the task is being processed
	clFinish(cldata.command_queue);

	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(cldata.command_queue, pixels, CL_TRUE, 0,
		sizeof(px), px, 0, 0, 0);
	assert (err == CL_SUCCESS);

	init_win(&screen);
	for(int i = 0; i < cldata.global_size; ++i)
		screen.surf_arr[i] = px[i];
	main_loop(&screen);
	close_sdl(&screen);

	return (0);
}
