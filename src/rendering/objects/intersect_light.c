/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/24 13:30:39 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
int	solve_quadratic_ez(float b, float c, float roots[2]);

bool	intersect_light(t_ray *ray, t_object *obj)
{
	t_light	*l;
	t_vec3	q;
	float	b;
	float	c;
	float	t[2];

	l = (t_light *)obj;
	q = ray->origin - l->origin;
	b = dot(q, ray->unit_dir);
	c = dot(q, q) - LIGHT_RADIUS * LIGHT_RADIUS;
	if (solve_quadratic_ez(b, c, t))
	{
		if (T_MIN < t[0] && t[0] < ray->closest_t)
		{
			ray->closest_t = t[0];
			return (ray->hit.type = LIGHT, true);
		}
		if (T_MIN < t[1] && t[1] < ray->closest_t)
		{
			ray->closest_t = t[1];
			return (ray->hit.type = LIGHT, true);
		}
	}
	return (false);
}
