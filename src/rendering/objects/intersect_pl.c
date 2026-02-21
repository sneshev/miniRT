#include "minirt.h"

bool	intersect_pl(t_ray *ray, t_object *obj)
{
	t_plane *pl;
	t_vec3	q;
	float	denom;

	pl = (t_plane *)obj;
	denom = dot(pl->normal, ray->unit_dir);
	if (denom > -T_MIN && denom < T_MIN)
		return (false);
	q = pl->point - ray->origin;
	float t = dot(q, pl->normal) / denom;

	if (t < ray->closest_t && t > T_MIN)
	{
		ray->closest_t = t;
		ray->hit.type = PLANE;
		ray->hit.albedo = pl->albedo;
		ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
		if (dot(ray->unit_dir, pl->normal) < 0)
			ray->hit.normal = pl->normal;
		else
			ray->hit.normal = -pl->normal;
		return (true);
	}
	return (false);
}
