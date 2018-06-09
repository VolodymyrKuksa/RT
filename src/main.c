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
/* Инклудим необходимую хню */
#include "rt.h"
#include <assert.h>
#include <time.h>
/* Это прикол в ебучем слионе*/
#ifdef CLION_BUILD
#define KERNEL_PATH "../src/kernel_source.cl"
#else
#define KERNEL_PATH "src/kernel_source.cl"
#endif
/* Это размеры окна */
unsigned int	g_win_width = 1080;
unsigned int	g_win_height = 720;


void	init_seeds(t_seeds *s) /* I don't understand WTF */
{
	int		i;

	s->size = (uint)(g_win_height * g_win_width * 2);
	s->seeds = (uint*)malloc(sizeof(uint) * s->size);
	srand((uint)clock());
	i = -1;
	while (++i < s->size)
		s->seeds[i] = (uint)rand(); // NOLINT
}


void	main_loop(t_scrn *screen, t_cldata *cl, t_scene *scene, t_seeds *seeds_host) /* This is shit */
{
	SDL_Event	e;
	int			quit;
	cl_float3	*px_host;
	cl_float3	*pixels;
	int			err;
	cl_mem		px_gpu;
	cl_mem		obj_gpu;
	cl_mem		seed_gpu;
	uint		num_samples = 1;
	float		sample_influence;

	px_host = (cl_float3*)malloc(sizeof(cl_float3) * cl->global_size);
	pixels = (cl_float3*)malloc(sizeof(cl_float3) * cl->global_size);

	//allocate memory on context for buffers
	px_gpu = clCreateBuffer(cl->context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		sizeof(cl_float3) * g_win_width * g_win_height, 0, &err);
	assert (err == CL_SUCCESS);
	obj_gpu = clCreateBuffer(cl->context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
		sizeof(t_sphere) * scene->num_obj, scene->obj, &err);
	assert (err == CL_SUCCESS);
	seed_gpu = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(int) * seeds_host->size, 0, &err);
	assert (err == CL_SUCCESS);

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

		err = clEnqueueWriteBuffer(cl->command_queue, seed_gpu, CL_TRUE, 0,
			sizeof(uint) * seeds_host->size, seeds_host->seeds, 0, 0, 0);
		assert(err == CL_SUCCESS);

		//set the allocated memory as an argument for __kernel function
		err = clSetKernelArg(cl->kernel, 0, sizeof(px_gpu), &px_gpu);
		assert (err == CL_SUCCESS);
		err = clSetKernelArg(cl->kernel, 1, sizeof(obj_gpu), &obj_gpu);
		assert (err == CL_SUCCESS);
		err = clSetKernelArg(cl->kernel, 2, sizeof(scene->num_obj), &scene->num_obj);
		assert (err == CL_SUCCESS);
		err = clSetKernelArg(cl->kernel, 3, sizeof(scene->cam), &scene->cam);
		assert (err == CL_SUCCESS);
		err = clSetKernelArg(cl->kernel, 4, sizeof(g_win_width), &g_win_width);
		assert (err == CL_SUCCESS);
		err = clSetKernelArg(cl->kernel, 5, sizeof(g_win_height), &g_win_height);
		assert (err == CL_SUCCESS);
		err = clSetKernelArg(cl->kernel, 6, sizeof(seed_gpu), &seed_gpu);
		assert (err == CL_SUCCESS);

		//push task to the command queue
		err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0,
			&cl->global_size, &cl->local_size, 0, 0, 0);
		assert (err == CL_SUCCESS);

		//read from the memory, filled by the current command que
		err = clEnqueueReadBuffer(cl->command_queue, px_gpu, CL_FALSE, 0,
			sizeof(cl_float3) * g_win_width * g_win_height, px_host, 0, 0, 0);
		assert (err == CL_SUCCESS);
		err = clEnqueueReadBuffer(cl->command_queue, seed_gpu, CL_FALSE, 0,
			sizeof(int) * seeds_host->size, seeds_host->seeds, 0, 0, 0);
		assert (err == CL_SUCCESS);

		clFinish(cl->command_queue);

		sample_influence = (1.0f / num_samples);

		for(int i = 0; i < cl->global_size; ++i)
		{
//			pixels[i].x *= 1.0f - sample_influence;
//			pixels[i].y *= 1.0f - sample_influence;
//			pixels[i].z *= 1.0f - sample_influence;
//
//			pixels[i].x += px_host[i].x * sample_influence;
//			pixels[i].y += px_host[i].y * sample_influence;
//			pixels[i].z += px_host[i].z * sample_influence;

//			if (px_host[i].x || px_host[i].y || px_host[i].z) {
				pixels[i].x = (pixels[i].x * (num_samples - 1) + px_host[i].x) /
							  num_samples;
				pixels[i].y = (pixels[i].y * (num_samples - 1) + px_host[i].y) /
							  num_samples;
				pixels[i].z = (pixels[i].z * (num_samples - 1) + px_host[i].z) /
							  num_samples;
//			}


			screen->surf_arr[i].bgra[0] = (u_char) (pixels[i].z * 0xff);
			screen->surf_arr[i].bgra[1] = (u_char) (pixels[i].y * 0xff);
			screen->surf_arr[i].bgra[2] = (u_char) (pixels[i].x * 0xff);


//			screen->surf_arr[i].bgra[0] *= 1.0f - sample_influence;
//			screen->surf_arr[i].bgra[1] *= 1.0f - sample_influence;
//			screen->surf_arr[i].bgra[2] *= 1.0f - sample_influence;
//
//			screen->surf_arr[i].bgra[0] += (u_char) (px_host[i].z * sample_influence * 0xff);
//			screen->surf_arr[i].bgra[1] += (u_char) (px_host[i].y * sample_influence * 0xff);
//			screen->surf_arr[i].bgra[2] += (u_char) (px_host[i].x * sample_influence * 0xff);
		}
