#include "minirt.h"

bool	intersect_sph(t_ray *ray, t_object *obj)
{
	t_sphere	*sph = (t_sphere *)obj;
	t_vec3	q = ray->origin - sph->center;
	float	b = dot(q, ray->unit_dir);
	float	c = dot(q, q) - sph->radius*sph->radius;
	float	disc = b*b - c;

	if (disc > 0) {
		float t = (-b - sqrt(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->object = obj;
			ray->hitpoint = ray->origin + ray->unit_dir * t;
			if (length(ray->origin - sph->center) > sph->radius)
				ray->normal = normalize(ray->hitpoint - sph->center);
			else
				ray->normal = normalize(sph->center - ray->hitpoint);
			return (true);
		}
		t = (-b + sqrt(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->object = obj;
			ray->hitpoint = ray->origin + ray->unit_dir * t;
			if (length(ray->origin - sph->center) > sph->radius)
				ray->normal = normalize(ray->hitpoint - sph->center);
			else
				ray->normal = normalize(sph->center - ray->hitpoint);
			return (true);
		}
	}
	return (false);
}
