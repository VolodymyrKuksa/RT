

//#include "kernel.h"
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

float	intersection_cylinder(t_ray *ray,t_cylinder cylinder, __float3 c_rot)
{
	t_quad		q;
	__float3 	x;
	float	tmp[2];

	x = ray->pos - cylinder.pos;
	tmp[0] = dot(ray->dir, c_rot);
	tmp[1] = dot(x, c_rot);
	q.a = 2.0 * (dot(ray->dir, ray->dir) - tmp[0] * tmp[0]);
	q.b = 2.0 * (dot(ray->dir, x) - tmp[0] * tmp[1]);
	q.c = dot(x, x) - tmp[1] * tmp[1] - cylinder.r * cylinder.r;
	if ((q.d = q.b * q.b - 2.0 * q.a * q.c) < 0)
		return (-1.0);
	q.d = sqrt(q.d);
	return ((q.res = (-q.b - q.d) / q.a) > 0 ? q.res : (-q.b + q.d) / q.a);
}

float	intersection_plane(t_ray *ray,t_plane plane, __float3 p_rot)
{
	__float3 	x;

	x = ray->pos - plane.pos;
	return (-dot(x, p_rot) / dot(ray->dir,p_rot));
}


float	intersection_cone(t_ray *ray,t_cone cone, __float3 c_rot)
{
	__float3 	x;
	float	tmp[3];
	__float3	hitpoint;
	t_quad		q;
	float	res, length;

	x = ray->pos - cone.pos;
	tmp[0] = cone.tng * cone.tng + 1.f;
	tmp[1] = dot(ray->dir, c_rot);
	tmp[2] = dot(x, c_rot);
	q.a = 2.f * (1.f - tmp[0] * tmp[1] * tmp[1]);
	q.b = 2.f * (dot(ray->dir, x) - tmp[0] * tmp[1] * tmp[2]);
	q.c = dot(x, x) - tmp[0] * tmp[2] * tmp[2];
	if ((q.d = q.b * q.b - 2.f * q.a * q.c) < 0.f)
		return (-1.f);
	q.d = sqrt(q.d);
	res = (-q.b - q.d) / q.a;
	if (res > 0)
	{
		hitpoint = res * ray->dir + x;
		length = dot(c_rot, hitpoint);
		if (length < cone.m2 && length > cone.m1)
			return (res);
	}
	res = (-q.b + q.d) / q.a;
	if (res > 0)
	{
		hitpoint = res * ray->dir + x;
		length = dot(c_rot, hitpoint);
		if (length > cone.m1 && length < cone.m2)
			return (res);
	}
	return (-1);
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
	return (normal);
}

__float3	normal_cylinder(__float3  hitpoint, __float3  dir, t_cylinder *cylinder, __float3 c_rot)
{
	__float3 	normal;
	float	t;

	t = dot(c_rot, cylinder->pos) -
		dot(c_rot, hitpoint);
	t /= dot(c_rot, c_rot);
	normal = hitpoint - cylinder->pos + c_rot * t;
	normal = normalize(normal);
	return (normal);
}

__float3	normal_plane(__float3  hitpoint, __float3  dir, t_plane *plane, __float3 p_rot)
{
	__float3  normal;

	normal = p_rot;
	return (normal);
}

__float3	normal_cone(__float3  hitpoint, __float3  dir, t_cone *cone, __float3 c_rot)
{
	__float3  normal;

	if (dot(c_rot, cone->pos - hitpoint) < 0)
		normal = c_rot * length(cone->pos - hitpoint)
										* sqrt(cone->tng * cone->tng + 1);
	else
		normal = c_rot * -1 * length(cone->pos - hitpoint) *
							 sqrt(cone->tng * cone->tng + 1);
	normal += cone->pos;
	normal = hitpoint - normal;
	normal = normalize(normal);
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
			n = normal_cylinder(hitpoint, ray.dir, &(hitobj.primitive.cylinder), hitobj.basis.u);
			break;
		case plane:
			n = normal_plane(hitpoint, ray.dir, &(hitobj.primitive.plane), hitobj.basis.u);
			break;
		case cone:
			n = normal_cone(hitpoint, ray.dir, &(hitobj.primitive.cone), hitobj.basis.u);
			break;
		default:
			break;
	}
	return n;
}
//-----------------------------------------------------------------------------^