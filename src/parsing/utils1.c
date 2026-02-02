/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:46:57 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/02 18:09:46 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_element(t_scene *scene)
{
	scene->camera.type = NONE;
	scene->light.type = NONE;
	scene->light.intersect = NULL;
	scene->light.brightness = 1.0f;
	scene->light.albedo = (t_vec3){1.0f, 1.0f, 1.0f};
	scene->ambient.type = NONE;
	scene->ambient.lightness = 0.0f;
	scene->ambient.albedo = (t_vec3){0.0f, 0.0f, 0.0f};
}

bool	is_comma(char c)
{
	if (c == ',')
		return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

bool	is_newline(char c)
{
	if (c == '\n')
		return (true);
	return (false);
}

int	str_diff(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
