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

#ifdef CLION_BUILD
#define KERNEL_PATH "../src/kernel_source.cl"
#else
#define KERNEL_PATH "src/kernel_source.cl"
#endif

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

void	clamp(cl_float3 *px)
{
	px->x = px->x > 1.f ? 1.f : px->x;
	px->y = px->y > 1.f ? 1.f : px->y;
	px->z = px->z > 1.f ? 1.f : px->z;
}

void update_window(cl_float3 *pixels, cl_float3 *px_host, t_scrn *screen, int global_size)
{
	static int num_samples;
	float sample_influence;

	++num_samples;
	sample_influence = (1.0f / num_samples);
	for(int i = 0; i < global_size; ++i)
	{
		pixels[i].x *= 1.0f - sample_influence;
		pixels[i].y *= 1.0f - sample_influence;
		pixels[i].z *= 1.0f - sample_influence;

		pixels[i].x += px_host[i].x * sample_influence;
		pixels[i].y += px_host[i].y * sample_influence;
		pixels[i].z += px_host[i].z * sample_influence;
		clamp(pixels + i);
		screen->surf_arr[i].bgra[0] = (u_char) (pixels[i].z * 0xff);
		screen->surf_arr[i].bgra[1] = (u_char) (pixels[i].y * 0xff);
		screen->surf_arr[i].bgra[2] = (u_char) (pixels[i].x * 0xff);
	}
	printf("samples: %u, influence: %f\n", num_samples, sample_influence);
	SDL_UpdateWindowSurface(screen->window);
}

void	cl_setup(t_cldata *cl)
{
	int			err;

	cl->px_host = (cl_float3*)malloc(sizeof(cl_float3) * cl->global_size);
	cl->pixels = (cl_float3*)malloc(sizeof(cl_float3) * cl->global_size);

	//allocate memory on context for buffers
	cl->px_gpu = clCreateBuffer(cl->context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		sizeof(cl_float3) * g_win_width * g_win_height, 0, &err);
	assert (err == CL_SUCCESS);
	cl->obj_gpu = clCreateBuffer(cl->context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_NO_ACCESS | CL_MEM_COPY_HOST_PTR,
		sizeof(t_sphere) * cl->sc.num_obj, cl->sc.obj, &err);
	assert (err == CL_SUCCESS);
	cl->seed_gpu = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(int) * cl->seeds.size, 0, &err);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(cl->kernel, 0, sizeof(cl->px_gpu), &cl->px_gpu);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl->kernel, 1, sizeof(cl->obj_gpu), &cl->obj_gpu);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl->kernel, 2, sizeof(cl->sc.num_obj), &cl->sc.num_obj);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl->kernel, 3, sizeof(cl->sc.cam), &cl->sc.cam);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl->kernel, 4, sizeof(g_win_width), &g_win_width);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl->kernel, 5, sizeof(g_win_height), &g_win_height);
	assert (err == CL_SUCCESS);
	err = clSetKernelArg(cl->kernel, 6, sizeof(cl->seed_gpu), &cl->seed_gpu);
	assert (err == CL_SUCCESS);
}

void	cl_exec(t_cldata *cl)
{
	int err;

	err = clEnqueueWriteBuffer(cl->command_queue, cl->seed_gpu, CL_TRUE, 0,
		sizeof(uint) * cl->seeds.size, cl->seeds.seeds, 0, 0, 0);
	assert(err == CL_SUCCESS);
	//push task to the command queue
	err = clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0,
		&cl->global_size, &cl->local_size, 0, 0, 0);
	assert (err == CL_SUCCESS);
	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(cl->command_queue, cl->px_gpu, CL_FALSE, 0,
		sizeof(cl_float3) * g_win_width * g_win_height, cl->px_host, 0, 0, 0);
	assert (err == CL_SUCCESS);
	err = clEnqueueReadBuffer(cl->command_queue, cl->seed_gpu, CL_FALSE, 0,
		sizeof(int) * cl->seeds.size, cl->seeds.seeds, 0, 0, 0);
	assert (err == CL_SUCCESS);
	clFinish(cl->command_queue);
}

void	main_loop(t_scrn *screen, t_cldata *cl)
{
	SDL_Event	e;
	int			quit;

	cl_setup(cl);
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
		cl_exec(cl);
		update_window(cl->pixels, cl->px_host,screen, (int)cl->global_size);
	}
}

void				print_log(t_cldata *cl)
{
	int				err;
	char			*build_log;
	size_t 			size;

	err = clGetProgramBuildInfo(cl->program, cl->dev_id, CL_PROGRAM_BUILD_LOG,
		0, 0, &size);
	assert(err == CL_SUCCESS);
	build_log = (char*)malloc(sizeof(char) * size);
	err = clGetProgramBuildInfo(cl->program, cl->dev_id, CL_PROGRAM_BUILD_LOG,
		size, build_log, 0);
	assert(err == CL_SUCCESS);
	write(1, build_log, ft_strlen(build_log));
	exit(EXIT_FAILURE);
}


void	init_openCL(t_cldata *cl)
{
	int		err;
	char	*options;

	options = "";//"-Werror";
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &cl->dev_id, 0);
	assert (err == CL_SUCCESS);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, &err);
	assert (err == CL_SUCCESS);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, &err);
	assert (err == CL_SUCCESS);
	cl->source = read_file(open(KERNEL_PATH, O_RDONLY), &cl->source_size);
	assert(NULL != cl->source);
	cl->program = clCreateProgramWithSource(cl->context, 1,
			(const char**)(&cl->source), &cl->source_size, &err);
	assert (err == CL_SUCCESS);
	err = clBuildProgram(cl->program, 0, 0, options, 0, 0);
	if (err != CL_SUCCESS)
		print_log(cl);
	cl->kernel = clCreateKernel(cl->program, "render_pixel", &err);
	assert (err == CL_SUCCESS);
	cl->global_size = g_win_height * g_win_width;
}

void get_work_group_size(t_cldata *cl)
{
	int err;

	err = clGetKernelWorkGroupInfo(cl->kernel, cl->dev_id,
	CL_KERNEL_WORK_GROUP_SIZE, sizeof(cl->local_size), &(cl->local_size), 0);
	cl->local_size = cl->local_size > cl->global_size ?
	cl->global_size : cl->local_size;
	while (cl->global_size % cl->local_size != 0)
		cl->local_size -= 1;
	assert (err == CL_SUCCESS);
}

int		main(void)
{
	t_cldata	cl;
	t_scrn		screen;

	init_openCL(&cl);
	init_scene(&cl.sc);
	init_seeds(&cl.seeds);
	//getting max work group size for this task
	get_work_group_size(&cl);
	init_win(&screen);
	main_loop(&screen, &cl);
	close_sdl(&screen);

	return (0);
}
