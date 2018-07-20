

//#include "kernel.h"
//---------------------------------intersection-------------------------------\/

float	intersection_rectangle(t_ray *ray,t_rectangle rectangle, __global t_basis *basis)
{
    __float3 	x;
    float t;
    __float3 hitpoint;

    x = ray->pos - rectangle.pos;
    t = -dot(x, basis->u) / dot(ray->dir,basis->u);
    hitpoint = t * ray->dir + x;
    if (fabs(dot(hitpoint, basis->v)) < rectangle.h && fabs(dot(hitpoint, basis->w)) < rectangle.w)
        return (t);
    return (-1.f);
}


float	intersection_disk(t_ray *ray,t_disk disk, float3 d_rot)
{
	__float3 	x;
	float t;
	__float3 hitpoint;

	x = ray->pos - disk.pos;
	t = -dot(x, d_rot) / dot(ray->dir,d_rot);
	hitpoint = t * ray->dir + x;
	if (length(hitpoint) > disk.r)
		return (-1.f);
	return (t);
}

float	intersection_sphere(t_ray *ray,t_sphere sphere)
{
	t_quad		q;
	__float3 	x;
	float dist;

	x = ray->pos - sphere.pos;
	dist = length(x) - sphere.r;
	if (dist > 0)
		x += dist*ray->dir;
	else
		dist = 0.f;
	q.b = 2.0f * dot(ray->dir, x);
	q.c = dot(x, x) - sphere.r * sphere.r;
	if ((q.d = (q.b * q.b - 4.0f * q.c)) < 0)
		return (-1.0f);
	q.d = sqrt(q.d);
	return ((q.res = ((-q.b - q.d) / 2.f)) > 0 ? q.res + dist: (-q.b + q.d) / 2.f);
}

float	intersection_cylinder(t_ray *ray,t_cylinder cylinder, __float3 c_rot)
{
	t_quad		q;
	__float3 	x, hitpoint;
	float	tmp[2], res[2], len;
	t_disk disk;

	x = ray->pos - cylinder.pos;
	tmp[0] = dot(ray->dir, c_rot);
	tmp[1] = dot(x, c_rot);
	q.a = 2.0 * (dot(ray->dir, ray->dir) - tmp[0] * tmp[0]);
	q.b = 2.0 * (dot(ray->dir, x) - tmp[0] * tmp[1]);
	q.c = dot(x, x) - tmp[1] * tmp[1] - cylinder.r * cylinder.r;
	if ((q.d = q.b * q.b - 2.0 * q.a * q.c) >= 0)
	{
		q.d = sqrt(q.d);
		q.res = (-q.b - q.d) / q.a;
		if (q.res > 0) {
			hitpoint = q.res * ray->dir + x;
			len = dot(hitpoint, c_rot);
			if (len < cylinder.h && len > 0)
				return (q.res);
		}
		q.res = (-q.b + q.d) / q.a;
		if (q.res > 0) {
			hitpoint = q.res * ray->dir + x;
			len = dot(hitpoint, c_rot);
			if (len < cylinder.h && len > 0)
				return (q.res);
		}
	}
	return (-1);
}

float	intersection_plane(t_ray *ray,t_plane plane, __float3 p_rot)
{
	__float3 	x;
	float d = dot(ray->dir,p_rot);
	x = ray->pos - plane.pos;
	if(d != 0)
		return (-dot(x, p_rot) / d);
	else
		return (-1.f);
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
	return (-1.f);
}

void positive_discriminant(double Q, __double2 koefs, double *solve, double b)
{
	double alpha, betha, ntmp;

	ntmp = -koefs[1] / 3.f;
		alpha = cbrt(-koefs[0] / 2.f + sqrt(Q));
		betha = -koefs[1] / (3.f * alpha);
		*solve = alpha + betha - b;
}

void negative_discriminant(double Q, __double2 koefs, double *solve, double b)
{
	double cosphi,tanphi, tmp, ntmp, phi;

	tmp = -3.f / koefs.y;
	ntmp = -koefs.y / 3.f;
	cosphi = -koefs.x * 0.5f * sqrt(tmp * tmp * tmp);
	phi = acos(cosphi);
	solve[0] = 2 * sqrt(ntmp) * cos(phi / 3.f) - b;
}

