
/*=============================PROTOTYPES=====================================*/

float3		change_of_basis(float3 vec, t_basis basis);
float3		get_texture_col(t_texture, int, int, int);
float3		get_texture_col_float(t_texture, float, float, int);

void		texture_plane(t_obj *, float3, t_texture, float2 *);
void		texture_sphere(t_obj *, float3, t_texture, float2 *);
void		texture_cylinder(t_obj *, float3, t_texture, float2 *);
void		texture_cone(t_obj *, float3, t_texture, float2 *);

/*============================================================================*/


float3		get_texture_col_float(t_texture texture, float fx, float fy,
	int tx_id)
{
	if (!texture.tx || !texture.txdata || tx_id >= texture.tx_count)
		return ((float3)(-1.f, -1.f, -1.f));

	int x = (int)(texture.txdata[tx_id].width * fx) % texture.txdata[tx_id].width;
	int y = (int)(texture.txdata[tx_id].height * fy) % texture.txdata[tx_id].height;
	int		index = texture.txdata[tx_id].start + texture.txdata[tx_id].width *
		y + x;
	float3		res = (float3)(texture.tx[index].bgra[2],
		texture.tx[index].bgra[1], texture.tx[index].bgra[0]) / 256;
	return (res);
}

float3		get_texture_col(t_texture texture, int x, int y, int tx_id)
{
	if (!texture.tx || !texture.txdata || tx_id >= texture.tx_count)
		return ((float3)(-1.f, -1.f, -1.f));
	x = x % texture.txdata[tx_id].width;
	y = y % texture.txdata[tx_id].height;
	int		index = texture.txdata[tx_id].start + texture.txdata[tx_id].width *
		y + x;
	float3		res = (float3)(texture.tx[index].bgra[2],
		texture.tx[index].bgra[1], texture.tx[index].bgra[0]);
	return (res / 256);
}

float3	change_of_basis(float3 vec, t_basis basis)
{
	float3	tmp;

	tmp.x = vec.x * basis.v.x + vec.y * basis.v.y + vec.z * basis.v.z;
	tmp.y = vec.x * basis.u.x + vec.y * basis.u.y + vec.z * basis.u.z;
	tmp.z = vec.x * basis.w.x + vec.y * basis.w.y + vec.z * basis.w.z;

	return tmp;
}

/*===========================TEXTURE MAPPING==================================*/

void	texture_plane(t_obj *plane, float3 hitpoint, t_texture texture, float2 *coord)
{
	hitpoint -= plane->primitive.plane.pos;
	hitpoint = change_of_basis(hitpoint, plane->basis);
	hitpoint /= 20;		//should be parsed as a variable
	coord->x = hitpoint.x;
	coord->y = hitpoint.z;
}

void	texture_sphere(t_obj *sphere, float3 hitpoint, t_texture texture, float2 *coord)
{
	hitpoint -= sphere->primitive.sphere.pos;
	hitpoint = change_of_basis(hitpoint, sphere->basis);
	hitpoint /= sphere->primitive.sphere.r;
	float	theta = acos(hitpoint.y) / PI;
	float2	tmp = (float2)(hitpoint.x, hitpoint.z);
	tmp = normalize(tmp);
	float	phi = acos(tmp.x) / PI_2;
	phi = hitpoint.z > 0 ? 1.f - phi : phi;
	coord->x = phi;
	coord->y = theta;
}

void	texture_cylinder(t_obj *cylinder, float3 hitpoint, t_texture texture, float2 *coord)
{
	hitpoint -= cylinder->primitive.cylinder.pos;
	hitpoint = change_of_basis(hitpoint, cylinder->basis);
	float	phi = acos(hitpoint.x / cylinder->primitive.cylinder.r) / PI_2;
	phi = hitpoint.z > 0 ? 1.f - phi : phi;
	hitpoint /= 20;		//should be parsed as a variable
	coord->x = phi;
	coord->y = -hitpoint.y;
}

void	texture_cone(t_obj *cone, float3 hitpoint, t_texture texture, float2 *coord)
{
	hitpoint -= cone->primitive.cone.pos;
	hitpoint = change_of_basis(hitpoint, cone->basis);
	float2	tmp = normalize((float2)(hitpoint.x, hitpoint.z));
	float	phi = acos(tmp.x) / PI_2;
	phi = tmp.y > 0 ? 1.f - phi : phi;
	hitpoint /= 20;		//should be parsed as a variable
	coord->x = phi;
	coord->y = -hitpoint.y;
}

/*============================================================================*/

void		get_texture_coord(t_obj *hitobj, float3 hitpoint, t_texture texture, float2 *coord)
{
	if (hitobj->type == plane)
		texture_plane(hitobj, hitpoint, texture, coord);
	else if (hitobj->type == cylinder)
		texture_cylinder(hitobj, hitpoint, texture, coord);
	else if (hitobj->type == sphere)
		texture_sphere(hitobj, hitpoint, texture, coord);
	else if (hitobj->type == cone)
		texture_cone(hitobj, hitpoint, texture, coord);
}
