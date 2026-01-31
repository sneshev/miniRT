/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/31 15:48:37 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_element(char **info, t_element *element, t_scene *scene)
{
	if (!str_diff(*info, "C"))
	{
		if (!valid_element('C', element))
			return (-1);
		if (parse_camera(info, &scene->camera) == false)
			return (print_error(CAMERA), -1);
		return (1);
	}
	else if (!str_diff(*info, "A"))
	{
		if (!valid_element('A', element))
			return (-1);
		if (parse_ambient(info, &scene->ambient) == false)
			return (print_error(AMBIENT), -1);
		return (1);
	}
	else if (!str_diff(*info, "L"))
	{
		if (!valid_element('L', element))
			return (-1);
		if (parse_light(info, &scene->light, scene) == false)
			return (print_error(LIGHT), -1);
		return (1);
	}
	return (0);
}

int	parse_object(char **info, t_scene *scene)
{
	if (!str_diff(*info, "sp"))
	{
		if (parse_sphere(info, scene) == false)
			return (print_error(SPHERE), -1);
		return (1);
	}
	else if (!str_diff(*info, "pl"))
	{
		if (parse_plane(info, scene) == false)
			return (print_error(PLANE), -1);
		return (1);
	}
	else if (!str_diff(*info, "cy"))
	{
		if (parse_cylinder(info, scene) == false)
			return (print_error(CYLINDER), -1);
		return (1);
	}
	return (0);
}

bool	parse_line(char *line, t_element *element, t_scene *scene)
{
	char	**info;
	int		state;
	
	info = ft_split(line, is_whitespace);
	if (!info)
		return (print_error(MALLOC), false);
	state = parse_element(info, element, scene);
	if (state == -1)
		return (free_arr(info), false);
	if (state == 1)
		return (free_arr(info), true);
	state = parse_object(info, scene);
	if (state == -1)
		return (free_arr(info), false);
	if (state == 1)
		return (free_arr(info), true);
	print_error(ELEMENT);
	return (free_arr(info), false);		
}

bool	check_line(char **line)
{
	int	len;
	
	len = ft_strlen(*line);
	if (len > 1 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	if (is_whitespace(**line) ||
		is_whitespace((*line)[ft_strlen(*line) - 1]))
		return (print_error(FORMAT), false);
	return (true);
}

int	open_file(char *file)
{
	int	fd;
	// check the extension
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(FD);
		exit(1);
	}
	return (fd);	
}

bool	valid_input(char *file, t_scene *scene)
{
	int			fd;
	char		*line;
	t_status	status;
	t_element	element;

	init_element(&element);
	fd = open_file(file);
	status = GNL_OK;
	while (status != GNL_EOF)
	{
		status = get_next_line(&line, fd);
		if (status == GNL_ERROR)
			return (print_error(MALLOC), close(fd), false);
		if (*line && check_line(&line) == false)
			return (free(line), get_next_line(&line, -1), close(fd), false);
		if (*line && !is_newline(*line))
		{
			if (parse_line(line, &element, scene) == false)
				return (free(line), get_next_line(&line, -1), close(fd), false);
		}
		free(line);
	}
	close(fd);
	return (true);
}
