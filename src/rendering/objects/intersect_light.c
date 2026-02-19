/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 18:37:07 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/19 16:51:51 by mmisumi          ###   ########.fr       */
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
		ray->object = obj;
		return (true);
	}
	return (false);
}
