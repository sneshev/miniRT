/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:25:09 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/12 19:45:12 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	return_error(t_error error)
{
	if (error == ERR_FORMAT)
		printf("Error\nInvalid line\n");
	else if (error == ERR_CAMERA)
		printf("Error\nInvalid or nonexistent camera\n");
	else if (error == ERR_AMBIENT)
		printf("Error\nInvalid ambient\n");
	else if (error == ERR_LIGHT)
		printf("Error\nInvalid light\n");
	else if (error == ERR_SPHERE)
		printf("Error\nInvalid sphere\n");
	else if (error == ERR_PLANE)
		printf("Error\nInvalid plane\n");
	else if (error == ERR_CYLINDER)
		printf("Error\nInvalid cylinder\n");
	else if (error == ERR_ELEMENT)
		printf("Error\ndouble element\n");
	else if (error == ERR_MALLOC)
		printf("Error\nMalloc error\n");
	else if (error == ERR_FD)
		printf("Error\nInvalid fd\n");
	else if (error == ERR_FILE)
		printf("Error\nInvalid file\n");
	else if (error == ERR_SPECIFYER)
		printf("Error\nInvalid specifyer\n");
	return (false);
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
