/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/15 18:11:14 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define BUFFER_SIZE 42

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

bool	to_vec3(t_vec3 *vec3, char *str)
{
	char 	**split;
	float	f[3];

	split = ft_split(str, ',');
	if (!split)
		return (printf("split error\n"), false);
	if (arr_count(split) != 3)
		return (printf("invalid arr count\n"), false);
	if (!to_float(&(f[0]), split[0]))
		return (printf("invalid f[0]\n"), false);
	printf("f[0]: %f\n", f[0]);
	if (!to_float(&(f[1]), split[1]))
		return (printf("invlaid f[1]\n"), false);
	printf("f[1]: %f\n", f[1]);
	if (!to_float(&(f[2]), split[2]))
		return (printf("invalid f[2]\n"), false);
	printf("f[2]: %f\n", f[2]);
	*vec3 = (t_vec3){f[0], f[1], f[2]};
	return (true);
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


// bool	parse_sphere(char **info, t_scene *scene)
// {
// 	if (arr_count(info) != 3)
// 		return (printf("invalid sphere arr count\n"), false);
// 	if (to_vec3(&(scene->sphere.center)))
// }

bool	parse_info(char **info, t_scene *scene)
{
	// if (!ft_strcmp(*info, "A"))
	// 	parse_ambient(info);
	if (!ft_strcmp(*info, "C"))
		return (parse_camera(info, &(scene->camera)));
	// else if (!ft_strcmp(*info, "L"))
	// 	parse_light();
	// else if (!ft_strcmp(*info, "sp"))
	// 	return (parse_sphere(info, &(scene->objs->type.sphere)));
	// else if (!ft_strcmp(*info, "pl"))
	// 	parse_plane();
	// else if (!ft_strcmp(*info, "cy"))
	// 	parse_cylinder();
	else
	{
		printf("Error\n: Invalid identifier\n");
		return (false);
	}
}

bool	is_valid_input(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**info;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (printf("Error reading file\n"), false);
	while (line)
	{
		if (is_newline(*line) == false)
		{
			printf("line: %s\n", line);
			if (is_space(*line) || is_space(line[ft_strlen(line) - 1]))
				return (printf("space error\n"), false);
			info = ft_split(line, ' ');
			if (!info)
				return (printf("split error\n"), free(line), false);
			if (parse_info(info, scene) == false)
				return (printf("failed parse info\n"), free(line), free_arr(info), false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
