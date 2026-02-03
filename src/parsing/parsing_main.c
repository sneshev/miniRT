/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/03 16:56:40 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	open_file(char *file)
{
	int	fd;
	// check the extension
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		print_error(ERR_FD);
		exit(1);
	}
	return (fd);
}

bool	check_line(char **line)
{
	int	len;
	
	len = ft_strlen(*line);
	if (len == 0)
		return (false);
	if (len > 1 && (*line)[len - 1] == '\n')
		(*line)[len - 1] = '\0';
	if (is_whitespace(**line) ||
		is_whitespace((*line)[ft_strlen(*line) - 1]))
		return (print_error(ERR_FORMAT), false);
	return (true);
}

bool	parse_line(char *line, t_scene *scene)
{
	char	**info;

	info = ft_split(line, is_whitespace);
	if (!info)
	{
		print_error(ERR_MALLOC);
		return (false);
	}
	if (parse_element(info, scene) == false
		&& parse_object(info, scene) == false)
	{
		free_arr(info);
		return (false);
	}
	free_arr(info);
	return (true);
}



bool	valid_input(char *file, t_scene *scene)
{
	int			fd;
	char		*line;
	t_status	status;

	init_element(scene);
	fd = open_file(file);
	status = GNL_OK;
	while (status != GNL_EOF)
	{
		status = get_next_line(&line, fd);
		if (status == GNL_ERROR)
			return (print_error(ERR_MALLOC), close(fd), false);
		if (check_line(&line) == false)
			return (free(line), get_next_line(&line, -1), close(fd), false);
		if (*line && !is_newline(*line))
		{
			if (parse_line(line, scene) == false)
				return (free(line), get_next_line(&line, -1), close(fd), false);
		}
		free(line);
	}
	if (scene->camera.type == NONE)
		return (print_error(ERR_CAMERA), false);
	return (close(fd), true);
}
