/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/09 17:03:28 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	}
		return (true);
}