#include "minirt.h"

bool	solve_quadratic(float a, float b, float c, float roots[2]);

static void	fill_ray_info(t_plane *pl, t_ray *ray, float t) {
	ray->closest_t = t;
	ray->hit.type = CYLINDER;
	ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
	ray->hit.albedo = pl->albedo;
	ray->hit.normal = pl->normal;
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
	t_vec3 d_perp;
	t_vec3 oc_perp;
	float a;
	float b;
	float c;
	float roots[2];

	d_perp = ray->unit_dir - cy->unit_dir * dot(ray->unit_dir, cy->unit_dir);
	oc_perp = oc - cy->unit_dir * dot(oc, cy->unit_dir);

	a = dot(d_perp, d_perp);
	b = 2.0f * dot(d_perp, oc_perp);
	c = dot(oc_perp, oc_perp) - cy->radius * cy->radius;
	if (solve_quadratic(a, b, c, roots))
	{
		if (T_MIN < roots[0] && roots[0] < ray->closest_t)
		{
			*t = roots[0];
			return (true);
		}
		else if (T_MIN < roots[1] && roots[1] < ray->closest_t)
		{
			*t = roots[1];
			return (true);
		}
	}
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
	ray->hit.type = CYLINDER;
	ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
	ray->hit.albedo = cy->albedo;
    // t_vec3 cp = hitpoint - cy->center;
    // t_vec3 axis_point = cy->center + cy->unit_dir * dot(cp, cy->unit_dir);
    // ray->hit.normal = normalize(axis_point - hitpoint) * -1; // points outward

	return (true);
}

bool	intersect_cyl(t_ray *ray, t_object *obj)
{
	t_cylinder *cy;
	bool		hit;

	hit = false;
	cy = (t_cylinder *)obj;
	// if (hits_caps(cy, ray)) {
	// 	hit = true;
	// }
	if (hits_side(cy, ray)) {
		hit = true;
	}
	return (hit);
}
