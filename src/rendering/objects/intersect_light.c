/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/23 14:50:30 by mmisumi          ###   ########.fr       */
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
			return (true);
		}
		t = (-b + sqrtf(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->hit.type = LIGHT;
			return (true);
		}
	}
	return (false);
}