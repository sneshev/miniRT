#include "minirt.h"

#define T_MIN 0.000001f

float hits_cap(t_cylinder *cy, t_plane *pl, t_ray ray)
{
	float	t;
	t_vec3	p;

	if (intersect_pl(&ray, (t_object *)pl))
	{
		t = ray.closest_t;
		p = ray.origin + ray.unit_dir * t;
		if (length(p - pl->point) <= cy->radius)
			return (t);
	}
	return (false);
}

bool	hits_caps(t_cylinder *cy, t_ray *ray)
{
	t_plane pl;
	float	t;

	pl.normal = cy->unit_dir;
	pl.albedo = cy->albedo;
	pl.point = cy->center + cy->unit_dir * (cy->height / 2);
	t = hits_cap(cy, &pl, *ray);
	if (t > T_MIN) {
		ray->closest_t = t;
		ray->attenuation = cy->albedo;
		return (true);
	}
	pl.normal *= -1;
	pl.point = cy->center - cy->unit_dir * (cy->height / 2);
	t = hits_cap(cy, &pl, *ray);
	if (t > T_MIN) {
		ray->closest_t = t;
		ray->attenuation = cy->albedo;
		return (true);
	}
	return (false);
}

bool	hits_2d(t_cylinder *cy, t_ray *ray, float *t, t_vec3 oc) 
{
	t_vec3 d_perp = ray->unit_dir - cy->unit_dir * dot(ray->unit_dir, cy->unit_dir);
	t_vec3 oc_perp = oc - cy->unit_dir * dot(oc, cy->unit_dir);

	float a = dot(d_perp, d_perp);
	float b = 2.0f * dot(d_perp, oc_perp);
	float c = dot(oc_perp, oc_perp) - cy->radius * cy->radius;

	float disc = b*b - 4*a*c;
	if (disc < 0)
		return (false);
	*t = (-b - sqrtf(disc)) / (2*a);
	if (*t >= T_MIN && *t < ray->closest_t)
		return (true);
	*t = (-b + sqrtf(disc)) / (2*a);
	if (*t >= T_MIN && *t < ray->closest_t)
		return (true);
	return (false);
}


bool	hits_side(t_cylinder *cy, t_ray *ray)
{
	t_vec3 hitpoint;
	float height;
	float t;

	if (!hits_2d(cy, ray, &t, ray->origin - cy->center))
		return (false);

	hitpoint = ray->origin + ray->unit_dir * t;
	height = dot(hitpoint - cy->center, cy->unit_dir);

	if (height < -cy->height * 0.5f || height > cy->height * 0.5f)
		return (false);

	ray->closest_t = t;
	ray->attenuation = cy->albedo;

	return (true);
}

bool	intersect_cyl(t_ray *ray, t_object *obj)
{
	t_cylinder *cy;
	bool		hit;

	hit = false;
	cy = (t_cylinder *)obj;
	if (hits_caps(cy, ray)) {
		hit = true;
		ray->object = obj;
	}
	if (hits_side(cy, ray)) {
		hit = true;
		ray->object = obj;
	}
	return (hit);
}
