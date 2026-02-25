/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:15:23 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/25 10:29:10 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hits_side(t_cylinder *cy, t_ray *ray);

static void	fill_ray_info(t_plane *pl, t_ray *ray, float t)
{
	ray->closest_t = t;
	ray->hit.type = CYLINDER;
	ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
	ray->hit.albedo = pl->albedo;
	ray->hit.normal = pl->normal;
}

static bool	hits_cap(t_plane *pl, t_ray ray, float disc_radius, float *t)
{
	(void)disc_radius;
	if (intersect_pl(&ray, (t_object *)pl))
	{
		*t = ray.closest_t;
		pl->normal = ray.hit.normal;
		if (length(ray.hit.hitpoint - pl->point) < disc_radius)
			return (true);
	}
	return (false);
}

bool	hits_caps(t_cylinder *cy, t_ray *ray)
{
	t_plane	pl;
	float	t;
	bool	ret;

	pl.albedo = cy->albedo;
	pl.point = cy->center + (cy->unit_dir * cy->height * 0.5f);
	pl.normal = cy->unit_dir;
	ret = false;
	if (hits_cap(&pl, *ray, cy->radius, &t))
	{
		fill_ray_info(&pl, ray, t);
		ret = true;
	}
	pl.normal *= -1;
	pl.point = cy->center - (cy->unit_dir * cy->height * 0.5f);
	if (hits_cap(&pl, *ray, cy->radius, &t))
	{
		fill_ray_info(&pl, ray, t);
		ret = true;
	}
	return (ret);
}

bool	intersect_cy(t_ray *ray, t_object *obj)
{
	t_cylinder	*cy;
	bool		hit;

	hit = false;
	cy = (t_cylinder *)obj;
	if (hits_caps(cy, ray))
	{
		hit = true;
	}
	if (hits_side(cy, ray))
	{
		hit = true;
	}
	return (hit);
}
