/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/03 18:42:28 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	open_file(char *file, int *fd)
{
	// check the extension
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		return(return_error(ERR_FD));
	}
	return (true);
}

bool	check_line(char **line)
{
	int	len;
	
	len = ft_strlen(*line);
	if (len > 1 && (*line)[len - 1] == '\n')
	{
		(*line)[len - 1] = '\0';
	}
	if (is_whitespace(**line) ||
		is_whitespace((*line)[ft_strlen(*line) - 1]))
	{
		return (return_error(ERR_FORMAT));
	}
	return (true);
}

bool	is_specifyer(char c)
{
	if (c == 'C' || c == 'A' || c == 'L'
		|| c == 's' || c == 'p' || c == 'c')
	{
		return (true);
	}
	return (false);
}

bool	parse_line(char *line, t_scene *scene)
{
	char	**info;

	if (is_specifyer(*line) == false)
	{
		return (return_error(ERR_SPECIFYER));
	}
	info = ft_split(line, is_whitespace);
	if (!info)
	{
		return (return_error(ERR_MALLOC));
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
	if (open_file(file, &fd) == false)
		return (false);
	status = GNL_OK;
	while (status != GNL_EOF)
	{
		status = get_next_line(&line, fd);
		if (status == GNL_ERROR)
			return (close(fd), return_error(ERR_MALLOC));
		if (*line && !is_newline(*line))
		{
			if (check_line(&line) == false)
				return (free(line), get_next_line(&line, -1), close(fd), false);
			if (parse_line(line, scene) == false)
				return (free(line), get_next_line(&line, -1), close(fd), false);
		}
		free(line);
	}
	if (scene->camera.type == NONE)
		return (close(fd), return_error(ERR_CAMERA));
	return (close(fd), true);
}
