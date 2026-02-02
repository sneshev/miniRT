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

#include "parsing.h"

bool	parse_camera(char **info, t_camera *camera)
{
	t_vec3	viewpoint;
	t_vec3	dir;
	float	hfov;

	if (arr_count(info) != 4)
		return (print_error(ERR_MALLOC), false);
	if (!valid_position(&viewpoint, info[1]))
		return (false);
	if (!valid_unit_direction(&dir, info[2]))
		return (false);
	if(!valid_hfov(&hfov, info[3]))
		return (false);
	setup_camera(camera, viewpoint, dir, hfov);
	return (true);
}

bool	parse_ambient(char **info, t_ambient *ambient)
{
	if (arr_count(info) != 3)
		return (print_error(ERR_MALLOC), false);
	if (!valid_unit_range(&(ambient->lightness), info[1]))
		return (false);
	if (!valid_color(&(ambient->albedo), info[2]))
		return (false);
	return (true);
}


bool	parse_light(char **info, t_light *light, t_scene *scene)
{
	if (arr_count(info) != 4)
		return (print_error(ERR_MALLOC), false);
	if (!valid_position(&(light->origin), info[1]))
		return (false);
	if (!valid_unit_range(&(light->brightness), info[2]))
		return (false);
	if (!valid_color(&(light->albedo), info[3]))
		return (false);
	light->intersect = intersect_light;
	push(&scene->objs, light, sizeof(t_light));
	return (true);
}

bool	parse_element(char **info, t_scene *scene)
{
	if (!str_diff(*info, "C") && valid_element('C', scene))
	{
		if (parse_camera(info, &scene->camera) == false)
			return (print_error(ERR_CAMERA), false);
		return (true);
	}
	else if (!str_diff(*info, "A") && valid_element('A', scene))
	{
		if (parse_ambient(info, &scene->ambient) == false)
			return (print_error(ERR_AMBIENT), false);
		return (true);
	}
	else if (!str_diff(*info, "L") && valid_element('L', scene))
	{
		if (parse_light(info, &scene->light, scene) == false)
			return (print_error(ERR_LIGHT), false);
		return (true);
	}
	return (false);
}

