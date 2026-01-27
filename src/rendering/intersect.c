#include "minirt.h"

#define T_MIN 0.000001f

bool	intersect_pl(t_ray *ray, t_object *obj)
{
	t_plane *pl = (t_plane *)obj;

	float denom = dot(pl->dir, ray->direction);
	if (denom > -T_MIN && denom < T_MIN)
		return (false);
	t_vec3 dist = pl->center - ray->origin;
	float t = dot(dist, pl->dir) / denom;

	if (t < ray->closest_t && t > T_MIN)
	{
		return (true);
	}
	return (false);
}

bool	intersect_sph(t_ray *ray, t_object *obj)
{
	(void)ray;
	(void)obj;

	return (false);

}

bool	intersect_cyl(t_ray *ray, t_object *obj)
{
	(void)ray;
	(void)obj;

	return (false);
}
