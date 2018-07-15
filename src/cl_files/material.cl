#include "kernel.h"

void	get_hitpoint_material(t_obj *hitobj,
	float3 hitpoint,
	t_material *material,
	t_texture texture,
	t_ray ray)
{
	float2	coord;

	if (hitobj->tex_id >=0)
	{
		get_texture_coord(hitobj, hitpoint, texture, &coord);
		coord.x = coord.x < 0 ? coord.x - ((int)coord.x - 1) : coord.x;
		coord.y = coord.y < 0 ? coord.y - ((int)coord.y - 1) : coord.y;
	}
	material->diffuse = hitobj->diffuse;
	material->specular = hitobj->specular;
	material->refraction = hitobj->refraction;
	material->roughness = hitobj->roughness;
	material->emission = hitobj->emission;
	material->color = hitobj->tex_id >= 0 ? get_texture_col_float(texture, coord.x, coord.y, hitobj->tex_id) : hitobj->color;
	material->normal = get_normal_obj(hitpoint, ray, hitobj);
	material->enter = dot(ray.dir, material->normal) < 0 ? true : false;
	material->normal = material->enter ? material->normal : -(material->normal);
}