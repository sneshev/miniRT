/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:43:27 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/18 22:59:46 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_sphere(char **info, t_scene *scene)
{
	t_sphere	sphere;
	float		diameter;

	if (arr_count(info) != 4)
		return (false);
	if (!valid_position(&(sphere.center), info[1]))
		return (false);
	if (!valid_float(&diameter, info[2]))
		return (false);
	sphere.radius = 0.5f * diameter;
	if (!valid_color(&(sphere.albedo), info[3]))
		return (false);
	sphere.type = SP;
	push(&(scene->objs), &sphere);
	return (true);
}

bool	parse_plane(char **info, t_scene *scene)
{
	t_plane	plane;

	if (arr_count(info) != 4)
		return (false);
	if (!valid_position(&(plane.center), info[1]))
		return (false);
	if (!valid_unit_direction(&(plane.dir), info[2]))
		return (false);
	if (!valid_color(&(plane.albedo), info[3]))
		return (false);
	plane.type = PL;
	push(&(scene->objs), &plane);
	return (true);
}

bool	parse_cylinder(char **info, t_scene *scene)
{
	t_cylinder	cylinder;
	float		diameter;

	if (arr_count(info) != 6)
		return (false);
	if (!valid_position(&(cylinder.center), info[1]))
		return (false);
	if (!valid_unit_direction(&(cylinder.dir), info[2]))
		return (false);
	if (!valid_float(&diameter, info[3]))
		return (false);
	cylinder.radius = 0.5f * diameter;
	if (!valid_float(&(cylinder.height), info[4]))
		return (false);
	if (!valid_color(&(cylinder.albedo), info[5]))
		return (false);
	cylinder.type = CY;
	push(&(scene->objs), &cylinder);
	return (true);
}
