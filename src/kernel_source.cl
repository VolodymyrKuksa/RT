#include "kernel.h"

__constant float EPSILON = 0.001;
__constant float PI = 3.14159265359f;
__constant int max_bounces = 20;
__constant int min_bounces = 5;


t_ray get_camera_ray(int x, int y, t_cam *cam, uint2 *seeds);
static float get_random(uint2 *seeds);
float	solve_quad(t_quad q);
float	get_intersection(t_ray *r, __global t_obj *obj, int n_obj, int *id);
float3	trace_ray(t_ray ray, __global t_obj *obj, int num_obj, uint2 *seeds);
t_ray	diffuse(t_ray ray, float3 n, float3 hitpoint, uint2 *seeds);
t_ray	reflect(t_ray ray, float3 n, float3 hitpt, t_obj sp, uint2 *seeds);
t_ray	refract(t_ray ray, float3 hitpoint, t_obj hitsphere, uint2 *seeds);
float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds);
bool	participating_media(t_ray *ray, float t, uint2 *seeds);

float	intersection_sphere(t_ray*,t_sphere);
float	intersection_cone(t_ray*,t_cone,__float3);
float	intersection_plane(t_ray*,t_plane,__float3);
float	intersection_cylinder(t_ray*,t_cylinder,__float3);

__float3	normal_sphere(__float3 , __float3 , t_sphere *);
__float3	normal_cone(__float3 , __float3 , t_cone * , __float3);
__float3	normal_plane(__float3 , __float3  , t_plane * , __float3);
__float3	normal_cylinder(__float3 , __float3 , t_cylinder * , __float3);

float3		get_normal_obj(float3 hitpoint, t_ray ray, t_obj hitobj);

float3		get_texture_col(__global t_rgb *tx, __global t_txdata *txdata, int tx_count, int x, int y, int tx_id);

t_ray get_camera_ray(int x, int y, t_cam *cam, uint2 *seeds)
{
	t_ray ray;

	float a = get_random(seeds) * 2 * PI; //random angle
	float r = sqrt(get_random(seeds) * cam->aperture); //random radius
	float ax = r * cos(a); //random x
	float ay = r * sin(a); // random y

	ray.pos = (float3)(ax,ay,0);

	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
		-cam->f_length);
	ray.dir.x = (ray.dir.x + get_random(seeds) - 0.5f) * cam->ratio;
	ray.dir.y = (ray.dir.y + get_random(seeds) - 0.5f) * cam->ratio;
	ray.dir -= ray.pos;
	ray.dir = normalize(ray.dir);
	ray.refractions = 0;
	ray.dust = cam->dust;
	return(ray);
}


static float get_random(uint2 *seeds)
{
	seeds->x = 36969 * ((seeds->x) & 65535) + ((seeds->x) >> 16);
	seeds->y = 18000 * ((seeds->y) & 65535) + ((seeds->y) >> 16);

	unsigned int ires = ((seeds->x) << 16) + (seeds->y);

	union {
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;
	return (res.f - 2.0f) / 2.0f;
}

float	get_intersection(t_ray *r, __global t_obj *object, int num_obj, int *id)
{
	float	t = -1;
	float	tmp = -1;
	for(int i = 0; i < num_obj; i++)
	{
		switch(object[i].type)
		{
			case sphere:
				tmp = intersection_sphere(r, object[i].primitive.sphere);
				break;
			case cylinder:
				tmp = intersection_cylinder(r, object[i].primitive.cylinder, object[i].basis.u);
				break;
			case plane:
				tmp = intersection_plane(r, object[i].primitive.plane, object[i].basis.u);
				break;
			case cone:
				tmp = intersection_cone(r, object[i].primitive.cone, object[i].basis.u);
				break;
			default:
				break;
		}
		if ((t < 0 && tmp > 0) || (tmp < t && tmp > 0))
		{
			t = tmp;
			*id = i;
		}
	}
//t = 0.5f;
	return t;
}

float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds)
{
	float rand1 = 2.0f * PI * get_random(seeds);
	float rand2 = get_random(seeds) * max_r;
	float rand2s = sqrt(rand2);

	float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) :
		(float3)(1.0f, 0.0f, 0.0f);
	float3 u = normalize(cross(axis, w));
	float3 v = cross(w, u);

	float3 newdir = normalize(u * cos(rand1)*rand2s +
		v*sin(rand1)*rand2s +w*sqrt(1.0f - rand2));

	return (newdir);
}

t_ray	diffuse(t_ray ray, float3 n, float3 hitpoint, uint2 *seeds)
{
	float3 newdir = sample_hemisphere(n, 1.f, seeds);
	ray.pos = hitpoint + EPSILON * newdir;
	ray.dir = newdir;

	return (ray);
}

t_ray	reflect(t_ray ray, float3 n, float3 hitpoint, t_obj sp, uint2 *seeds)
{
	float3 tmp = ray.dir;
	float3 reflected_dir;

	reflected_dir = tmp - 2 * dot(tmp, n) * n;
	ray.dir = sample_hemisphere(reflected_dir, sp.roughness, seeds);
	ray.pos = hitpoint + EPSILON * n;
	return (ray);
}

