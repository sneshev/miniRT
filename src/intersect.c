#include "minirt.h"

bool	intersect_pl(t_ray *ray, t_object *obj)
{
	(void)ray;
	t_plane *pl = (t_plane *)obj;	
	printf("hi"); fflush(NULL);
	print_vec3("normal", pl->normal); fflush(NULL);
	print_vec3("dir", ray->direction); fflush(NULL);
	float denom = dot(pl->normal, ray->direction);
	float t = dot(pl->point, pl->normal) / denom;

	if (t < ray->closest_t && t > T_MIN)
	{
		ray->closest_t = t;

		ray->normal = pl->normal;
		// ray->attenuation = pl->albedo;
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
