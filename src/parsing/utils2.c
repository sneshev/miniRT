/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:25:09 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/26 15:39:21 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	has_wrong_commas(char *str)
{
	if (*str == ',')
		return (true);
	while (*(str + 1))
	{
		if (*str == ',' && *(str + 1) == ',')
			return (true);
		str++;
	}
	if (*str == ',')
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

int	vec3_diff(t_vec3 v1, t_vec3 v2)
{
	if (fabs(v1[X] - v2[X]) > 0.001f)
		return (1);
	if (fabs(v1[Y] - v2[Y]) > 0.001f)
		return (1);
	if (fabs(v1[Z] - v2[Z]) > 0.001f)
		return (1);
	return (0);
}

void	get_orthogonal_base(t_vec3 *ortho, t_vec3 dir_normal)
{
	t_vec3	up;

	ortho[W] = dir_normal;
	up = new_vec3(0.0f, 1.0f, 0.0f);
	if (!vec3_diff(up, ortho[W]))
		up = new_vec3(0.0f, 0.0f, -1.0f);
	else if (!vec3_diff(-up, ortho[W]))
		up = new_vec3(0.0f, 0.0f, 1.0f);
	ortho[U] = normalize(cross(up, ortho[W]));
	ortho[V] = normalize(cross(ortho[W], ortho[U]));
}

void	setup_camera(
	t_camera *cam, t_vec3 viewpoint, t_vec3 dir_normal, float hfov)
{
	float	theta;
	float	width;
	float	height;
	t_vec3	ortho[3];
	t_vec3	center;

	theta = hfov * M_PI / 180;
	width = 2 * tan(theta / 2);
	height = width / ((float)WIDTH / (float)HEIGHT);
	get_orthogonal_base(ortho, dir_normal);
	cam->origin = viewpoint;
	center = cam->origin + ortho[W];
	cam->horizontal = width * ortho[U];
	cam->vertical = height * ortho[V];
	cam->upper_left = center - 0.5f * cam->horizontal + 0.5f * cam->vertical;
}
