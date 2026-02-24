/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sph.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:17:29 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 13:18:29 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	solve_quadratic_ez(float b, float c, float t[2]);

static void	fill_ray_info(t_sphere *sph, t_ray *ray, float t)
{
	ray->hit.type = SPHERE;
	ray->closest_t = t;
	ray->hit.albedo = sph->albedo;
	ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
	if (length(ray->origin - sph->center) > sph->radius)
		ray->hit.normal = normalize(ray->hit.hitpoint - sph->center);
	else
		ray->hit.normal = normalize(sph->center - ray->hit.hitpoint);
}

bool	intersect_sph(t_ray *ray, t_object *obj)
{
	t_sphere	*sph;
	t_vec3		oc;
	float		t[2];
	float		b;
	float		c;

	sph = (t_sphere *)obj;
	oc = ray->origin - sph->center;
	b = dot(oc, ray->unit_dir);
	c = dot(oc, oc) - sph->radius * sph->radius;
	if (solve_quadratic_ez(b, c, t))
	{
		if (T_MIN < t[0] && t[0] < ray->closest_t)
		{
			fill_ray_info(sph, ray, t[0]);
			return (true);
		}
		if (T_MIN < t[1] && t[1] < ray->closest_t)
		{
			fill_ray_info(sph, ray, t[1]);
			return (true);
		}
	}
	return (false);
}
