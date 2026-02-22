/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/22 13:40:11 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_light(t_ray *ray, t_object *obj)
{
	t_light	*l = (t_light *)obj;
	t_vec3	q = ray->origin - l->origin;
	float	b = dot(q, ray->unit_dir);
	float	c = dot(q, q) - LIGHT_RADIUS*LIGHT_RADIUS;
	float	disc = b*b - c;

	if (disc > 0) {
		float t = (-b - sqrtf(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->hit.type = LIGHT;
			ray->hit.albedo = l->emission;
			ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
			if (length(ray->origin - l->origin) > LIGHT_RADIUS)
				ray->hit.normal = normalize(ray->hit.hitpoint - l->origin);
			else
				ray->hit.normal = normalize(l->origin - ray->hit.hitpoint);
			return (true);
		}
		t = (-b + sqrtf(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->hit.type = LIGHT;
			ray->hit.albedo = l->emission;
			ray->hit.hitpoint = ray->origin + ray->unit_dir * t;
			if (length(ray->origin - l->origin) > LIGHT_RADIUS)
				ray->hit.normal = normalize(ray->hit.hitpoint - l->origin);
			else
				ray->hit.normal = normalize(l->origin - ray->hit.hitpoint);
			return (true);
		}
	}
	return (false);
}