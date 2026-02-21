/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/21 16:44:10 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersect_light(t_ray *ray, t_object *obj)
{
	t_sphere	sphere;
	t_light		*light;

	light = (t_light *)obj;
	sphere.center = light->origin;
	sphere.radius = 1.0f;
	if (intersect_sph(ray, (t_object *)&sphere) == true)
	{
		ray->hit.type = LIGHT;
		return (true);
	}
	return (false);
}
// bool	intersect_light(t_ray *ray, t_object *obj)
// {
// 	t_light	*light;
// 	t_vec3	q;
// 	float	b;
// 	float	c;
// 	float	disc;
// 	float	t;

// 	light = (t_light *)obj;
// 	q = ray->origin - light->origin;
// 	b = dot(q, ray->unit_dir);
// 	c = dot(q, q) - LIGHT_RADIUS*LIGHT_RADIUS;
// 	disc = b*b - c;

// 	if (disc > 0)
// 	{
// 		t = (-b - sqrtf(disc));
// 		if (t < ray->closest_t && t > T_MIN)
// 		{
// 			ray->hit.type = LIGHT;
// 			return (true);
// 		}
// 		t = (-b + sqrtf(disc));
// 		if (t < ray->closest_t && t > T_MIN)
// 		{
// 			ray->hit.type = LIGHT;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }
