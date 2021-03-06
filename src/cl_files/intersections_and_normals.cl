

//#include "kernel.h"
//---------------------------------intersection-------------------------------\/

float	intersection_paraboloid(t_ray *ray,t_paraboloid paraboloid, __float3 p_rot)
{
	t_quad		q;
	__float3 	x, hitpoint;
	float dist ,u , z, len;

	x = ray->pos - paraboloid.pos;

	u = dot(ray->dir, p_rot);
	z = dot(x, p_rot);

	q.a = 2.f * (dot(ray->dir, ray->dir) - u * u);
	q.b = 2.f * (dot(ray->dir, x) - u * (z + 2.f *  paraboloid.k));
	q.c = dot(x, x) - z * (z + 4.f *  paraboloid.k);
	if ((q.d = q.b * q.b - 2.f * q.a * q.c) >= 0.f)
	{
		q.d = sqrt(q.d);
		q.res = (-q.b - q.d) / q.a;
		if (q.res > 0.f) {
			hitpoint = q.res * ray->dir + x;
			len = dot(hitpoint, p_rot);
			if (len < paraboloid.m && len > 0.f)
				return (q.res);
		}
		q.res = (-q.b + q.d) / q.a;
		if (q.res > 0.f) {
			hitpoint = q.res * ray->dir + x;
			len = dot(hitpoint, p_rot);
			if (len < paraboloid.m && len > 0.f)
				return (q.res);
		}
	}
	return (-1.f);

}

float	intersection_rectangle(t_ray *ray,t_rectangle rectangle, __global t_basis *basis)
{
	__float3 	x;
	float t;
	__float3 hitpoint;

	x = ray->pos - rectangle.pos;
	t = -dot(x, basis->u) / dot(ray->dir,basis->u);
	hitpoint = t * ray->dir + x;
	if (fabs(dot(hitpoint, basis->v)) <= rectangle.h  && fabs(dot(hitpoint, basis->w)) <= rectangle.w)
		return (t);
	return (-1.f);
}

float	intersection_rect(t_ray *ray,t_rectangle rectangle, t_basis *basis)
{
	__float3 	x;
	float t;
	__float3 hitpoint;

	x = ray->pos - rectangle.pos;
	t = -dot(x, basis->u) / dot(ray->dir,basis->u);
	hitpoint = t * ray->dir + x;
	if (fabs(dot(hitpoint, basis->v)) < rectangle.h + 0.001f && fabs(dot(hitpoint, basis->w)) < rectangle.w + 0.001f)
		return (t);
	return (-1.f);
}