void fourth_degree_equation_solver(__float4 koefs, __float2 *solve)
{
	__double3 ferrari_koefs, cubic_resol_koefs;
	__double2 cubic_two_params_koefs;
	double a2, a3, a4, p2, b2, Q, z, t, y, s, cubic_solve[3];
	int num_of_roots, i = 0;
	t_quad q;

	a2 = koefs[3] * koefs[3];
	a3 = a2 * koefs[3];
	a4 = a2 * a2;
	//y4+py2+qy+r=0
	ferrari_koefs[2] = koefs[2] - 0.375f * a2;
	ferrari_koefs[1] = 0.125f * a3 - 0.5f * koefs[2] * koefs[3] + koefs[1];
	ferrari_koefs[0] = (-0.01171875f) * a4 + 0.0625f * koefs[2] * a2 - 0.25f * koefs[1] * koefs[3] + koefs[0];
	if (ferrari_koefs[1] * ferrari_koefs[1] < 1e-4)
	{
		q.b = ferrari_koefs[2];
		q.c = ferrari_koefs[0];
		q.d = q.b * q.b - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[0] = (-q.b - q.d) / 2.f;
			(*solve)[1] = (-q.b + q.d) / 2.f;
			if ((*solve)[0] >= 0.f)
				(*solve)[0] = (q.res = -sqrt((*solve)[0]) - koefs[3] / 4.f) > 0.f ? q.res : sqrt((*solve)[0]) - koefs[3] / 4.f;
			if ((*solve)[1] >= 0.f)
				(*solve)[1] = (q.res = -sqrt((*solve)[1]) - koefs[3] / 4.f) > 0.f ? q.res : sqrt((*solve)[1]) - koefs[3] / 4.f;
		}
		return;
	}
	//y3+py2+qy+r=0
	cubic_resol_koefs[2] = (-0.5f) * ferrari_koefs[2];
	cubic_resol_koefs[1] = -ferrari_koefs[0];
	cubic_resol_koefs[0] = (-0.125f) * ferrari_koefs[1] * ferrari_koefs[1] + 0.5f * ferrari_koefs[0] * ferrari_koefs[2];
	p2 = cubic_resol_koefs[2] * cubic_resol_koefs[2];
	//y3+py+q=0
	cubic_two_params_koefs[1] = cubic_resol_koefs[1] - p2 / 3.f;
	cubic_two_params_koefs[0] = cubic_resol_koefs[0] + 2.f * p2  * cubic_resol_koefs[2] / 27.f - cubic_resol_koefs[2] * cubic_resol_koefs[1] / 3.f;
	//y = z+t, 3zt+p = 0
	b2 = cubic_two_params_koefs[0] * cubic_two_params_koefs[0];
	Q = cubic_two_params_koefs[1] * cubic_two_params_koefs[1] * cubic_two_params_koefs[1] / 27.f + cubic_two_params_koefs[0] * cubic_two_params_koefs[0] / 4.f;
	if (Q > 0)
		positive_discriminant(Q, cubic_two_params_koefs, &cubic_solve, cubic_resol_koefs[2] / 3.f);
	else
		negative_discriminant(Q, cubic_two_params_koefs, &cubic_solve, cubic_resol_koefs[2] / 3.f);
	if ((q.b = 2.f * cubic_solve[i] - ferrari_koefs[2]) > 0.f ) {
		q.a = q.b;
		q.b = -sqrt(q.b);
		q.c = ferrari_koefs[1] / (-2.f * q.b) + cubic_solve[i];
		q.d = q.a - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[0] =
					(q.res = (-q.b - q.d) / 2.f - koefs[3] / 4.f) > 0.f
					? q.res : (-q.b + q.d) / 2.f - koefs[3] / 4.f;
		}
		q.b = -q.b;
		q.c = ferrari_koefs[1] / (-2.f * q.b) + cubic_solve[i];
		q.d = q.a - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[1] =
					(q.res = (-q.b - q.d) / 2.f - koefs[3] / 4.f) > 0.f
					? q.res : (-q.b + q.d) / 2.f - koefs[3] / 4.f;
		}
	}
}

int check_sphere(t_ray *ray, float radius, __float3 pos)
{
	t_quad		q;
	__float3 	x;

	x = ray->pos - pos;
	q.b = 2.0f * dot(ray->dir, x);
	q.c = dot(x, x) - radius * radius;
	if ((q.d = (q.b * q.b - 4.0f * q.c)) < 0)
		return (0);
	return (1);
}

