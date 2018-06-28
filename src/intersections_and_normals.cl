

#include "../src/kernel.h"
//---------------------------------intersection-------------------------------\/
float	intersection_sphere(t_ray *ray,t_sphere sphere)
{
	t_quad		q;
	__float3 	x;

	x = ray->pos - sphere.pos;
	q.a = 2.0f;
	q.b = 2.0f * dot(ray->dir, x);
	q.c = dot(x, x) - sphere.r * sphere.r;
	if ((q.d = (q.b * q.b - 2.0f * q.a * q.c)) < 0)
		return (-1.0f);
	q.d = sqrt(q.d);
	return ((q.res = ((-q.b - q.d) / q.a)) > 0 ? q.res : (-q.b + q.d) / q.a); // if x1 > 0 -> ret x1 else ret x2
	//return(1.f);
}

float	intersection_cylinder(t_ray *ray,t_cylinder cylinder)
{
	t_quad		q;
	__float3 	x;
	float	tmp[2];

	x = ray->pos - cylinder.pos;
	tmp[0] = dot(ray->dir, cylinder.rot);
	tmp[1] = dot(x, cylinder.rot);
	q.a = 2.0 * (dot(ray->dir, ray->dir) - tmp[0] * tmp[0]);
	q.b = 2.0 * (dot(ray->dir, x) - tmp[0] * tmp[1]);
	q.c = dot(x, x) - tmp[1] * tmp[1] - cylinder.r * cylinder.r;
	if ((q.d = q.b * q.b - 2.0 * q.a * q.c) < 0)
		return (-1.0);
	q.d = sqrt(q.d);
	return ((q.res = (-q.b - q.d) / q.a) > 0 ? q.res : (-q.b + q.d) / q.a);
}

float	intersection_plane(t_ray *ray,t_plane plane)
{
	__float3 	x;

	x = ray->pos - plane.pos;
	return (-dot(x, plane.rot) / dot(ray->dir,plane.rot));
}

float	intersection_cone(t_ray *ray,t_cone cone)
{
	__float3 	x;
	float	tmp[3];
	t_quad		q;

	x = ray->pos - cone.pos;
	tmp[0] = cone.tng * cone.tng + 1.0;
	tmp[1] = dot(ray->dir, cone.rot);
	tmp[2] = dot(x, cone.rot);
	q.a = 2.0 * (dot(ray->dir, ray->dir) - tmp[0] * tmp[1] * tmp[1]);
	q.b = 2.0 * (dot(ray->dir, x) - tmp[0] * tmp[1] * tmp[2]);
	q.c = dot(x, x) - tmp[0] * tmp[2] * tmp[2];
	if ((q.d = q.b * q.b - 2.0 * q.a * q.c) < 0)
		return (-1.0);
	q.d = sqrt(q.d);
	return ((q.res = (-q.b - q.d) / q.a) > 0 ? q.res : (-q.b + q.d) / q.a);
}
//-----------------------------------------------------------------------------^
// ray->pos точка на сфере 
// ray->dir текущий вектор

//-------------------------------------normal---------------------------------\/
__float3	normal_sphere(__float3  hitpoint, __float3  dir, t_sphere *sphere)
{
	__float3  normal;

	normal = hitpoint - sphere->pos;
	normal = normalize(normal);
//	if (dot(dir, normal) > 0)
//		normal *= -1.f;
	return (normal);
}

__float3	normal_cylinder(__float3  hitpoint, __float3  dir, t_cylinder *cylinder)
{
	__float3 	normal;
	float	t;

	t = dot(cylinder->rot, cylinder->pos) -
		dot(cylinder->rot, hitpoint);
	t /= dot(cylinder->rot, cylinder->rot);
	normal = hitpoint - cylinder->pos + cylinder->rot * t;
	normal = normalize(normal);
//	if (dot(dir, normal) > 0)
//		normal *= -1.f;
	return (normal);
}

__float3	normal_plane(__float3  hitpoint, __float3  dir, t_plane *plane)
{
	__float3  normal;

	normal = plane->rot;
//	if (dot(dir, normal) > 0)
//		normal *=  -1.f;
	return (normal);
}

__float3	normal_cone(__float3  hitpoint, __float3  dir, t_cone *cone)
{
	__float3  normal;

	if (dot(cone->rot, cone->pos - hitpoint) < 0)
		normal = cone->rot * length(cone->pos - hitpoint)
										* sqrt(cone->tng * cone->tng + 1);
	else
		normal = cone->rot * -1 * length(cone->pos - hitpoint) *
							 sqrt(cone->tng * cone->tng + 1);
	normal += cone->pos;
	normal = hitpoint - normal;
	normal = normalize(normal);
//	if (dot(dir, normal) > 0)
//		normal *= -1.f;
	return (normal);
}

float3		get_normal_obj(float3 hitpoint, t_ray ray, t_obj hitobj)
{
	float3 n;
	switch (hitobj.type)
	{
		case sphere:
			n = normal_sphere(hitpoint, ray.dir, &(hitobj.primitive.sphere));
			break;
		case cylinder:
			n = normal_cylinder(hitpoint, ray.dir, &(hitobj.primitive.cylinder));
			break;
		case plane:
			n = normal_plane(hitpoint, ray.dir, &(hitobj.primitive.plane));
			break;
		case cone:
			n = normal_cone(hitpoint, ray.dir, &(hitobj.primitive.cone));
			break;
		default:
			break;
	}
	return n;
}
//-----------------------------------------------------------------------------^