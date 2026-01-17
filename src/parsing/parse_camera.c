/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:45:29 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/15 20:47:16 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int vec3_compare(t_vec3 v1, t_vec3 v2)
{
    if (fabs(v1[X] - v2[X]) > 0.001f)
		return 1;
    if (fabs(v1[Y] - v2[Y]) > 0.001f)
		return 1;
    if (fabs(v1[Z] - v2[Z]) > 0.001f)
		return 1;

    return 0;
}

void	get_orthogonal_base(t_vec3 *ortho, t_vec3 dir_normal)
{
	t_vec3	up;

	ortho[W] = dir_normal;
	up = (t_vec3){0.0f, 1.0f, 0.0f};
	if (vec3_compare(up, ortho[W]) == 0)
		up = (t_vec3){0.0f, 0.0f, -1.0f};
	ortho[U] = cross(up, ortho[W]);
	normalize(&ortho[U]);
	ortho[V] = cross(ortho[W], ortho[U]);
	normalize(&ortho[V]);
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

bool	parse_camera(char **info, t_camera *camera)
{
	t_vec3		viewpoint;
	t_vec3		dir_normal;
	float		hfov;

	if (arr_count(info) != 4)
		return (printf("invlaid camera arr count\n"), false);
	if (!to_vec3(&viewpoint, info[1]))
		return (printf("invalid viewpoint\n"), false);
	print_vec3("viewpoint", viewpoint);
	if (!to_vec3(&dir_normal, info[2]))
		return (printf("invalid dir_normal\n"), false);
	print_vec3("dir_normal", dir_normal);
	if (length(dir_normal) != 1)
		return (printf("not normalized\n"), false);
	if (!to_float(&hfov, info[3]))
		return (printf("invalid hfov\n"), false);
	if (hfov < 1.0f || hfov > 179.0f)
		return (printf("incorrect hfov\n"), false);
	printf("hfov: %f\n", hfov);
	setup_camera(camera, viewpoint, dir_normal, hfov);
	return (true);
}