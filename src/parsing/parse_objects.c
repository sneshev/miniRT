/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 20:43:27 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 21:34:52 by winnitytrin      ###   ########.fr       */
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
	scene->objs[0].sphere = sphere;
	return (true);
}
