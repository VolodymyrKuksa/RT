/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkuksa <vkuksa@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/22 16:24:00 by vkuksa            #+#    #+#             */
/*   Updated: 2018/06/22 16:24:00 by vkuksa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

extern unsigned int		g_win_width;
extern unsigned int		g_win_height;

void	cl_exec(t_cldata *cl)
{
	clEnqueueWriteBuffer(cl->command_queue, cl->seed_gpu, CL_FALSE, 0,
		sizeof(uint) * cl->seeds.size, cl->seeds.seeds, 0, 0, 0);
	clEnqueueNDRangeKernel(cl->command_queue, cl->kernel, 1, 0,
		&cl->global_size, &cl->local_size, 0, 0, 0);
	clEnqueueReadBuffer(cl->command_queue, cl->px_gpu, CL_FALSE, 0,
		sizeof(cl_float3) * g_win_width * g_win_height, cl->px_host, 0, 0, 0);
	clEnqueueReadBuffer(cl->command_queue, cl->seed_gpu, CL_FALSE, 0,
		sizeof(int) * cl->seeds.size, cl->seeds.seeds, 0, 0, 0);
	clFinish(cl->command_queue);
}
