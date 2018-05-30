__constant float EPSILON = 0.00003f;
__constant float PI = 3.14159265359f;

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
float	check_sphere(t_ray *ray, t_sphere sphere);
static float get_random(uint2 *seeds);
float	solve_quad(t_quad q);
float3	sphere_normal_point(float3 pt, t_sphere sphere);
float3	sphere_normal_ray(t_ray r, t_sphere sphere, float t);
float	get_intersection(t_ray *ray, __global t_sphere *obj, int num_obj, int *id);
float3	get_random_float3(uint2 *seeds);
float3	trace_ray(t_ray ray, __global t_sphere *obj, int num_obj, uint2 *seeds);


t_ray get_camera_ray(int x, int y, t_cam *cam)
{
	t_ray ray;

//	ray.pos = cam->pos;
//	ray.dir = ray.pos + cam->dir * cam->f_length + cam->updir *
//	(cam->pr_pl_h / 2 - y) + cam->ldir * (cam->pr_pl_w / 2 - x);
//	ray.dir = normalize(ray.dir);
	ray.pos = (float3)(0,0,0);
	ray.dir = normalize((float3)(x - cam->pr_pl_w / 2,-y + cam->pr_pl_h / 2,-cam->f_length));
	return(ray);
}

float3	sphere_normal_point(float3 pt, t_sphere sphere)
{
	return (normalize(pt - sphere.pos));
}

float3	sphere_normal_ray(t_ray r, t_sphere sphere, float t)
{
	float3	intersect;
	float3	n;

	intersect = r.pos + t * r.dir;
	n = sphere_normal_point(intersect, sphere);
	return (dot(n, r.dir) > 0 ? -1 * n : n);
}

float	solve_quad(t_quad q)
{
	float	t1;
	float	t2;

	t1 = (-q.b - sqrt(q.d)) / q.a;
	t2 = (-q.b + sqrt(q.d)) / q.a;
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (t1);
	if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		return (t2);
	return (-1);
}

float	check_sphere(t_ray *ray, t_sphere sphere)
{
	t_quad		q;
	__float3	x;

	x = ray->pos - sphere.pos;
	q.a = 2.0f;
	q.b = 2.0f * dot(ray->dir, x);
	q.c = dot(x, x) - sphere.r * sphere.r;
	if ((q.d = q.b * q.b - 2.0 * q.a * q.c) < 0)
		return (-1.0f);
	return (solve_quad(q));
}

static float get_random(uint2 *seeds)
{
	/* hash the seeds using bitwise AND operations and bitshifts */
	seeds->x = 36969 * ((seeds->x) & 65535) + ((seeds->x) >> 16);
	seeds->y = 18000 * ((seeds->y) & 65535) + ((seeds->y) >> 16);

	unsigned int ires = ((seeds->x) << 16) + (seeds->y);

	/* use union struct to convert int to float */
	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

float3	get_random_float3(uint2 *seeds)
{
	float3	new_vec;
	new_vec.x = get_random(seeds);
	new_vec.y = get_random(seeds);
	new_vec.z = get_random(seeds);

	return new_vec;
}

//colors are represented as float3, where x - red, y - green, z - blue

float	get_intersection(t_ray *ray, __global t_sphere *obj, int num_obj, int *id)
{
	float	t = -1;
	float	tmp = -1;
	for(int i = 0; i < num_obj; ++i)
	{
		tmp = check_sphere(ray, obj[i]);
		if ((t < 0 && tmp > 0) || (tmp < t && tmp > 0))
		{
			t = tmp;
			*id = i;
		}
	}
	return t;
}

float3	trace_ray(t_ray ray, __global t_sphere *obj, int num_obj, uint2 *seeds)
{
	float3	accum_col = (float3)(0,0,0); //accumulated color
	float3	col_mask = (float3)(1,1,1); //colour mask
	for(int	bounce = 0; bounce < 8; ++bounce)
	{
		int obj_id = 0;
		float t = get_intersection(&ray, obj, num_obj, &obj_id);
		if (t < 0)
			break;

		float3	hitpoint = ray.pos + t * ray.dir;
		float3	n = sphere_normal_point(hitpoint, obj[obj_id]);
		n = dot(n, ray.dir) > 0 ? -1 * n : n;

		float	rand1 = 2.0f * PI * get_random(seeds);
		float	rand2 = get_random(seeds);
		float	rand2s = sqrt(rand2);

		float3	axis = fabs(n.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
		float3 u = normalize(cross(axis, n));
		float3 v = cross(n, u);

		ray.dir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + n*sqrt(1.0f - rand2));
		ray.pos = hitpoint + n * (EPSILON * 3);

		accum_col += col_mask * obj[obj_id].emission;
		if (obj[obj_id].emission.x > 0 || obj[obj_id].emission.y > 0 || obj[obj_id].emission.z > 0)
		break;
		col_mask *= obj[obj_id].col;
		col_mask *= dot(n, ray.dir);
	}
	return accum_col;
}

__kernel void	render_pixel(
	__global float3 *pixels,
	__global t_sphere *obj,
	int num_obj,
	t_cam cam,
	int w,
	int h,
	__global unsigned int *seed)
{
	int		id = get_global_id(0);
	int		x = id % w;
	int		y = id / w;
	uint2	seeds;
	seeds.x = seed[id];
	seeds.y = seed[id + w * h];
	t_ray ray = get_camera_ray(x, y, &cam);
	pixels[id] = (float3)(0,0,0);
//	int		max_sample = 100;
//	float	sample_influence = 1.0f / max_sample;
//	for(int samples = 0; samples < max_sample; ++samples)
	pixels[id] += trace_ray(ray, obj, num_obj, &seeds);
	seed[id] = seeds.x;
	seed[id + w * h] = seeds.y;
}



/*
int		obj_id = 0;
float t = get_intersection(&ray, obj, num_obj, &obj_id);
if (t <= 0.0f)
{
pixels[id] = get_random_float3(&seeds);
pixels[id] = normalize(pixels[id]) * 0.6f;
return ;
}
float3	n = sphere_normal(ray, obj[obj_id], t);
float3	light_vec = normalize((float3)(1,1,1));
float	res = dot(n, light_vec);
pixels[id] = res > 0 ? obj[obj_id].col * res : 0;
*/