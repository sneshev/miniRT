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

t_vec3	get_orthogonal_base(t_vec3 *ortho, t_vec3 dir_normal)
{
	t_vec3	up;

	ortho[W] = dir_normal;
	up = (t_vec3){0.0f, 1.0f, 0.0f};
	if (vec3_compare(up, ortho[W]) == 0)
		up = (t_vec3){0.0f, 0.0f, -1.0f};
	ortho[U] = cross(up, cam->w);
	normalize(&ortho[U]);
	ortho[V] = cross(ortho[W], ortho[U]);
	normalize(&ortho[V]);
}

void	setup_camera(t_camera *cam, t_vec3 viewpoint, t_vec3 dir_normal, float hfov)
{
	float	theta;
	float	width;
	float	height;
	t_vec3	ortho;
	t_vec3	center;

	theta = hfov * M_PI / 180;
	width = 2 * tan(theta / 2);
	height = width / ((float)WIDTH / (float)HEIGHT);
	get_orthonogal_base(&ortho, dir_normal);
	cam->origin = viewpoint;
	center = cam->origin + ortho[W];
	cam->horizontal = width * ortho[U];
	cam->vertical = height * ortho[V];
	cam->upper_left = center - 0.5f * cam->horizontal + 0.5f * cam->vertical;
}

bool	to_vec3(t_vec3 *vec3, char *str)
{
	char	**split;

	split = ft_split(str, ',');
	if (!split)
		return (false);
	if (arr_count(split) != 3)
		return (false);
	if (!to_float(&vec3[X], *split))
		return (false);
	split++;
	if (!to_float(&vec3[Y], *split))
		return (false);
	split++;
	if (!to_float(&vec3[Z], *split))
		return (false);
	return (true);
}

bool	parse_camera(char **info, t_scene *scene)
{
	t_camera	camera;
	t_vec3		viewpoint;
	t_vec3		dir_normal;
	float		hfov;

	if (count_arr(info) != 4)
		return (printf("Error\n: Invalid element information\n"), false);
	info++;
	if (!to_vec3(&viewpoint, *info))
		return (printf("Error\n: Invalid vector\n"), false);
	info++;
	if (!to_vec3(&dir_normal, *info))
		return (false);
	if (length(dir_normal != 1))
		return (printf("Error\n: Camera orientation not normalized\n"), false);
	info++;
	if (!to_float(&hfov, *info))
		return (printf("Error\n: Invalid field of view\n"), false);
	setup_camera(scene->camera, viewpoint, dir_normal, hfov);
}

bool	parse_info(char **info, t_scene *scene)
{
	if (!ft_strcmp(*info, "A"))
		parse_ambient(info);
	else if (!ft_strcmp(*info, "C"))
		return (parse_camera(info, scene));
	else if (!ft_strcmp(*info, "L"))
		parse_light();
	else if (!ft_strcmp(*info, "sp"))
		parse_sphere();
	else if (!ft_strcmp(*info, "pl"))
		parse_plane();
	else if (!ft_strcmp(*info, "cy"))
		parse_cylinder();
	else
	{
		printf("Error\n: Invalid identifier\n");
		return (false);
	}
	return (true);
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
			info = ft_split(line, ' ');
			if (!info)
				return (free(line), printf("Error\n: Failed to allocate space\n"), false);
			if (parse_info(info, scene) == false)
				return (free(line), free_arr(info), false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

// bool	is_valid_input(char *file, t_scene *scene)
// {
// 	int		fd;
// 	char	*line;
// 	char	**info;

// 	fd = open(file, O_RDONLY);
// 	line = get_next_line(fd);
// 	if (!line)
// 		return (printf("Error reading file\n"), false);
// 	while (line)
// 	{
// 		if (is_empty_line(line) == false)
// 		{
// 			split = ft_split(line, ' ');
// 			if (!split)
// 				return (free(line), false);
// 			if (is_valid_line(line) == false)
// 				return (free(line), free_arr(split), false);
// 			parse_line(line, scene);
// 		}
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (true);
// }
