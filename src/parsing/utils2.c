/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:25:09 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/02 18:33:52 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	print_error(t_error error)
{
	if (error == ERR_FORMAT)
		printf("Error: Invalid line\n");
	else if (error == ERR_CAMERA)
		printf("Error: Invalid or nonexistent camera\n");
	else if (error == ERR_AMBIENT)
		printf("Error: Invalid ambient\n");
	else if (error == ERR_LIGHT)
		printf("Error: Invalid light\n");
	else if (error == ERR_SPHERE)
		printf("Error: Invalid sphere\n");
	else if (error == ERR_PLANE)
		printf("Error: Invalid plane\n");
	else if (error == ERR_CYLINDER)
		printf("Error: Invalid cylinder\n");
	else if (error == ERR_ELEMENT)
		printf("Error: double element\n");
	else if (error == ERR_MALLOC)
		printf("Error: Malloc error\n");
}

void	get_orthogonal_base(t_vec3 *ortho, t_vec3 dir_normal)
{
	t_vec3	up;

	ortho[W] = dir_normal;
	up = (t_vec3){0.0f, 1.0f, 0.0f};
	if (vec3_compare(up, ortho[W]) == 0)
		up = (t_vec3){0.0f, 0.0f, -1.0f};
	ortho[U] = normalize(cross(up, ortho[W]));
	ortho[V] = normalize(cross(ortho[W], ortho[U]));
}

void	setup_camera(t_camera *cam, t_vec3 viewpoint, t_vec3 dir_normal, float hfov)
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
