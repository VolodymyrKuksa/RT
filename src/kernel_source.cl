__kernel void	hello_world(__global unsigned int *pixels,
	int w,
	int h)
{
	int		id = get_global_id(0);
	int		x = id % w;
	int		y = id / w;
	double	xx = double(x) / (double)w;
	double	yy = double(y) / (double)h;

	pixels[id] = (double)0x0 * (1.0 - xx) + (double)0xff * xx;
	pixels[id] = pixels[id] << 8;
	pixels[id] += (double)0x0 * (1.0 - yy) + (double)0xff * yy;
	pixels[id] = pixels[id] << 8;
}

/*__kernel void	hello_world(__global int *input, __global int *output)
{
	int		id;

	id = get_global_id(0);
	output[id] = input[id] * input[id];
}*/
