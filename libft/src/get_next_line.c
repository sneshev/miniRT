/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:41:17 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/18 20:42:00 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_status	last_line(char **line, char **ptr)
{
	*line = ft_strdup(*ptr);
	if (!*line)
		return (exit_status(ptr, GNL_ERROR));
	return (exit_status(ptr, GNL_EOF));
}

t_status	return_line(char **line, char **ptr)
{
	int		x;
	char	*temp;

	x = find_newline(*ptr);
	*line = ft_substr(*ptr, 0, x);
	if (!*line)
		return (exit_status(ptr, GNL_ERROR));
	temp = ft_substr(*ptr, x, ft_strlen(*ptr));
	free(*ptr);
	*ptr = temp;
	return (GNL_OK);
}

t_status	gnl_strjoin(char **buf, char **ptr)
{
	char	*temp;

	temp = ft_strjoin(*ptr, *buf);
	if (!temp)
		return (GNL_ERROR);
	free(*buf);
	*buf = NULL;
	free(*ptr);
	*ptr = temp;
	return (GNL_OK);
}

t_status	get_next_line(char **line, int fd)
{
	static char	*ptr = NULL;
	char		*buf;
	int			n;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (exit_status(&ptr, GNL_ERROR));
	while (1)
	{
		if (find_newline(ptr))
			return (return_line(line, &ptr));
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (exit_status(&ptr, GNL_ERROR));
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (free(buf), exit_status(&ptr, GNL_ERROR));
		if (n == 0)
			return (free(buf), last_line(line, &ptr));
		buf[n] = '\0';
		if (gnl_strjoin(&buf, &ptr) == GNL_ERROR)
			return (free(buf), exit_status(&ptr, GNL_ERROR));
	}
}
