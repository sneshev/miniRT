#include "minirt.h"

#define T_MIN 0.000001f

float hits_cap(t_cylinder *cy, t_plane *pl, t_ray ray)
{
	float	t;
	t_vec3	p;

	if (intersect_pl(&ray, (t_object *)pl))
	{
		t = ray.closest_t;
		p = ray.origin + ray.direction * t;
		if (length(p - pl->point) <= cy->radius)
			return (t);
	}
	return (0);
}

bool	hits_caps(t_cylinder *cy, t_ray *ray)
{
	t_plane pl;
	float	t;

	pl.normal = cy->dir;
	pl.albedo = cy->albedo;
	pl.point = cy->center + cy->dir * (cy->height / 2);
	t = hits_cap(cy, &pl, *ray);
	if (t) {
		ray->closest_t = t;
		ray->normal = pl.normal;
		ray->attenuation = cy->albedo;
		return (true);
	}
	pl.normal *= -1;
	pl.point = cy->center - cy->dir * (cy->height / 2);
	t = hits_cap(cy, &pl, *ray);
	if (t) {
		ray->closest_t = t;
		ray->normal = pl.normal;
		ray->attenuation = cy->albedo;
		return (true);
	}
	return (false);
}

bool	hits_side(t_cylinder *cy, t_ray *ray) {
	(void)cy;
	(void)ray;

	return (false);
}

bool	intersect_cyl(t_ray *ray, t_object *obj)
{
	t_cylinder *cy;
	bool		hit;

	hit = false;
	cy = (t_cylinder *)obj;
	if (hits_caps(cy, ray)) {
		hit = true;
	}
	if (hits_side(cy, ray))
	{
		hit = true;
	}
	return (hit);
}