float intersection_torus(t_ray *ray, t_torus torus, __float3 t_rot)
{
	__float3    x;
	__float4 equation_koefs, dots,qq,u;
	__float2 solve = (__float2){-1.f, -1.f};
	float R2, r2, Rr, dist;

	Rr = torus.R + torus.r + 1;
	if (!check_sphere(ray, Rr, torus.pos))
		return (-1.f);
	x = ray->pos - torus.pos;
	dist = length(x) - Rr;
	if (dist > 0.f)
		x += ray->dir * dist;
	else
		dist = 0.f;
	R2 = torus.R * torus.R;
	r2 = torus.r * torus.r;
	//ax4+bx3+cx2+dx1+e
	//a == 1
	dots[0] = dot(x, t_rot);
	dots[1] = dot(ray->dir, t_rot);
	dots[2] = dot(x, x);
	dots[3] = dot(x, ray->dir);
	qq[0] = 1.0f - dots[1] * dots[1];
	qq[1] = 2.0f * (dots[3] - dots[0] * dots[1]);
	qq[2] = dots[2] - dots[0] * dots[0];
	qq[3] = dots[2] + R2 - r2;
	equation_koefs[3] = 4.0f * dots[3];
	equation_koefs[2] = 2.0f * qq[3] + equation_koefs[3] * equation_koefs[3] * 0.25f - 4.0f * R2 * qq[0];
	equation_koefs[1] = equation_koefs[3] * qq[3] - 4.0f * R2 * qq[1];
	equation_koefs[0] = qq[3] * qq[3] - 4.0f * R2 * qq[2];
	fourth_degree_equation_solver(equation_koefs, &solve);

	if(solve[0] > 0)
	{
		if(solve[1] > 0)
			return (solve[0] < solve[1] ? solve[0] + dist : solve[1] + dist);
		else
			return (solve[0] + dist);
	}
	else if (solve[1] > 0)
		return (solve[1] + dist);
	else
		return(-1.f);
}
//-----------------------------------------------------------------------------^

//-------------------------------------normal---------------------------------\/

__float3	normal_rectangle(__float3  hitpoint, t_rectangle *disk, __float3 r_rot)
{
    __float3  normal;
    normal = r_rot;
    return (normal);
}
__float3	normal_disk(__float3  hitpoint, t_disk *disk, __float3 d_rot)
{
	__float3  normal;
	normal = d_rot;
	return (normal);
}

__float3	normal_sphere(__float3  hitpoint, t_sphere *sphere)
{
	__float3  normal;

	normal = hitpoint - sphere->pos;
	return (normalize(normal));
}

__float3	normal_cylinder(__float3  hitpoint, t_cylinder *cylinder, __float3 c_rot)
{
	__float3 	normal;
	float	t;

	t = dot(c_rot, cylinder->pos) -
		dot(c_rot, hitpoint);
	t /= dot(c_rot, c_rot);
	normal = hitpoint - cylinder->pos + c_rot * t;
	return (normalize(normal));
}

__float3	normal_plane(__float3  hitpoint, t_plane *plane, __float3 p_rot)
{
	__float3  normal;
	normal = p_rot;
	return (normal);
}

__float3	normal_cone(__float3  hitpoint, t_cone *cone, __float3 c_rot)
{
	__float3  normal;
	hitpoint -= cone->pos;
	normal = hitpoint - (cone->tng * cone->tng + 1.f) * c_rot * dot(hitpoint,c_rot);
	return (normalize(normal));
}

__float3	normal_torus(__float3  hitpoint, t_torus *torus, __float3 t_rot)
{
	__float3  normal;

	hitpoint -= torus->pos;
	normal = hitpoint - dot(hitpoint, t_rot) * t_rot;
	normal = normalize(normal);
	normal = hitpoint - normal * torus->R;
	return (normalize(normal));
}

float3		get_normal_obj(float3 hitpoint, t_ray ray, t_obj *hitobj)
{
	float3 n;
	switch (hitobj->type)
	{
		case sphere:
			n = normal_sphere(hitpoint, &(hitobj->primitive.sphere));
			break;
		case cylinder:
			n = normal_cylinder(hitpoint, &(hitobj->primitive.cylinder), hitobj->basis.u);
			break;
		case plane:
			n = hitobj->basis.u;//normal_plane(hitpoint, &(hitobj->primitive.plane), hitobj->basis.u);
			break;
		case cone:
			n = normal_cone(hitpoint, &(hitobj->primitive.cone), hitobj->basis.u);
			break;
		case torus:
			n = normal_torus(hitpoint, &(hitobj->primitive.torus), hitobj->basis.u);
			break;
		case disk:
			n = hitobj->basis.u;//normal_disk(hitpoint, &(hitobj->primitive.disk), hitobj->basis.u);
			break;
        case rectangle:
            n = hitobj->basis.u;//normal_rectangle(hitpoint, &(hitobj->primitive.rectangle), hitobj->basis.u);
		default:
			break;
	}
	return n;
}
//-----------------------------------------------------------------------------^