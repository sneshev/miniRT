#include "minirt.h"

#define T_MIN 0.000001f

bool	intersect_pl(t_ray *ray, t_object *obj)
{
	t_plane *pl;
	t_vec3	q;
	float	denom;

	pl = (t_plane *)obj;
	denom = dot(pl->dir, ray->direction);
	if (denom > -T_MIN && denom < T_MIN)
		return (false);
	q = pl->center - ray->origin;
	float t = dot(q, pl->dir) / denom;

	if (t < ray->closest_t && t > T_MIN)
	{
		ray->closest_t = t;
		// ray->attenuation = pl->albedo;
		return (true);
	}
	return (false);
}

bool	intersect_sph(t_ray *ray, t_object *obj)
{
	(void)ray;	
	(void)obj;	
	// t_vec3

	return (false);

}

bool	intersect_cyl(t_ray *ray, t_object *obj)
{
	(void)ray;
	(void)obj;

	return (false);
}
