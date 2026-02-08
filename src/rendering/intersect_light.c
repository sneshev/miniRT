/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/05 16:10:32 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_light(t_ray *ray, t_object *obj)
{
	t_light	*light = (t_light *)obj;

	t_vec3	q = ray->origin - light->origin;
	float	a = 1;
	float	b = dot(q, ray->unit_dir);
	float	c = dot(q, q) - T_MIN;
	float	disc = b*b - a*c;

	if (disc > 0) {
		float t = (-b - sqrt(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->object = obj;
			return (true);
		}
		t = (-b + sqrt(disc));
		if (t < ray->closest_t && t > T_MIN) {
			ray->closest_t = t;
			ray->object = obj;
			return (true);
		}
	}
	return (false);
}