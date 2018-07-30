#include "kernel.h"

__constant float EPSILON = 0.001;
__constant float PI = 3.14159265359f;
__constant float PI_2 = 6.28318530718f;
__constant int max_bounces = 20;
__constant int min_bounces = 5;


t_ray get_camera_ray(int x, int y, t_cam *cam, uint2 *seeds);
static float get_random(uint2 *seeds);
float	solve_quad(t_quad q);
float	get_intersection(t_ray *r, __global t_obj *obj, int n_obj, int *id);
float3	trace_ray(t_ray, __global t_obj *, int, uint2 *, t_texture, float3, float);
t_ray	diffuse(t_ray ray, float3 n, float3 hitpoint, uint2 *seeds);
t_ray	reflect(t_ray ray, float3 hitpt, t_material material, uint2 *seeds);
t_ray	refract(t_ray, float3, t_material, uint2 *, float);
float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds);
bool	participating_media(t_ray *ray, float t, uint2 *seeds);

float	intersection_sphere(t_ray*,t_sphere);
float	intersection_cone(t_ray*,t_cone,__float3);
float	intersection_plane(t_ray*,t_plane,__float3);
float	intersection_cylinder(t_ray*,t_cylinder,__float3);
float	intersection_torus(t_ray*,t_torus,__float3);
float	intersection_disk(t_ray*,t_disk,__float3);
float	intersection_rectangle(t_ray*,t_rectangle,__global t_basis*);
float	intersection_parallelogram(t_ray*,t_parallelogram,__global t_basis*);
float 	intersection_triangle(t_ray *ray,t_triangle triangle);
float	intersection_paraboloid(t_ray *ray,t_paraboloid paraboloid, __float3);

__float3	normal_sphere(__float3 , t_sphere *);
__float3	normal_cone(__float3  , t_cone * , __float3);
__float3	normal_plane(__float3  , t_plane * , __float3);
__float3	normal_cylinder(__float3 , t_cylinder * , __float3);
__float3	normal_parallelogram(__float3, t_parallelogram *, t_basis *);

float3		get_normal_obj(float3 hitpoint, t_obj *hitobj);

float3	get_point_color(t_obj *hitobj, float3 hitpoint, t_texture texture);
int	get_hitpoint_material(t_obj *, float3, t_material *, t_texture, t_ray);
void	get_texture_coord(t_obj *, float3, float2 *);

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
			case torus:
				tmp = intersection_torus(r, object[i].primitive.torus, object[i].basis.u);
                break;
			case disk:
				tmp = intersection_disk(r, object[i].primitive.disk, object[i].basis.u);
				break;
            case rectangle:
                tmp = intersection_rectangle(r, object[i].primitive.rectangle, &(object[i].basis));
                break;
			case parallelogram:
				tmp = intersection_parallelogram(r, object[i].primitive.parallelogram, &(object[i].basis));
				break;
			case triangle:
				tmp = intersection_triangle(r, object[i].primitive.triangle);
				break;
			case paraboloid:
				tmp = intersection_paraboloid(r, object[i].primitive.paraboloid, object[i].basis.u);
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

t_ray	reflect(t_ray ray, float3 hitpoint, t_material material, uint2 *seeds)
{
	float3 tmp = ray.dir;
	float3 reflected_dir;

	reflected_dir = tmp - 2 * dot(tmp, material.normal) * material.normal;
	ray.dir = sample_hemisphere(reflected_dir, material.roughness, seeds);
	ray.pos = hitpoint + EPSILON * ray.dir;
	return (ray);
}

