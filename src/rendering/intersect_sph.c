#include "minirt.h"

#define T_MIN 0.000001f

bool	intersect_sph(t_ray *ray, t_object *obj)
{
	t_sphere	*sph = (t_sphere *)obj;
	t_vec3	q = ray->origin - sph->center;
	float	a = dot(ray->unit_dir, ray->unit_dir);
	float	b = dot(q, ray->unit_dir);
	float	c = dot(q, q) - sph->radius*sph->radius;
	float	disc = b*b - a*c;

	if (disc > 0) {
		float t = (-b - sqrt(b*b - a*c)) / a;
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->attenuation = sph->albedo;
			ray->object = obj;
			return (true);
		}
		t = (-b + sqrt(b*b - a*c)) / a;
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->attenuation = sph->albedo;
			ray->object = obj;
			return (true);
		}
	}
	return (false);
}
