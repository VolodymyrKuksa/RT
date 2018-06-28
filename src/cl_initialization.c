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

void	init_defaults(t_cldata *cl)
{
	cl->num_samples = 0;
	cl->move_keys = NOKEY;
	cl->mv_data.move_spd = 1.f;
	cl->mv_data.turn_a = 2.5;
	cl->mv_data.cosine_a = cos(DTR(cl->mv_data.turn_a));
	cl->mv_data.sine_a = sin(DTR(cl->mv_data.turn_a));
}

void	init_opencl(t_cldata *cl)
{
	int		err;

	clGetDeviceIDs(0, DEVICE_TYPE, 1, &cl->dev_id, 0);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, 0);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, 0);
	cl->source = read_file(open(KERNEL_PATH, O_RDONLY), &cl->source_size);
	cl->program = clCreateProgramWithSource(cl->context, 1,
		(const char**)(&cl->source), &cl->source_size, 0);
	err = clBuildProgram(cl->program, 0, 0, 0, 0, 0);
	if (err != CL_SUCCESS)
		print_log(cl);
	cl->kernel = clCreateKernel(cl->program, "render_pixel", 0);
	cl->global_size = g_win_height * g_win_width;
}

void	cl_setup(t_cldata *cl)
{
	cl->px_host = (cl_float3*)malloc(sizeof(cl_float3) * cl->global_size);
	cl->pixels = (cl_float3*)malloc(sizeof(cl_float3) * cl->global_size);
	cl->px_gpu = clCreateBuffer(cl->context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		sizeof(cl_float3) * g_win_width * g_win_height, 0, 0);
	cl->obj_gpu = clCreateBuffer(cl->context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_sphere) * cl->sc.num_obj, cl->sc.obj, 0);
	cl->seed_gpu = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
		sizeof(int) * cl->seeds.size, 0, 0);
	clSetKernelArg(cl->kernel, 0, sizeof(cl->px_gpu), &cl->px_gpu);
	clSetKernelArg(cl->kernel, 1, sizeof(cl->obj_gpu), &cl->obj_gpu);
	clSetKernelArg(cl->kernel, 2, sizeof(cl->sc.num_obj), &cl->sc.num_obj);
	clSetKernelArg(cl->kernel, 3, sizeof(cl->sc.cam), &cl->sc.cam);
	clSetKernelArg(cl->kernel, 4, sizeof(g_win_width), &g_win_width);
	clSetKernelArg(cl->kernel, 5, sizeof(g_win_height), &g_win_height);
	clSetKernelArg(cl->kernel, 6, sizeof(cl->seed_gpu), &cl->seed_gpu);
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
