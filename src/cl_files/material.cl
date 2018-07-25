#include "kernel.h"

float3		color_disrupt(int disrupt, float2 coord, float3 col);
float3		get_point_col(t_obj *hitobj, t_texture texture, float2 coord);

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
	return (1);
}