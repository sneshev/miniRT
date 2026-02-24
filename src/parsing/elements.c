/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:27:34 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 14:27:57 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	parse_camera(char **info, t_camera *camera)
{
	t_vec3	viewpoint;
	t_vec3	dir;
	float	hfov;

	if (arr_count(info) != 4)
		return (false);
	if (!valid_position(&viewpoint, info[1]))
		return (false);
	if (!valid_unit_direction(&dir, info[2]))
		return (false);
	if (!valid_hfov(&hfov, info[3]))
		return (false);
	setup_camera(camera, viewpoint, dir, hfov);
	return (true);
}

bool	parse_ambient(char **info, t_ambient *ambient)
{
	float	lightness;
	t_vec3	albedo;

	if (arr_count(info) != 3)
		return (false);
	if (!valid_unit_range(&lightness, info[1]))
		return (false);
	if (!valid_color(&albedo, info[2]))
		return (false);
	ambient->type = AMBIENT;
	ambient->emission = lightness * albedo;
	return (true);
}

bool	parse_light(char **info, t_light *light, t_scene *scene)
{
	float	brightness;
	t_vec3	albedo;

	if (arr_count(info) != 4)
		return (false);
	if (!valid_position(&(light->origin), info[1]))
		return (false);
	if (!valid_unit_range(&brightness, info[2]))
		return (false);
	if (!valid_color(&albedo, info[3]))
		return (false);
	light->type = LIGHT;
	light->intersect = intersect_light;
	light->emission = brightness * albedo;
	push(&scene->objs, light, sizeof(t_light));
	return (true);
}

bool	parse_element(char **info, t_scene *scene)
{
	if (!str_diff(*info, "C") && valid_element('C', scene))
	{
		if (parse_camera(info, &scene->camera) == false)
			return (return_error(ERR_CAMERA));
		return (true);
	}
	else if (!str_diff(*info, "A") && valid_element('A', scene))
	{
		if (parse_ambient(info, &scene->ambient) == false)
			return (return_error(ERR_AMBIENT));
		return (true);
	}
	else if (!str_diff(*info, "L") && valid_element('L', scene))
	{
		if (parse_light(info, &scene->light, scene) == false)
			return (return_error(ERR_LIGHT));
		return (true);
	}
	return (false);
}
