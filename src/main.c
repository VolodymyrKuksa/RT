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
#define SIZE 4096

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
		SDL_WINDOWPOS_UNDEFINED, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
		if (screen->window == NULL)
		{
			ft_putstr("Window could not be created! Error: ");
			ft_putendl(SDL_GetError());
			return (0);
		}
		else
			screen->surface = SDL_GetWindowSurface(screen->window);
	}
	screen->surf_arr = (unsigned int *)screen->surface->pixels;
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
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, &err);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, &err);
	cl->source = (char**)malloc(sizeof(char*));
	*cl->source = read_file(KERNEL_PATH, &cl->source_size);
	cl->program = clCreateProgramWithSource(cl->context, 1,
		(const char **)cl->source, &cl->source_size, &err);
	err = clBuildProgram(cl->program, 0, 0, 0, 0, 0);
	cl->kernel = clCreateKernel(cl->program, "hello_world", &err);
}

int		main(void) {

	t_cldata	cldata;
	int			input[SIZE];	//input buffer
	int			output[SIZE];	//output buffer
	cl_mem		clin;			//gpu memory for input buffer
	cl_mem		clout;			//gpu memory fot output buffer
	int			err;			//error code

	init_openCL(&cldata);


	//generate random data set
	srand((unsigned) clock());
	for (int i = 0; i < SIZE; ++i) {
		input[i] = rand(); // NOLINT
	}

	//get size of the buffer
	cldata.global_size = SIZE;

	//allocate memory on context for buffers
	clin = clCreateBuffer(cldata.context,
		CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY, cldata.global_size, 0, &err);
	assert (err == CL_SUCCESS);
	clout = clCreateBuffer(cldata.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, cldata.global_size, 0, &err);
	assert (err == CL_SUCCESS);

	//write data set to the device memory
	err = clEnqueueWriteBuffer(cldata.command_queue, clin, CL_TRUE, 0,
		cldata.global_size, input, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(cldata.kernel, 0, sizeof(clin), &clin);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cldata.kernel, 1, sizeof(clout), &clout);
	assert (err == CL_SUCCESS);

	//getting max work group size for this task
	err = clGetKernelWorkGroupInfo(cldata.kernel, cldata.dev_id,
		CL_KERNEL_WORK_GROUP_SIZE, sizeof(cldata.local_size),
		&cldata.local_size, 0);
	assert (err == CL_SUCCESS);
	cldata.local_size = cldata.local_size > cldata.global_size ?
		cldata.global_size : cldata.local_size;
	printf("%lu\n", cldata.local_size);

	//push task to the command queue
	err = clEnqueueNDRangeKernel(cldata.command_queue, cldata.kernel, 1, 0,
		&cldata.global_size, &cldata.local_size, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//wait while the task is being processed
	clFinish(cldata.command_queue);

	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(cldata.command_queue, clout, CL_TRUE, 0,
		cldata.global_size, output, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//print result
	int results = 0;
	for (int i = 0; i < SIZE; ++i) {
		if (output[i] == input[i] * input[i]) {
			results++;
		}
	}
	printf("%d/%d correct results\n", results, SIZE);

	t_scrn	screen;

	init_win(&screen);
	main_loop(&screen);
	close_sdl(&screen);

	return (0);
}



/*	cl_device_id	*device_ids;
	unsigned int	devcount;

	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 0, 0, &devcount);
	device_ids = (cl_device_id*)malloc(sizeof(cl_device_id) * devcount);
	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, devcount, device_ids, 0);

	char	*name;
	name = (char*)malloc(sizeof(char) * 256);
	for (int i = 0; i < devcount; ++i) {
		clGetDeviceInfo(device_ids[i], CL_DEVICE_NAME, 256, name, 0);
		printf("%s:\n", name);
		clGetDeviceInfo(device_ids[i], CL_DEVICE_VERSION, 256, name, 0);
		i < devcount - 1 ? printf("%s\n\n", name) : printf("%s\n", name);
	}*/

	/*
	int					err;			//error code
	cl_device_id		gpu_dev;		//compute device identifier
	cl_context			context;		//context (devices to compute on)
	cl_command_queue	command_queue;	//entity to push commands
	char				*source;		//kernel source code
	size_t				source_size;	//kernel source code size
	cl_program			program;		//program built from kernel source code
	cl_kernel			kernel;			//kernel (task)
	size_t				global_size;	//global work group size
	size_t				local_size;		//local (max) work group size
	int					input[SIZE];	//input buffer
	int					output[SIZE];	//output buffer
	cl_mem				clin;			//gpu memory for input buffer
	cl_mem				clout;			//gpu memory fot output buffer

	//get first gpu device on the computer
	//0 for platform because apple already handles it
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &gpu_dev, 0);
	assert (err == CL_SUCCESS);

	cl_bool	image_support;
	err = clGetDeviceInfo(gpu_dev, CL_DEVICE_IMAGE_SUPPORT,
		sizeof(image_support), &image_support, 0);
	assert (err == CL_SUCCESS);
	if (image_support)
		printf("Images supported!\n");
	else
		printf("Images not supported(\n");

	//create context with all devices which have to work on the task
	context = clCreateContext(0, 1, &gpu_dev, 0, 0, &err);
	assert (err == CL_SUCCESS);

	//create command queue entity to be able to push tasks to the contest
	command_queue = clCreateCommandQueue(context, gpu_dev, 0, &err);
	assert (err == CL_SUCCESS);

	//read kernel source code and it`s size
	source = read_file(KERNEL_PATH, &source_size);
	assert(source && source_size > 0);

	//create program on context with given source code
	program = clCreateProgramWithSource(context, 1, (const char **)&source,
		&source_size, &err);
	assert (err == CL_SUCCESS);

	//build the program with no compilation parameters
	err = clBuildProgram(program, 0, 0, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//create kernel (task) out of the successfully built program
	kernel = clCreateKernel(program, "hello_world", &err);
	assert (err == CL_SUCCESS);

	//generate random data set
	srand((unsigned)clock());
	for (int i = 0; i < SIZE; ++i) {
		input[i] = rand(); // NOLINT
	}

	//get size of the buffer
	global_size = sizeof(input);

	//allocate memory on context for buffers
	clin = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_HOST_WRITE_ONLY,
		global_size, 0, &err);
	assert (err == CL_SUCCESS);
	clout = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		global_size, 0, &err);
	assert (err == CL_SUCCESS);

	//write data set to the device memory
	err = clEnqueueWriteBuffer(command_queue, clin, CL_TRUE, 0, global_size,
		input, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(kernel, 0, sizeof(clin), &clin);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(kernel, 1, sizeof(clout), &clout);
	assert (err == CL_SUCCESS);

	//getting max work group size for this task
	err = clGetKernelWorkGroupInfo(kernel, gpu_dev, CL_KERNEL_WORK_GROUP_SIZE,
		sizeof(local_size), &local_size, 0);
	assert (err == CL_SUCCESS);
	local_size = local_size > global_size ? global_size : local_size;
	printf("%lu\n", local_size);

	//push task to the command queue
	err = clEnqueueNDRangeKernel(command_queue, kernel, 1, 0, &global_size,
		&local_size, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//wait while the task is being processed
	clFinish(command_queue);

	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(command_queue, clout, CL_TRUE, 0, global_size,
		output, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//print result
	int results = 0;
	for(int i = 0; i < SIZE; ++i)
	{
		if (output[i] == input[i] * input[i])
			results++;
	}
	printf("%d/%d correct results\n", results, SIZE);

	return (0);
}
