/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/17 18:29:01 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_sphere(char **info, t_scene *scene)
{
	t_sphere	sphere;
	float		diameter;

	if (arr_count(info) != 4)
		return (printf("invalid sphere arr count\n"), false);
	print_arr(info);
	if (!to_vec3(&(sphere.center), info[1]))
		return (printf("invalid sphere center\n"), false);
	print_vec3("sphere center", sphere.center);
	if (!to_float(&diameter, info[2]))
		return (printf("invalid sphere radius\n"), false);
	sphere.radius = 0.5f * diameter;
	printf("sphere radius: %f\n", sphere.radius);
	if (!to_color(&(sphere.albedo), info[3]))
		return (printf("invalid color\n"), false);
	scene->objs[0].sphere = sphere;
	return (true);
}

bool	parse_line(char *line, t_scene *scene)
{
	char	**info;

	info = ft_split(line, ' ');
	if (!info)
		return (false);
	if (!ft_strcmp(*info, "C"))
		return (parse_camera(info, &(scene->camera)));
	else if (!ft_strcmp(*info, "sp"))
		return (parse_sphere(info, scene));
	else
	{
		printf("Error: Invalid identifier\n");
		return (false);
	}
	return (true);
}

// bool	parse_info(char **info, t_scene *scene)
// {
// 	// if (!ft_strcmp(*info, "A"))
// 	// 	parse_ambient(info);
// 	if (!ft_strcmp(*info, "C"))
// 		return (parse_camera(info, &(scene->camera)));
// 	// else if (!ft_strcmp(*info, "L"))
// 	// 	parse_light();
// 	else if (!ft_strcmp(*info, "sp"))
// 		return (parse_sphere(info, &(scene->objs->sphere)));
// 	// else if (!ft_strcmp(*info, "pl"))
// 	// 	parse_plane();
// 	// else if (!ft_strcmp(*info, "cy"))
// 	// 	parse_cylinder();
// 	else
// 	{
// 		printf("Error\n: Invalid identifier\n");
// 		return (false);
// 	}
// }

bool	check_line(char **line)
{
	int	len;
	
	len = ft_strlen(*line);
	if (len > 1 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	if (is_space(**line) || is_space((*line)[ft_strlen(*line) - 1]))
		return (false);
	return (true);	
}

bool	is_valid_input(char *file, t_scene *scene)
{
	int			fd;
	char		*line;
	t_status	status;

	fd = open(file, O_RDONLY);
	while (1)
	{
		status = get_next_line(&line, fd);
		if (status == GNL_ERROR)
			return (false);
		if (check_line(&line) == false)
			return (free(line), false);
		if (!is_newline(*line))
		{
			if (parse_line(line, scene) == false)
				return (free(line), false);
		}
		free(line);
		if (status == GNL_EOF)
			break ;
	}
	//check the correct elements and stuff
	return (true);
}
