#include "kernel.h"

float3		color_disrupt(int disrupt, float2 coord, float3 col);
float3		get_point_col(t_obj *hitobj, t_texture texture, float2 coord);
float	perlin_noise(float2 coord);
float	noise2d(float x, float y);
float smooth_inter(float x, float y, float s);
float lin_inter(float x, float y, float s);
int noise2(int x, int y);

constant int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
					 185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
					 9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
					 70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
					 203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
					 164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
					 228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
					 232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
					 193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
					 101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
					 135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
					 114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

int noise2(int x, int y)
{
	int tmp = hash[y % 256];
	return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
	return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
	return lin_inter(x, y, s * s * (3-2*s));
}

float	noise2d(float x, float y)
{
	int x_int = x;
	int y_int = y;
	float x_frac = x - x_int;
	float y_frac = y - y_int;
	int s = noise2(x_int, y_int);
	int t = noise2(x_int+1, y_int);
	int u = noise2(x_int, y_int+1);
	int v = noise2(x_int+1, y_int+1);
	float low = smooth_inter(s, t, x_frac);
	float high = smooth_inter(u, v, x_frac);
	return smooth_inter(low, high, y_frac);
}

float	perlin_noise(float2 coord)
{
	float	freq = 10.f;
	float	amp = 50.f;
	float	fin = 0;
	float	div = 0.0;

	float	xa = coord.x * amp;
	float	ya = coord.y * amp;

	for (int i = 0; i < 5; ++i)
	{
		div += 256 * amp;
		fin += noise2d(xa, ya) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
	}

	return (fin / div);
}

float3		color_disrupt(int disrupt, float2 coord, float3 col)
{
	if (disrupt == CHESS)
		return ((coord.x > 0.5f && coord.y > 0.5f) ||
		(coord.x <= 0.5f && coord.y <= 0.5f)) ? float3(0.9f,0.9f,0.9f) : col;
	else if (disrupt == COS)
	{
		float cos1 = cos(coord.y * PI);
		cos1 = cos1 < 0 ? -cos1 : cos1;
		float cos2 = cos(coord.x * PI);
		cos2 = cos2 < 0 ? -cos2 : cos2;
		return col * cos1 * cos2;
	}
	else if (disrupt == CIRCLE)
	{
		coord -= 0.5f;
		coord *= 80.f;
		float dist = sqrt(coord.x * coord.x + coord.y * coord.y);
		dist = cos(dist);
		dist = dist < 0.00001f ? 0.00001f : dist;
		return col * dist + (float3)(1.f,0.5f,0.5f) * (1.f - dist);
	}
	else if (disrupt == PERLIN)
	{
		float val = perlin_noise(coord);
		return (float3)(val, val, val);
	}
	else if (disrupt == PERLIN_RED)
	{
		float val = perlin_noise(coord);
		return (float3)(1.f - val, val, val);
	}
	else if (disrupt == PERLIN_GREEN)
	{
		float val = perlin_noise(coord);
		return (float3)(val, 1.f - val, val);
	}
	else if (disrupt == PERLIN_BLUE)
	{
		float val = perlin_noise(coord);
		return (float3)(val, val, 1.f - val);
	}
	return (col);
}

float3		get_point_col(t_obj *hitobj, t_texture texture, float2 coord)
{
	float3	res;

	res = hitobj->color;
	if (hitobj->col_disrupt && hitobj->tex_id < 0)
		res = color_disrupt(hitobj->col_disrupt, coord, hitobj->color);
	if (hitobj->tex_id >= 0)
		res = get_texture_col_float(texture, coord.x, coord.y, hitobj->tex_id);
	return (res);
}

int	get_hitpoint_material(t_obj *hitobj,
	float3 hitpoint,
	t_material *material,
	t_texture texture,
	t_ray ray)
{
	float2	coord;

	get_texture_coord(hitobj, hitpoint, &coord);
	coord.x = coord.x < 0 ? coord.x - ((int)coord.x - 1) : coord.x;
	coord.y = coord.y < 0 ? coord.y - ((int)coord.y - 1) : coord.y;

	material->diffuse = hitobj->diffuse;
	material->specular = hitobj->specular;
	material->refraction = hitobj->refraction;

	if (hitobj->mater_tex_id >= 0)
	{
		float3 tmp = get_texture_col_float(texture, coord.x, coord.y, hitobj->mater_tex_id);

		float sum = tmp.x + tmp.y + tmp.z;
		if (sum > 0.1f)
		{
			material->diffuse = tmp.x;
			material->specular = tmp.y;
			material->refraction = tmp.z;
			material->diffuse /= sum;
			material->specular /= sum;
			material->refraction /= sum;
		}
		else if(sum >= 0.f)
			return (0);
	}

	material->roughness = hitobj->roughness;
	material->emission = hitobj->emission;
	material->color = get_point_col(hitobj, texture, coord);
	material->normal = get_normal_obj(hitpoint, ray, hitobj);
	material->enter = dot(ray.dir, material->normal) < 0 ? true : false;
	material->normal = material->enter ? material->normal : -(material->normal);
	if (hitobj->type == plane || hitobj->type == disk || hitobj->type == rectangle)
		material->enter = true;
	return (1);
}