#include "minirt.h"

t_ray	get_ray(t_camera *cam, float h, float v)
{
	t_ray	ray;
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray.origin = cam->origin;
	ray.unit_dir = normalize(hitpoint - ray.origin);
	ray.closest_t = FLT_MAX;
	ray.hit.type = NONE;
	return (ray);
}

t_ray	random_scatter_ray(t_ray *ray)
{
	t_ray	scatter_ray;

	scatter_ray.origin = ray->hit.hitpoint;
	scatter_ray.unit_dir = normalize(ray->hit.normal + random_point_in_unit_sphere());
	scatter_ray.closest_t = FLT_MAX;
	scatter_ray.hit.type = NONE;
	return (scatter_ray);
}
