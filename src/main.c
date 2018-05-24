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

#define DEBUG
#include <assert.h>


int		main(void)
{

	cl_device_id	*device_ids;
	unsigned int	devcount;
	int				err;

	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_ALL, 0, 0, &devcount);
	assert(err == CL_SUCCESS);
	device_ids = (cl_device_id*)malloc(sizeof(cl_device_id) * devcount);
	err = clGetDeviceIDs(0, CL_DEVICE_TYPE_ALL, devcount, device_ids, 0);
	assert(err == CL_SUCCESS);

	char	*name;
	name = (char*)malloc(sizeof(char) * 256);
	for (int i = 0; i < devcount; ++i) {
		clGetDeviceInfo(device_ids[i], CL_DEVICE_NAME, 256, name, 0);
		printf("%s:\n", name);
		clGetDeviceInfo(device_ids[i], CL_DEVICE_VERSION, 256, name, 0);
		i < devcount - 1 ? printf("%s\n\n", name) : printf("%s\n", name);
	}

	return (0);
}