t_ray	refract(t_ray ray, __float3 hitpoint, t_material material, uint2 *seeds, float refr_coef)
{
	float	cosine_theta = dot(ray.dir, material.normal);
	float	cosine_theta_r;

	if (material.enter && ray.refractions > 0) {
		ray.pos = hitpoint + EPSILON *ray.dir;
		ray.refractions++;
		return (ray);
	} else if (!material.enter && ray.refractions > 1) {
		ray.pos = hitpoint + EPSILON * ray.dir;
		ray.refractions--;
		return (ray);
	}

	float3	t;
	if (material.enter)
	{
		cosine_theta_r = 1.f - (1.f - cosine_theta * cosine_theta)
			/ (refr_coef * refr_coef);
		ray.refractions++;
		cosine_theta_r = sqrt(cosine_theta_r);
		t = ((ray.dir - material.normal * cosine_theta) / refr_coef) -
			material.normal * cosine_theta_r;
	}
	else
	{
		cosine_theta_r = 1.f - (refr_coef * refr_coef * (1.f - cosine_theta * cosine_theta));
		ray.refractions--;
		cosine_theta_r = sqrt(cosine_theta_r);
		t = (refr_coef * (ray.dir - material.normal * cosine_theta)) -
			material.normal * cosine_theta_r;
	}

	if (dot(t, material.normal) < 0.f)
	{
		ray.dir = sample_hemisphere(t, material.roughness, seeds);
		ray.pos = hitpoint + EPSILON * ray.dir;
	}
	else
		return reflect(ray, hitpoint, material, seeds);

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

float3	trace_ray(t_ray ray, __global t_obj *obj, int num_obj, uint2 *seeds,
t_texture texture, float3 mask, float refr_coef)
{
	float3	res = (float3)(0, 0, 0);
	t_material	material;
	for (int bounce = 0; bounce < max_bounces; ++bounce)
	{
		float r = get_random(seeds);
		float light = mask.x + mask.y + mask.z;
		if (r > light)
			break;
		int hitobj_id = -1;
		float t = get_intersection(&ray, obj, num_obj, &hitobj_id);
		if (t < 0)
			break;
 //return ((__float3)(1,1,1));
		t_obj hitobj = obj[hitobj_id];
		if (ray.dust > 0.f && participating_media(&ray, t, seeds))
			continue;
		__float3 hitpoint = ray.pos + t * ray.dir;
		if(get_hitpoint_material(&hitobj, hitpoint, &material, texture, ray))
		{
			res += mask *material.emission;
			mask *= material.color;
			float rand = get_random(seeds);
			rand -= material.diffuse;
			if (rand <= 0.f)
			{
				ray = diffuse(ray, material.normal, hitpoint, seeds);
				float cosine = dot(material.normal, ray.dir);
				cosine = cosine < 0 ? -cosine : cosine;
				mask *= sqrt(cosine);
			}
			else if (rand - material.specular <= 0.f)
			{
				ray = reflect(ray, hitpoint, material, seeds);
				if (dot(material.normal, ray.dir) < 0)
					break;
			}
			else
				ray = refract(ray, hitpoint, material, seeds, refr_coef);
		}
		else
			ray.pos = hitpoint + EPSILON * ray.dir;
	}
	return (res);
}

float		cartoon_round(float val);

float		cartoon_round(float val)
{
	return val > 0.5f ? 1.f : 0.f;
}

float3		apply_effect(float3 px, int effect);

float3		apply_effect(float3 px, int effect)
{
	if (!effect)
		return px;
	else if (effect == BLACK_N_WHITE)
	{
		float	avrg = (px.x + px.y + px.z) / 3;
		return (float3)(avrg, avrg, avrg);
	}
	else if (effect == NEGATIVE)
	{
		return (float3)(1.f - px.x, 1.f - px.y, 1.f - px.z);
	}
	else if (effect == SEPIA)
	{
		float3	res;
		res.x = 0.393f * px.x + 0.769f * px.y + 0.189 * px.z;
		res.y = 0.349f * px.x + 0.686f * px.y + 0.168 * px.z;
		res.z = 0.272f * px.x + 0.534f * px.y + 0.131 * px.z;
		return res;
	}
	else if (effect == CARTOON)
	{
		return (float3)(cartoon_round(px.x), cartoon_round(px.y), cartoon_round(px.z));
	}
	return px;
}

t_ray get_precise_ray(int x, int y, t_cam *cam);

t_ray get_precise_ray(int x, int y, t_cam *cam)
{
	t_ray ray;

	ray.pos = (float3)(0,0,0);

	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
		-cam->f_length);
	ray.dir.x *= cam->ratio;
	ray.dir.y *= cam->ratio;
	ray.dir = normalize(ray.dir);
	return(ray);
}

__kernel void	get_mouse_intersect(
	int x,
	int y,
	__global t_obj *obj,
	int num_obj,
	t_cam cam,
	__global int *id)
{
	t_ray ray = get_precise_ray(x, y, &cam);
	int		tmp;
	float t = get_intersection(&ray, obj, num_obj, &tmp);
	if (t > 0.f)
		*id = tmp;
	else
		*id = -1;
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

	t_texture	texture = {tx, txdata, tx_count};
	t_ray ray = get_camera_ray(x, y, &cam, &seeds);
	pixels[id] = (float3)(0,0,0);
	pixels[id] += trace_ray(ray, obj, num_obj, &seeds, texture, cam.filter,
		cam.refr_coef) * cam.brightness;
	pixels[id] = apply_effect(pixels[id], cam.effect);
	seed[id] = seeds.x;
	seed[id + w * h] = seeds.y;
}
