/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:25:09 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/22 20:45:08 by sneshev          ###   ########.fr       */
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

void	init_element(t_scene *scene)
{
	scene->camera.type = NONE;
	scene->light.type = NONE;
	scene->light.intersect = NULL;
	scene->light.emission = new_vec3(1.0f, 1.0f, 1.0f);
	scene->ambient.type = NONE;
	scene->ambient.emission = new_vec3(0.0f, 0.0f, 0.0f);
}

void	get_orthogonal_base(t_vec3 *ortho, t_vec3 dir_normal)
{
	t_vec3	up;

	ortho[W] = dir_normal;
	printf("%f", ortho[W][3]); fflush(NULL);
	up = new_vec3(0.0f, 1.0f, 0.0f);
	if (vec3_compare(up, ortho[W]) == 0)
		up = new_vec3(0.0f, 0.0f, -1.0f);
	ortho[U] = normalize(cross(up, ortho[W]));
	printf("%f", ortho[U][3]); fflush(NULL);
	ortho[V] = normalize(cross(ortho[W], ortho[U]));
	printf("%f", ortho[V][3]); fflush(NULL);
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
