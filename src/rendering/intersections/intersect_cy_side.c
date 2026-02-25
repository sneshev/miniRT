/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy_side.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:29:57 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/25 10:44:56 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	solve_quadratic(float a, float b, float c, float roots[2]);

static int	find_roots_cy(
	t_cylinder *cy,
	t_vec3 d_perp,
	t_vec3 oc_perp,
	float roots[2]
)
{
	float	a;
	float	b;
	float	c;

	a = dot(d_perp, d_perp);
	if (-T_MIN <= a && a <= T_MIN)
		return (false);
	b = 2.0f * dot(d_perp, oc_perp);
	c = dot(oc_perp, oc_perp) - cy->radius * cy->radius;
	return (solve_quadratic(a, b, c, roots));
}

// ∥P−C−((P−C)⋅v)v∥^2=r2
bool	hits_2d(t_cylinder *cy, t_ray *ray, float *t)
{
	t_vec3	oc;
	t_vec3	oc_perp;
	t_vec3	d_perp;
	float	roots[2];

	oc = ray->origin - cy->center;
	oc_perp = oc - cy->unit_dir * dot(oc, cy->unit_dir);
	d_perp = ray->unit_dir - cy->unit_dir * dot(ray->unit_dir, cy->unit_dir);
	if (find_roots_cy(cy, d_perp, oc_perp, roots))
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

static t_vec3	get_cy_side_normal(t_cylinder *cy, t_ray *ray, t_vec3 hitpoint)
{
	t_vec3	cp;
	t_vec3	hitpoint_proj;
	t_vec3	normal;

	cp = hitpoint - cy->center;
	hitpoint_proj = cy->center + cy->unit_dir * dot(cp, cy->unit_dir);
	normal = normalize(hitpoint_proj - hitpoint);
	if (dot(ray->unit_dir, normal) > 0)
		normal *= -1;
	return (normal);
}

bool	hits_side(t_cylinder *cy, t_ray *ray)
{
	t_vec3	hitpoint;
	float	height;
	float	t;

	if (!hits_2d(cy, ray, &t))
		return (false);
	hitpoint = ray->origin + ray->unit_dir * t;
	height = dot(hitpoint - cy->center, cy->unit_dir);
	if (height < -cy->height * 0.5f || height > cy->height * 0.5f)
		return (false);
	ray->closest_t = t;
	ray->hit.type = CYLINDER;
	ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
	ray->hit.albedo = cy->albedo;
	ray->hit.normal = get_cy_side_normal(cy, ray, hitpoint);
	return (true);
}
