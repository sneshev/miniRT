#include "minirt.h"

#define T_MIN 0.000001f

bool	intersect_pl(t_ray *ray, t_object *obj)
{
	t_plane *pl;
	t_vec3	q;
	float	denom;

	pl = (t_plane *)obj;
	denom = dot(pl->normal, ray->direction);
	if (denom > -T_MIN && denom < T_MIN)
		return (false);
	q = pl->point - ray->origin;
	float t = dot(q, pl->normal) / denom;

	if (t < ray->closest_t && t > T_MIN)
	{
		ray->closest_t = t;
		ray->attenuation = pl->albedo;
		return (true);
	}
	return (false);
}

bool	intersect_sph(t_ray *ray, t_object *obj)
{
	t_sphere	*sph = (t_sphere *)obj;
	t_vec3	q = ray->origin - sph->center;
	float	a = dot(ray->direction, ray->direction);
	float	b = dot(q, ray->direction);
	float	c = dot(q, q) - sph->radius*sph->radius;
	float	disc = b*b - a*c;

	if (disc > 0) {
		float t = (-b - sqrt(b*b - a*c)) / a;
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->attenuation = sph->albedo;

			return (true);
		}
		t = (-b + sqrt(b*b - a*c)) / a;
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->attenuation = sph->albedo;
			return (true);
		}
	}
	return (false);
}

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

bool	intersect_cyl(t_ray *ray, t_object *obj)
{
	(void)ray;
	t_cylinder *cy;

	cy = (t_cylinder *)obj;
	if (hits_caps(cy, ray)) {

	}
	// if (hits_sides(cy))
	// {
// 
	// }
	return (false);
}
