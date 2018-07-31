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

void	init_seeds(t_seeds *s)
{
	size_t		i;

	s->size = (uint)(g_win_height * g_win_width * 2);
	s->seeds = (uint*)malloc(sizeof(uint) * s->size);
	srand((uint)clock());
	i = 0;
	while (i < s->size)
		s->seeds[i++] = (uint)rand();
}

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
	env->client.active = 0;
	env->server.active = 0;
}

void	choose_device(t_cldata *cl)
{
	cl_device_id		*dev_ids;
	unsigned int		i;
	unsigned int		dev_count;
	char				buff[256];
	cl_device_fp_config	tmp;

	clGetDeviceIDs(0, DEVICE_TYPE, 0, 0, &dev_count);
	dev_ids = (cl_device_id*)malloc(sizeof(cl_device_id) * dev_count);
	clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, dev_count, dev_ids, 0);
	cl->dev_id = NULL;
	i = 0;
	while (i < dev_count)
	{
		clGetDeviceInfo(dev_ids[i], CL_DEVICE_DOUBLE_FP_CONFIG, sizeof(tmp),
			&tmp, 0);
		if (tmp & (CL_FP_FMA | CL_FP_ROUND_TO_NEAREST | CL_FP_ROUND_TO_ZERO |
			CL_FP_ROUND_TO_INF | CL_FP_INF_NAN | CL_FP_DENORM))
			cl->dev_id = dev_ids[i];
		i++;
	}
	bzero(buff, 256);
	clGetDeviceInfo(cl->dev_id, CL_DEVICE_NAME, 255, buff, 0);
	ft_putendl(buff);
	free(dev_ids);
	if (!cl->dev_id)
		put_error("Could not choose gpu device");
}

void	init_opencl(t_cldata *cl)
{
	choose_device(cl);
	cl->context = clCreateContext(0, 1, &cl->dev_id, 0, 0, 0);
	cl->command_queue = clCreateCommandQueue(cl->context, cl->dev_id, 0, 0);
	cl->source[0] = read_file(open(KERNEL_PATH0, O_RDONLY), 0);
	cl->source[1] = read_file(open(KERNEL_PATH1, O_RDONLY), 0);
	cl->source[2] = read_file(open(KERNEL_PATH2, O_RDONLY), 0);
	cl->source[3] = read_file(open(KERNEL_PATH3, O_RDONLY), 0);
	cl->program = clCreateProgramWithSource(cl->context, 4,
		(const char**)(&cl->source), 0, 0);
	cl->pr_intersect = clCreateProgramWithSource(cl->context, 4,
		(const char**)(&cl->source), 0, 0);
	free(cl->source[0]);
	free(cl->source[1]);
	free(cl->source[2]);
	free(cl->source[3]);
	if (clBuildProgram(cl->program, 0, 0, KERNEL_INC_DIR, 0, 0))
		print_log(cl);
	if (clBuildProgram(cl->pr_intersect, 0, 0, KERNEL_INC_DIR, 0, 0))
		print_log(cl);
	cl->kernel = clCreateKernel(cl->program, "render_pixel", 0);
	cl->kr_intersect = clCreateKernel(cl->program, "get_mouse_intersect", 0);
	cl->global_size = g_win_height * g_win_width;
	pthread_mutex_init(&cl->pixel_lock, NULL);
}

void	cl_set_args(t_env *e)
{
	clSetKernelArg(e->cl.kernel, 0, sizeof(e->cl.px_gpu), &e->cl.px_gpu);
	clSetKernelArg(e->cl.kernel, 1, sizeof(e->cl.obj_gpu), &e->cl.obj_gpu);
	clSetKernelArg(e->cl.kernel, 2, sizeof(e->scene.num_obj),
		&e->scene.num_obj);
	clSetKernelArg(e->cl.kernel, 3, sizeof(e->scene.cam), &e->scene.cam);
	clSetKernelArg(e->cl.kernel, 4, sizeof(g_win_width), &g_win_width);
	clSetKernelArg(e->cl.kernel, 5, sizeof(g_win_height), &g_win_height);
	clSetKernelArg(e->cl.kernel, 6, sizeof(e->cl.seed_gpu), &e->cl.seed_gpu);
	clSetKernelArg(e->cl.kernel, 7, sizeof(e->cl.tx_gpu), &e->cl.tx_gpu);
	clSetKernelArg(e->cl.kernel, 8, sizeof(e->cl.txdata_gpu),
		&e->cl.txdata_gpu);
	clSetKernelArg(e->cl.kernel, 9, sizeof(e->textures.tx_count),
		&e->textures.tx_count);
	clSetKernelArg(e->cl.kr_intersect, 2, sizeof(e->cl.obj_gpu),
		&e->cl.obj_gpu);
	clSetKernelArg(e->cl.kr_intersect, 3, sizeof(e->scene.num_obj),
		&e->scene.num_obj);
	clSetKernelArg(e->cl.kr_intersect, 4, sizeof(e->scene.cam), &e->scene.cam);
	clSetKernelArg(e->cl.kr_intersect, 5, sizeof(e->cl.id_gpu), &e->cl.id_gpu);
}

void	cl_setup(t_env *e)
{
	e->cl.id_host = (int*)malloc(sizeof(int));
	e->cl.px_host = (cl_float3*)malloc(sizeof(cl_float3) * e->cl.global_size);
	e->cl.pixels = (cl_float3*)malloc(sizeof(cl_float3) * e->cl.global_size);
	e->cl.id_gpu = clCreateBuffer(e->cl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY, sizeof(int), 0, 0);
	e->cl.px_gpu = clCreateBuffer(e->cl.context,
		CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		sizeof(cl_float3) * g_win_width * g_win_height, 0, 0);
	e->cl.obj_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_obj) * e->scene.num_obj, e->scene.obj, 0);
	e->cl.seed_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_WRITE,
		sizeof(int) * e->cl.seeds.size, 0, 0);
	e->cl.tx_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_rgb) * e->textures.total_size, e->textures.tx, 0);
	e->cl.txdata_gpu = clCreateBuffer(e->cl.context, CL_MEM_READ_ONLY |
		CL_MEM_HOST_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(t_txdata) * e->textures.tx_count, e->textures.txdata, 0);
	cl_set_args(e);
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
