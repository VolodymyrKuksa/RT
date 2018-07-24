#include "kernel.h"

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
	material->color = hitobj->tex_id >= 0 ? get_texture_col_float(texture, coord.x, coord.y, hitobj->tex_id) : hitobj->color;
	material->normal = get_normal_obj(hitpoint, ray, hitobj);
	material->enter = dot(ray.dir, material->normal) < 0 ? true : false;
	material->normal = material->enter ? material->normal : -(material->normal);
	return (1);
}