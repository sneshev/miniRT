/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/19 15:46:39 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// bool	intersect_light(t_ray *ray, t_object *obj)
// {
// 	t_light	*light = (t_light *)obj;
// 	t_vec3	op;
// 	float	d;
// 	float	t;

// 	op = (light->origin - ray->origin);
// 	t = dot(op, ray->unit_dir);
// 	op = normalize(light->origin - ray->origin);
// 	d = dot(op, ray->unit_dir);
// 	if (fabs(1.0f - d) > 0.001f)
// 		return (false);
// 	if (t < ray->closest_t && t > T_MIN)
// 	{
// 		ray->closest_t = t;
// 		ray->object = obj;
// 	}
// 		return (true);
// }

bool	intersect_light(t_ray *ray, t_object *obj)
{
	t_sphere	sphere;
	t_light		*light;

	light = (t_light *)obj;
	sphere.center = light->origin;
	sphere.radius = 1.0f;
	if (intersect_sph(ray, (t_object *)&sphere) == true);
	{
		ray->object = obj;
		return (true);
	}
	return (false);
}


// bool	intersect_light(t_ray *ray, t_object *obj)
// {
// 	t_light	*light = (t_light *)obj;

// 	t_vec3	q = ray->origin - light->origin;
// 	float	a = 1;
// 	float	b = dot(q, ray->unit_dir);
// 	float	c = dot(q, q) - T_MIN;
// 	float	disc = b*b - a*c;

// 	if (disc > 0) {
// 		float t = (-b - sqrt(disc));
// 		if (t < ray->closest_t && t > T_MIN) {
// 			ray->closest_t = t;
// 			ray->object = obj;
// 			return (true);
// 		}
// 		t = (-b + sqrt(disc));
// 		if (t < ray->closest_t && t > T_MIN) {
// 			ray->closest_t = t;
// 			ray->object = obj;
// 			return (true);
// 		}
// 	}
// 	return (false);
// }