float	intersection_parallelogram(t_ray *ray,t_parallelogram paral, __global t_basis *basis)
{
	t_rectangle rect;
	float3 tmp1;
	t_basis bas;
	float tmp[6], res = -1.f;

	bas = *basis;
	rect.pos = paral.pos + bas.u * paral.h;
	rect.w = paral.l;
	rect.h = paral.w;
	tmp[0] = intersection_rect(ray, rect, &bas);
	rect.pos = paral.pos - bas.u * paral.h;
	tmp[1] = intersection_rect(ray, rect, &bas);

	tmp1 = bas.w;
	bas.w = bas.u;
	bas.u = tmp1;

	rect.pos = paral.pos + bas.u * paral.l;
	rect.w = paral.h;
	rect.h = paral.w;
	tmp[2] = intersection_rect(ray, rect, &bas);
	rect.pos = paral.pos - bas.u * paral.l;
	tmp[3] = intersection_rect(ray, rect, &bas);

	tmp1 = bas.v;
	bas.v = bas.u;
	bas.u = tmp1;

	rect.pos = paral.pos + bas.u * paral.w;
	rect.w = paral.h;
	rect.h = paral.l;
	tmp[4] = intersection_rect(ray, rect, &bas);
	rect.pos = paral.pos - bas.u * paral.w;
	tmp[5] = intersection_rect(ray, rect, &bas);
	int i = -1;
	while (++i < 6)
	{

		if (res < 0 && tmp[i] > 0)
			res = tmp[i];
		else if (res > 0 && tmp[i] > 0 && tmp[i] < res)
			res = tmp[i];
	}
	return (res);
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
	dist = length(x) - sphere.r - 1.f;
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
	float	tmp[2], len;

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

float intersection_triangle(t_ray *ray,t_triangle triangle)
{
	float3 normal, x, v[3], c[3], hitpoint;
	float d, t;

	v[0] = triangle.d2 - triangle.d1;
	v[1] = triangle.d3 - triangle.d2;
	v[2] = triangle.d1 - triangle.d3;
	normal = normalize(cross(v[0], v[1]));
	x = ray->pos - triangle.d1;
	if ((d = dot(ray->dir,normal)) == 0.f)
		return (-1.f);
	t = -dot(x, normal) / d;
	hitpoint = t * ray->dir + ray->pos;
	c[0] = hitpoint - triangle.d1;
	c[1] = hitpoint - triangle.d2;
	c[2] = hitpoint - triangle.d3;
	if(length(cross(v[0],c[0]))+length(cross(v[1],c[1]))+length(cross(v[2],c[2])) < length(cross(v[1], v[2])) + EPSILON)
		return (t);
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
	double cosphi, tmp, ntmp, phi;

	tmp = -3.f / koefs.y;
	ntmp = -koefs.y / 3.f;
	cosphi = -koefs.x * 0.5f * sqrt(tmp * tmp * tmp);
	phi = acos(cosphi);
	*solve = 2.f * sqrt(ntmp) * cos(phi / 3.f) - b;
}

void fourth_degree_equation_solver(__float4 koefs, __float2 *solve)
{
	__double3 ferrari_koefs, cubic_resol_koefs;
	__double2 cubic_two_params_koefs;
	double a2, a3, a4, p2, b2, Q, cubic_solve;
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
	if ((q.b = 2.f * cubic_solve - ferrari_koefs[2]) > 0.f ) {
		q.a = q.b;
		q.b = -sqrt(q.b);
		q.c = ferrari_koefs[1] / (-2.f * q.b) + cubic_solve;
		q.d = q.a - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[0] =
					(q.res = (-q.b - q.d) / 2.f - koefs[3] / 4.f) > 0.f
					? q.res : (-q.b + q.d) / 2.f - koefs[3] / 4.f;
		}
		q.b = -q.b;
		q.c = ferrari_koefs[1] / (-2.f * q.b) + cubic_solve;
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
	__float4 equation_koefs, dots,qq;
	__float2 solve = (__float2){-1.f, -1.f};
	float R2, r2, Rr, dist;

	Rr = torus.big_r + torus.r + 1;
	if (!check_sphere(ray, Rr, torus.pos))
		return (-1.f);
	x = ray->pos - torus.pos;
	dist = length(x) - Rr;
	if (dist > 0.f)
		x += ray->dir * dist;
	else
		dist = 0.f;
	R2 = torus.big_r * torus.big_r;
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
	hitpoint -= cylinder->pos;
	normal = hitpoint - dot(hitpoint, c_rot) * c_rot;
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
	normal = hitpoint - normal * torus->big_r;
	return (normalize(normal));
}

__float3	normal_paraboloid(__float3  hitpoint, t_paraboloid *paraboloid, __float3 p_rot)
{
	__float3  normal;
	float		m;

	hitpoint = hitpoint - paraboloid->pos;
	m = dot(hitpoint, p_rot);
	normal = hitpoint - p_rot * (m + paraboloid->k);
	return (normalize(normal));
}

__float3	normal_parallelogram(__float3  hitpoint, t_parallelogram *paral, t_basis *basis)
{
	__float3  normal;
	float length;
	bool flag;
	normal = hitpoint - paral->pos;

	length = dot(normal, basis->u);
	flag = length > 0.f ? true : false;
	if(!flag)
		length = -length;
	length = length - paral->h;
	length *= length;

	if (length < 0.00001f)
		return (flag == true ? basis->u : -(basis->u));

	length = dot(normal, basis->w);
	flag = length > 0.f ? true : false;
	if(!flag)
		length = -length;
	length = length - paral->l;
	length *= length;

	if (length < 0.00001f)
		return (flag  == true ? basis->w : -(basis->w));

	length = dot(normal, basis->v);
	flag = length > 0.f ? true : false;

	return (flag  == true ? basis->v : -(basis->v));
}

__float3	normal_triangle(__float3  hitpoint, t_triangle *triangle)
{
	return (normalize(cross(triangle->d2 - triangle->d1, triangle->d3 - triangle->d2)));
}

float3		get_normal_obj(float3 hitpoint, t_obj *hitobj)
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
			n = hitobj->basis.u;
			break;
		case cone:
			n = normal_cone(hitpoint, &(hitobj->primitive.cone), hitobj->basis.u);
			break;
		case torus:
			n = normal_torus(hitpoint, &(hitobj->primitive.torus), hitobj->basis.u);
			break;
		case disk:
			n = hitobj->basis.u;
			break;
        case rectangle:
            n = hitobj->basis.u;
			break;
		case parallelogram:
			n = normal_parallelogram(hitpoint, &(hitobj->primitive.parallelogram), &(hitobj->basis));
			break;
		case triangle:
			n = normal_triangle(hitpoint, &(hitobj->primitive.triangle));
			break;
		case paraboloid:
			n = normal_paraboloid(hitpoint, &(hitobj->primitive.paraboloid), hitobj->basis.u);
			break;
		default:
			break;
	}
	return n;
}
//-----------------------------------------------------------------------------^