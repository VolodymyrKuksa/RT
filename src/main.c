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

//#define NDEBUG
#include <assert.h>

//absolute path if executable is not in main proj dir (ex: cmake-build-debug)
#define KERNEL_PATH "/Users/vkuksa/projects/rt/src/kernel_source.cl"

int		main(void)
{

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

	int					err;			//error code
	cl_device_id		gpu_dev;		//compute device identifier
	cl_context			context;		//context (devices to compute on)
	cl_command_queue	command_queue;	//entity to push commands
	char				*source;		//kernel source code
	size_t				source_size;	//kernel source code size
	cl_program			program;		//program built from kernel source code
	cl_kernel			kernel;			//kernel (task)
	char				buff[14];		//buffer to fill with chars
	cl_mem				mem;			//gpu memory for the buffer
	size_t				buff_len;		//buffer length
	size_t				work_group;		//max work group size

	//get first gpu device on the computer
	//0 for platform because apple already handles it
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &gpu_dev, 0);
	assert (err == CL_SUCCESS);

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

	//get size of the buffer
	buff_len = sizeof(buff);

	//allocate memory on context for the buffer
	mem = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_HOST_READ_ONLY,
		buff_len, 0, &err);
	assert (err == CL_SUCCESS);

	//set the allocated memory as an argument for __kernel function
	err = clSetKernelArg(kernel, 0, sizeof(mem), &mem);
	assert (err == CL_SUCCESS);

	//don`t bother getting max work group size for this task
	work_group = 1;

	//push task to the command queue
	err = clEnqueueNDRangeKernel(command_queue, kernel, 1, 0, &buff_len,
		&work_group, 0, 0, 0);
	assert (err == CL_SUCCESS);

	//wait while the task is being processed
	clFinish(command_queue);

	//read from the memory, filled by the current command que
	err = clEnqueueReadBuffer(command_queue, mem, CL_TRUE, 0, buff_len, buff,
		0, 0, 0);
	assert (err == CL_SUCCESS);

	//print result
	printf("%s", buff);

	return (0);
}
