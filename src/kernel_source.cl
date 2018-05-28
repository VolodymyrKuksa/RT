typedef struct		s_sphere
{
	__float3		col;
	__float3		pos;
	__float3		emission;
	float			r;
}					t_sphere;


typedef struct		s_cam
{
	__float3		pos;
	__float3		dir;
	__float3		updir;
	__float3		ldir;
	float			f_length;
	float			aperture;
}					t_cam;



__kernel void	hello_world(__global unsigned int *pixels,
	__global t_sphere *obj,
	int num_obj,
	t_cam cam,
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

	if (cam.pos.x == 0 && cam.pos.y == 0 && cam.pos.z == 50)
		pixels[id] = 0xffffff;
}
