#include "minirt.h"

t_ray	new_ray(t_vec3 *in_origin, t_vec3 *in_direction) {
	t_ray ray;
	ray.origin = *in_origin;
	ray.direction = *in_direction;
	ray.closest_t = FLT_MAX;
	ray.attenuation = (t_vec3){1, 1, 1};
	return (ray);
}

t_type	new_sphere(t_vec3 in_center, float in_radius, t_color in_albedo) {
	
}