t_ray	refract(t_ray ray, __float3 hitpoint, t_obj object, uint2 *seeds)
{
	float3	n = get_normal_obj(hitpoint, ray, object);

	bool	enter = dot(ray.dir, n) > 0 ? false : true;
	n = enter ? n : -n;

	float	cosine_theta = dot(ray.dir, n);
	float	cosine_theta_r;

	if (enter && ray.refractions > 0) {
		ray.pos = hitpoint + EPSILON * n;
		ray.refractions++;//Поговорить с Вовчиком
		return (ray);
	} else if (!enter && ray.refractions > 1) {
		ray.pos = hitpoint + EPSILON * n;
		ray.refractions--;
		return (ray);
	}

	float3	t;
	if (enter)
	{
		cosine_theta_r = 1.f - (1.f - cosine_theta * cosine_theta)
			/ 2.25f;
		ray.refractions++;
		cosine_theta_r = sqrt(cosine_theta_r);
		t = ((ray.dir - n * cosine_theta) / 1.5f) - n * cosine_theta_r;
	}
	else
	{
		cosine_theta_r = 1.f - (2.25f * (1 - cosine_theta * cosine_theta));
		ray.refractions--;
		cosine_theta_r = sqrt(cosine_theta_r);
		t = (1.5f * (ray.dir - n * cosine_theta)) - n * cosine_theta_r;
	}

	ray.dir = sample_hemisphere(t, object.roughness, seeds);
	ray.pos = hitpoint + EPSILON * ray.dir;

	return (ray);
}

bool	participating_media(t_ray *ray, float t, uint2 *seeds)
{
	if (!ray->refractions)
	{
		float collision_prob = t * ray->dust;
		float rd = get_random(seeds);
		if (rd < collision_prob)
		{
			float new_t = t * get_random(seeds);
			float3 n = (float3)(get_random(seeds) - 0.5f,
								get_random(seeds) - 0.5f,
								get_random(seeds) - 0.5f);
			n = normalize(n);
			float3 hitpoint = new_t * ray->dir + ray->pos;
			*ray = diffuse(*ray, n, hitpoint, seeds);
			return true;
		}
	}
	return false;
}
//------------------------------------------------------------------------------\/
float3	trace_ray(t_ray ray, __global t_obj *obj, int num_obj, uint2 *seeds)
{
	float3	mask = (float3)(1.f, 1.f, 1.f);
	float3	res = (float3)(0, 0, 0);
	int		bounce = 0;
	for (int bounce = 0; bounce < max_bounces; ++bounce)
	{
		//if ray cant transfer much light, it will be break earlier
		if (bounce > min_bounces) {
			float r = get_random(seeds);
			float light = mask.x > mask.y && mask.x > mask.z ? mask.x :
				(mask.y > mask.z ? mask.y : mask.z);
			if (r > light)
				break;
		}

		int hitobj_id = -1;
		float t = get_intersection(&ray, obj, num_obj, &hitobj_id);

		if (t < 0)
			break;
		t_obj hitobj = obj[hitobj_id];
		if (ray.dust > 0.f && participating_media(&ray, t, seeds))
			continue;
		__float3 hitpoint = ray.pos + t * ray.dir;
		res += mask * hitobj.emission;
		__float3 n = get_normal_obj(hitpoint, ray, hitobj);
		n = dot(n, ray.dir) > 0 ? -n : n;
		float rand = get_random(seeds);
		rand -= hitobj.diffuse;
		if (rand <= 0.f)
		{
			mask *= hitobj.color;
			ray = diffuse(ray, n, hitpoint, seeds);
			float	cosine = dot(n, ray.dir);
			cosine = cosine < 0 ? -cosine : cosine;
			mask *= sqrt(cosine);//poor gamma-correction
		}
		else if (rand - hitobj.specular <= 0.f)
		{
			ray = reflect(ray, n, hitpoint, hitobj, seeds);
			if (dot(n, ray.dir) < 0)
				break;
		}
		else
			ray = refract(ray, hitpoint, hitobj, seeds);
	}
	return (res);
}
//------------------------------------------------------------------------------/\


float3		get_texture_col(__global t_rgb *tx, __global t_txdata *txdata, int tx_count, int x, int y, int tx_id)
{
	x = x % txdata[tx_id].width;
	y = y % txdata[tx_id].height;
	if (tx_id >= tx_count)
		return ((float3)(-1.f, -1.f, -1.f));
	int		index = txdata[tx_id].start + txdata[tx_id].width * y + x;
	float3		res =
		(float3)(tx[index].bgra[2], tx[index].bgra[1], tx[index].bgra[0]);
	return (res/ 256);
}


 __kernel void	render_pixel(
	__global float3 *pixels,
	__global t_obj *obj,
	int num_obj,
	t_cam cam,
	int w,
	int h,
	__global unsigned int *seed,
	__global t_rgb *tx,
	__global t_txdata *txdata,
	int tx_count)
{
	int		id = get_global_id(0);
	int		x = id % w;
	int		y = id / w;
	uint2	seeds;
	seeds.x = seed[id];
	seeds.y = seed[id + w * h];

//	int		tx_id = 1;
//	pixels[id] = get_texture_col(tx, txdata, tx_count, x, y, tx_id);

	t_ray ray = get_camera_ray(x, y, &cam, &seeds);
	pixels[id] = (float3)(0,0,0);
	pixels[id] += trace_ray(ray, obj, num_obj, &seeds);
	seed[id] = seeds.x;
	seed[id + w * h] = seeds.y;
}