//		printf("%d\n", *(seeds_host->seeds));
		printf("samples: %u, influence: %f\n", num_samples, sample_influence);
		num_samples++;

		SDL_UpdateWindowSurface(screen->window);
	}
}

void				print_log(t_cldata *cl)
{
	int				err;
	char			build_log[4096];

	err = clGetProgramBuildInfo(cl->program, cl->dev_id, CL_PROGRAM_BUILD_LOG,
		4096, build_log, 0);
	assert(err == CL_SUCCESS);
	printf("%s\n", build_log);
	exit(EXIT_FAILURE);
}

void	init_openCL(t_cldata *cl)
{
	int		err;
	char	*options;

	options = "-Werror";
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &cl->dev_id, 0); // SO DEVICE CPU or GPU
	assert (err == CL_SUCCESS);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, &err);
	assert (err == CL_SUCCESS);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, &err);
	assert (err == CL_SUCCESS);
	cl->source = read_file(open(KERNEL_PATH, O_RDONLY), &cl->source_size);
	assert(NULL != cl->source);
	cl->program = clCreateProgramWithSource(cl->context, 1,
		&cl->source, &cl->source_size, &err);
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

int		main(void)
{
	t_cldata	cl;
	t_seeds		seeds_host;
	int	err;
	t_scrn		screen;
	t_scene		scene;

	init_openCL(&cl);
	init_scene(&scene);
	init_seeds(&seeds_host); /* WTF ??????*/
	/*Sooo global_size it's all pixels but I need more inf*/
	cl.global_size = g_win_height * g_win_width;
	//getting max work group size for this task fuck you
	err = clGetKernelWorkGroupInfo(cl.kernel, cl.dev_id,
		CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl.local_size),
		&cl.local_size, 0);
	assert (err == CL_SUCCESS);
	cl.local_size = cl.local_size > cl.global_size ?
		cl.global_size : cl.local_size;
	while (cl.global_size % cl.local_size != 0) /*WTF ?????????*/
		cl.local_size -= 1;
	init_win(&screen);
	main_loop(&screen, &cl, &scene, &seeds_host);
	close_sdl(&screen);

	return (0);
}
