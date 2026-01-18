/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/18 20:48:06 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_line(char *line, t_scene *scene, t_element *element)
{
	char	**info;
	bool	ret_status;

	info = ft_split(line, is_whitespace);
	if (!info)
		return (false);
	if (!str_diff(*info, "C") && valid_element('C', element))
		ret_status = parse_camera(info, &(scene->camera));
	else if (!str_diff(*info, "A") && valid_element('A', element))
		ret_status = parse_ambient(info, &(scene->ambient));
	else if (!str_diff(*info, "L") && valid_element('L', element))
		ret_status = parse_light(info, &(scene->light));
	else if (!str_diff(*info, "sp"))
		ret_status = parse_sphere(info, scene);
	else if (!str_diff(*info, "pl"))
		ret_status = parse_plane(info, scene);
	else if (!str_diff(*info, "cy"))
		ret_status = parse_cylinder(info, scene);
	else
		ret_status = false;
	free_arr(info);
	return (ret_status);
}

bool	check_line(char **line)
{
	int	len;
	
	len = ft_strlen(*line);
	if (len > 1 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	if (is_whitespace(**line) ||
		is_whitespace((*line)[ft_strlen(*line) - 1]))
		return (false);
	return (true);
}

bool	is_valid_input(char *file, t_scene *scene)
{
	int			fd;
	char		*line;
	t_status	status;
	t_element	element;

	init_element(&element);
	fd = open(file, O_RDONLY);
	while (1)
	{
		status = get_next_line(&line, fd);
		if (status == GNL_ERROR)
			return (false);
		if (*line && check_line(&line) == false)
			return (free(line), false);
		if (*line && !is_newline(*line))
		{
			if (parse_line(line, scene, &element) == false)
				return (free(line), get_next_line(&line, fd), false);
		}
		free(line);
		if (status == GNL_EOF)
			break ;
	}
	return (true);
}
