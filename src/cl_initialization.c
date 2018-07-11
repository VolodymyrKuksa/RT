/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 16:01:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/22 16:01:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "rt.h"

extern unsigned int		g_win_width;
extern unsigned int		g_win_height;

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
}

void	init_opencl(t_cldata *cl)
{
	int		err;

	clGetDeviceIDs(0, DEVICE_TYPE, 1, &cl->dev_id, 0);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, 0);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, 0);
	cl->source[0] = read_file(open(KERNEL_PATH0, O_RDONLY), 0);
	cl->source[1] = read_file(open(KERNEL_PATH1, O_RDONLY), 0);
	cl->program = clCreateProgramWithSource(cl->context, 2,
		(const char**)(&cl->source), 0, 0);
	err = clBuildProgram(cl->program, 0, 0, KERNEL_INC_DIR, 0, 0);
	if (err != CL_SUCCESS)
	{
		printf("%d\n", err);
		print_log(cl);
	}
	cl->kernel = clCreateKernel(cl->program, "render_pixel", 0);
	cl->global_size = g_win_height * g_win_width;
}

void	cl_setup(t_env *e)
{
	e->cl.px_host = (cl_float3*)malloc(sizeof(cl_float3) * e->cl.global_size);
	e->cl.pixels = (cl_float3*)malloc(sizeof(cl_float3) * e->cl.global_size);
	e->cl.px_gpu = clCreateBuffer(e->cl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		sizeof(cl_float3) * g_win_width * g_win_height, 0, 0);
	e->cl.obj_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_obj) * e->sc.num_obj, e->sc.obj, 0);
	e->cl.seed_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_WRITE,
		sizeof(int) * e->cl.seeds.size, 0, 0);

	int		err;

	compress_texture(&e->textures);
	e->cl.tx_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_rgb) * e->textures.total_size, e->textures.tx, &err);
//	printf("err: %d\n", err);
	assert(err == CL_SUCCESS || err == CL_INVALID_HOST_PTR);	//might throw CL_OUT_OF_HOST_MEMORY
	e->cl.txdata_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_txdata) * e->textures.tx_count, e->textures.txdata, &err);
	assert(err == CL_SUCCESS || err == CL_INVALID_HOST_PTR);

	clSetKernelArg(e->cl.kernel, 0, sizeof(e->cl.px_gpu), &e->cl.px_gpu);
	clSetKernelArg(e->cl.kernel, 1, sizeof(e->cl.obj_gpu), &e->cl.obj_gpu);
	clSetKernelArg(e->cl.kernel, 2, sizeof(e->sc.num_obj), &e->sc.num_obj);
	clSetKernelArg(e->cl.kernel, 3, sizeof(e->sc.cam), &e->sc.cam);
	clSetKernelArg(e->cl.kernel, 4, sizeof(g_win_width), &g_win_width);
	clSetKernelArg(e->cl.kernel, 5, sizeof(g_win_height), &g_win_height);
	clSetKernelArg(e->cl.kernel, 6, sizeof(e->cl.seed_gpu), &e->cl.seed_gpu);
	clSetKernelArg(e->cl.kernel, 7, sizeof(e->cl.tx_gpu), &e->cl.tx_gpu);
	clSetKernelArg(e->cl.kernel, 8, sizeof(e->cl.txdata_gpu), &e->cl.txdata_gpu);
	clSetKernelArg(e->cl.kernel, 9, sizeof(e->textures.tx_count), &e->textures.tx_count);
}

void	get_work_group_size(t_cldata *cl)
{
	clGetKernelWorkGroupInfo(cl->kernel, cl->dev_id, CL_KERNEL_WORK_GROUP_SIZE,
		sizeof(cl->local_size), &(cl->local_size), 0);
	cl->local_size = cl->local_size > cl->global_size ?
		cl->global_size : cl->local_size;
	while (cl->global_size % cl->local_size != 0)
		cl->local_size -= 1;
}
