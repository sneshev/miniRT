/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/22 07:37:37 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	open_file(char *file, int *fd)
{
	char *extention;
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (return_error(ERR_FILE));
	extention = file +  len - 3;
	if (ft_strncmp(extention, ".rt", 3))
		return (return_error(ERR_FILE));
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		return(return_error(ERR_FD));
	}
	return (true);
}

bool	parse_line(char *line, t_scene *scene)
{
	char	**info;

	if (!is_specifyer(*line))
		return (return_error(ERR_SPECIFYER));
	info = ft_split(line, is_whitespace);
	if (!info)
		return(return_error(ERR_MALLOC));
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
	int			fd = -1;
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
			if (parse_line(line, scene) == false)
				return (free(line), get_next_line(&line, -1), close(fd), false);
		}
		free(line);
	}
	if (scene->camera.type == NONE)
		return (close(fd), return_error(ERR_CAMERA));
	return (close(fd), true);
}
