/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/30 20:20:55 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int vec3_compare(t_vec3 v1, t_vec3 v2)
{
    if (fabs(v1[X] - v2[X]) > 0.001f)
		return 1;
    if (fabs(v1[Y] - v2[Y]) > 0.001f)
		return 1;
    if (fabs(v1[Z] - v2[Z]) > 0.001f)
		return 1;

    return 0;
}

bool	intersect_light(t_ray *ray, t_object *obj)
{
	t_light	*light = (t_light *)obj;
	t_vec3	op;
	float	d;
	float	t;

	op = (light->origin - ray->origin);
	t = dot(op, ray->unit_dir);
	op = normalize(light->origin - ray->origin);
	d = dot(op, ray->unit_dir);
	if (fabs(1.0f - d) > 0.001f)
		return (false);
	if (t < ray->closest_t && t > T_MIN)
	{
		ray->closest_t = t;
		ray->object = obj;
		return (true);
	}
	return (false);
}