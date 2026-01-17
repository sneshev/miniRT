/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/17 16:46:35 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_sphere(char **info, t_sphere *sphere)
{
	float	diameter;

	if (arr_count(info) != 4)
		return (printf("invalid sphere arr count\n"), false);
	print_arr(info);
	if (!to_vec3(&(sphere->center), info[1]))
		return (printf("invalid sphere center\n"), false);
	print_vec3("sphere center", sphere->center);
	if (!to_float(&diameter, info[2]))
		return (printf("invalid sphere radius\n"), false);
	sphere->radius = 0.5f * diameter;
	printf("sphere radius: %f\n", sphere->radius);
	if (!to_color(&(sphere->albedo), info[3]))
		return (printf("invalid color\n"), false);
	return (true);
}

bool	parse_info(char **info, t_scene *scene)
{
	// if (!ft_strcmp(*info, "A"))
	// 	parse_ambient(info);
	if (!ft_strcmp(*info, "C"))
		return (parse_camera(info, &(scene->camera)));
	// else if (!ft_strcmp(*info, "L"))
	// 	parse_light();
	else if (!ft_strcmp(*info, "sp"))
		return (parse_sphere(info, &(scene->objs->sphere)));
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

char	*get_line(int fd)
{
	char		*line;
	int			len;
	t_status	status;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	// getting rid of the newline
	len = ft_strlen(line);
	printf("line before: %s\n", line);
	printf("c: %c\n", line[len - 1]);
	if (len > 1 && line[len - 1] == '\n')
	{
		printf("line after: %s\n", line);
		line[len - 1] = '\0';
	}
	printf("c after: %c\n", line[ft_strlen(line) - 1]);
	if (is_space(line[0]) || is_space(line[ft_strlen(line) - 1]))
		return (NULL);
	return (line);
}

bool	is_valid_input(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**info;

	fd = open(file, O_RDONLY);
	line = get_line(fd);
	if (!line)
		return (printf("Error reading file\n"), false);
	while (line)
	{
		if (is_newline(*line) == false)
		{
			info = ft_split(line, ' ');
			if (!info)
				return (printf("split error\n"), free(line), false);
			if (parse_info(info, scene) == false)
				return (printf("failed parse info\n"), free(line), free_arr(info), false);
		}
		free(line);
		line = get_line(fd);
		printf("line: %s\n", line);
		if (!line)
			return (printf("Error reading file\n"), false);
	}
	return (true);
}
