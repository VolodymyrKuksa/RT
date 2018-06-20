__constant float EPSILON = 0.001;
__constant float PI = 3.14159265359f;
__constant int max_bounces = 10;


typedef struct		s_surf
{
	float3		type;
	float			roughness;
}					t_surf;

typedef struct		s_sphere
{
	__float3		col;
	__float3		pos;
	__float3		emission;
	float			r;
	t_surf			surf;
}					t_sphere;


typedef struct		s_cam
{
	__float3		pos;
	__float3		dir;
	__float3		updir;
	__float3		ldir;
	float			f_length;
	float			aperture;
	float			ratio;
	float			pr_pl_w;
	float			pr_pl_h;
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


t_ray get_camera_ray(int x, int y, t_cam *cam, uint2 *seeds);
float	check_sphere(t_ray *ray, t_sphere sphere);
static float get_random(uint2 *seeds);
float	solve_quad(t_quad q);
float3	sphere_normal_point(float3 pt, t_sphere sphere);
float3	sphere_normal_ray(t_ray r, t_sphere sphere, float t);
float	get_intersection(t_ray *ray, __global t_sphere *obj, int num_obj, int *id);
float3	get_random_float3(uint2 *seeds);
float3	trace_ray(t_ray ray, __global t_sphere *obj, int num_obj, uint2 *seeds);
t_ray	diffuse(t_ray ray, float3 n, float3 hitpoint, uint2 *seeds);
t_ray	reflect(t_ray ray, float3 n, float3 hitpoint, t_sphere hitsphere, uint2 *seeds);
float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds);


t_ray get_camera_ray(int x, int y, t_cam *cam, uint2 *seeds)
{
	t_ray ray;

	float a = get_random(seeds) * 2 * PI;
	float r = sqrt(get_random(seeds) * cam->aperture);

	float ax = r * cos(a);
	float ay = r * sin(a);

	ray.pos = (float3)(ax,ay,0);

	ray.dir = (float3)(x - cam->pr_pl_w / 2,-y + cam->pr_pl_h / 2,-cam->f_length);
	ray.dir.x = (ray.dir.x + get_random(seeds) - 0.5f) * cam->ratio;
	ray.dir.y = (ray.dir.y + get_random(seeds) - 0.5f) * cam->ratio;
	ray.dir -= ray.pos;
	ray.dir = normalize(ray.dir);
	return(ray);
}

float3	sphere_normal_point(float3 pt, t_sphere sphere)
{
	return (normalize(pt - sphere.pos));
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

float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds)
{
	float rand1 = 2.0f * PI * get_random(seeds);
	float rand2 = get_random(seeds) * max_r;
	float rand2s = sqrt(rand2);

	float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
	float3 u = normalize(cross(axis, w));
	float3 v = cross(w, u);

	float3 newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));

	return (newdir);
}

t_ray	diffuse(t_ray ray, float3 n, float3 hitpoint, uint2 *seeds)
{
	float3 newdir = sample_hemisphere(n, 1.f, seeds);
	ray.pos = hitpoint + EPSILON * newdir;
	ray.dir = newdir;

	return (ray);
}

t_ray	reflect(t_ray ray, float3 n, float3 hitpoint, t_sphere hitsphere, uint2 *seeds)
{
	float3 tmp = ray.dir;
	float3 reflected_dir;

	reflected_dir = tmp - 2 * dot(tmp, n) * n;
	ray.dir = sample_hemisphere(reflected_dir, hitsphere.surf.roughness, seeds);
	ray.pos = hitpoint + EPSILON * ray.dir;
	return (ray);
}

float3	trace_ray(t_ray ray, __global t_sphere *obj, int num_obj, uint2 *seeds)
{
	float3	mask = (float3)(1.f, 1.f, 1.f);
	float3	res = (float3)(0, 0, 0);

	for (int bounce = 0; bounce < max_bounces; ++bounce)
	{
		int hitsphere_id;
		float t = get_intersection(&ray, obj, num_obj, &hitsphere_id);
		if (t < 0)
			break;
		float3 hitpoint = ray.pos + t * ray.dir;
		if (obj[hitsphere_id].surf.type.y != 1.f)
			mask *= obj[hitsphere_id].col;
		res += mask * obj[hitsphere_id].emission;
		if (obj[hitsphere_id].emission.x || obj[hitsphere_id].emission.y || obj[hitsphere_id].emission.z)
			break;
		float3 n = sphere_normal_point(hitpoint, obj[hitsphere_id]);
		n = dot(n, ray.dir) > 0 ? n * -1 : n;

		float rand = get_random(seeds);

		rand -= obj[hitsphere_id].surf.type.x;
		if (rand <= 0.f)
		{
//			mask *= obj[hitsphere_id].col;
//			res += mask * obj[hitsphere_id].emission;
			ray = diffuse(ray, n, hitpoint, seeds);
		}
		else if (rand - obj[hitsphere_id].surf.type.y <= 0.f)
			ray = reflect(ray, n, hitpoint, obj[hitsphere_id], seeds);
		else
			break; //refraction here

		float cosine = dot(n, ray.dir);
		if (cosine < 0)
			break;
		mask *= sqrt(cosine);//poor gamma-correction
	}

	return (res);
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
	t_ray ray = get_camera_ray(x, y, &cam, &seeds);
	pixels[id] = (float3)(0,0,0);
	pixels[id] += trace_ray(ray, obj, num_obj, &seeds);
	seed[id] = seeds.x;
	seed[id + w * h] = seeds.y;
}
