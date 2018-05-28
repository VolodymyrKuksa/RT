

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
	int				pr_pl_w;
	int				pr_pl_h;
}					t_cam;

typedef struct		s_ray
{
	__float3		pos;
	__float3		dir;
}					t_ray;

typedef struct		s_quad
{
	float a;
	float b;
	float c;
	float d;
}					t_quad;

t_ray get_camera_ray(int x, int y, t_cam *cam);
float	check_sphere(t_ray ray, t_sphere sphere);

t_ray get_camera_ray(int x, int y, t_cam *cam)
{
t_ray ray;

ray.pos = cam->pos;
ray.dir = ray.pos + cam->dir * cam->f_length + cam->updir *
(cam->pr_pl_h / 2 - y) + cam->ldir * (cam->pr_pl_w / 2 - x);
ray.dir = normalize(ray.dir);
return(ray);
}

float	check_sphere(t_ray ray, t_sphere sphere)
{
	t_quad		q;
	__float3	x;

	x = ray.pos - sphere.pos;
	q.a = 2.0f;
	q.b = 2.0f * dot(ray.dir, x);
	q.c = dot(x, x) - sphere.r * sphere.r;
	if ((q.d = q.b * q.b - 2.0 * q.a * q.c) < 0)
		return (-1.0f);
	return (1.0f);
}


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
	t_ray ray = get_camera_ray(x, y, &cam);
	float t = 	check_sphere(ray, *obj);
		pixels[id] = t > 0 ? 0xff0000 : 0xffffff;
}


