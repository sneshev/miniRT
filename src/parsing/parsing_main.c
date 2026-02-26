/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/26 15:39:31 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	return_error(t_error error)
{
	if (error == ERR_FORMAT)
		printf("Error\nInvalid line\n");
	else if (error == ERR_CAMERA)
		printf("Error\nInvalid or nonexistent camera\n");
	else if (error == ERR_AMBIENT)
		printf("Error\nInvalid ambient\n");
	else if (error == ERR_LIGHT)
		printf("Error\nInvalid light\n");
	else if (error == ERR_SPHERE)
		printf("Error\nInvalid sphere\n");
	else if (error == ERR_PLANE)
		printf("Error\nInvalid plane\n");
	else if (error == ERR_CYLINDER)
		printf("Error\nInvalid cylinder\n");
	else if (error == ERR_ELEMENT)
		printf("Error\ndouble element\n");
	else if (error == ERR_MALLOC)
		printf("Error\nMalloc error\n");
	else if (error == ERR_FD)
		printf("Error\nInvalid fd\n");
	else if (error == ERR_FILE)
		printf("Error\nInvalid file\n");
	else if (error == ERR_SPECIFYER)
		printf("Error\nInvalid specifyer\n");
	return (false);
}

bool	open_file(char *file, int *fd)
{
	char	*extention;
	int		len;

	len = ft_strlen(file);
	if (len < 4)
		return (return_error(ERR_FILE));
	extention = file + len - 3;
	if (ft_strncmp(extention, ".rt", 3))
		return (return_error(ERR_FILE));
	*fd = open(file, O_RDONLY);
	if (*fd < 0)
	{
		return (return_error(ERR_FD));
	}
	return (true);
}

bool	parse_line(char *line, t_scene *scene)
{
	char	**info;

	if (!is_specifyer(line))
		return (return_error(ERR_SPECIFYER));
	info = ft_split(line, is_whitespace);
	if (!info)
		return (return_error(ERR_MALLOC));
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

	fd = -1;
	if (init_element(scene) == -1)
		return (false);
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
