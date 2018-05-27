__kernel void	hello_world(__global unsigned int *pixels,
	__global int *width,
	__global int *height)
{
	int		id;

	id = get_global_id(0);
	pixels[id] = id;
}

/*__kernel void	hello_world(__global int *input, __global int *output)
{
	int		id;

	id = get_global_id(0);
	output[id] = input[id] * input[id];
}*/
