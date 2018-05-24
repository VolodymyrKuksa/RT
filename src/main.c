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

int		main(void)
{

	cl_device_id	device_id;

	if (clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 1, &device_id, 0))
	{
		printf("failed to get device ids\n");
		exit (EXIT_FAILURE);
	}

	char	*name;
	name = (char*)malloc(sizeof(char) * 256);
	clGetDeviceInfo(device_id, CL_DEVICE_NAME, 256, name, 0);
	printf("%s\n", name);

	return (0);


}