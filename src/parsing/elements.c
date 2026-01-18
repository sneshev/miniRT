	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:45:29 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 20:55:56 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_camera(char **info, t_camera *camera)
{
	t_vec3	viewpoint;
	t_vec3	dir;
	float	hfov;

	printf("validating camera:\n");
	if (arr_count(info) != 4)
		return (false);
	if (!valid_position(&viewpoint, info[1]))
		return (false);
	if (!valid_unit_direction(&dir, info[2]))
		return (false);
	if(!valid_hfov(&hfov, info[3]))
		return (false);
	setup_camera(camera, viewpoint, dir, hfov);
	print_camera(*camera);
	return (true);
}

bool	parse_ambient(char **info, t_ambient *ambient)
{
	printf("validating ambient:\n");
	if (arr_count(info) != 3)
		return (false);
	if (!valid_unit_range(&(ambient->lightness), info[1]))
		return (false);
	if (!valid_color(&(ambient->albedo), info[2]))
		return (false);
	print_ambient(*ambient);
	return (true);
}

bool	parse_light(char **info, t_light *light)
{
	printf("validating light:\n");
	if (arr_count(info) != 4)
		return (false);
	if (!valid_position(&(light->origin), info[1]))
		return (false);
	if (!valid_unit_range(&(light->brightness), info[2]))
		return (false);
	if (!valid_color(&(light->albedo), info[3]))
		return (false);
	print_light(*light);
	return (true);
}



