/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:29:14 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 15:03:20 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	get_cam_ray(t_camera *cam, float h, float v)
{
	t_ray	ray;
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray.origin = cam->origin;
	ray.unit_dir = normalize(hitpoint - ray.origin);
	ray.closest_t = FLT_MAX;
	ray.hit.type = NONE;
	return (ray);
}

t_ray	random_scatter_ray(t_ray *ray)
{
	t_ray	scatter_ray;

	scatter_ray.origin = ray->hit.hitpoint;
	scatter_ray.unit_dir = normalize
		(ray->hit.normal + random_point_in_unit_sphere());
	scatter_ray.closest_t = FLT_MAX;
	scatter_ray.hit.type = NONE;
	return (scatter_ray);
}

t_ray	new_ray(t_vec3 inOrigin, t_vec3 inDirection)
{
	t_ray	ray;

	ray.origin = inOrigin;
	ray.unit_dir = normalize(inDirection);
	ray.closest_t = FLT_MAX;
	ray.hit.type = NONE;
	return (ray);
}
