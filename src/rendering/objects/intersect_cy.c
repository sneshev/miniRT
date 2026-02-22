#include "minirt.h"

static void	fill_ray_info(t_plane *pl, t_ray *ray, float t) {
	ray->closest_t = t;
	ray->hit.type = CYLINDER;
	ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
	ray->hit.albedo = pl->albedo;
	// ray->hit.normal = pl->normal;
    if (dot(ray->unit_dir, pl->normal) < 0)
        ray->hit.normal = pl->normal;
    else
        ray->hit.normal = -pl->normal;
}

static bool	hits_cap(t_plane *pl, t_ray ray, float disc_radius, float *t) {
	(void)disc_radius;
	if (intersect_pl(&ray, (t_object *)pl)) {
		*t = ray.closest_t;
		pl->normal = ray.hit.normal;
		if (length(ray.hit.hitpoint - pl->point) < disc_radius)
			return (true);
	}
	return (false);
}

//if i comment either cap, it works. The black hole is somehow the second cap at the back
bool	hits_caps(t_cylinder *cy, t_ray *ray) {
	t_plane	pl;
	float	t;
	bool	ret = false;

	pl.albedo = cy->albedo;
	pl.point = cy->center + (cy->unit_dir * cy->height * 0.5f);
	pl.normal = cy->unit_dir;

	if (hits_cap(&pl, *ray, cy->radius, &t)) {
		fill_ray_info(&pl, ray, t);
		ret = true;
	}

	pl.normal *= -1;
	pl.point = cy->center - (cy->unit_dir * cy->height * 0.5f);
	if (hits_cap(&pl, *ray, cy->radius, &t) /*t > T_MIN*/) {
		fill_ray_info(&pl, ray, t);
		ret = true;
	}
	return (ret);
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
	}
	// if (hits_side(cy, ray)) {
	// 	hit = true;
	// }
	return (hit);
}
