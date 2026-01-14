/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 13:41:17 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/14 13:42:37 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define BUFFER_SIZE 42

int	find_newline(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*return_line(char **ptr)
{
	int		x;
	char	*line;
	char	*temp;

	x = find_newline(*ptr);
	line = ft_substr(*ptr, 0, x);
	temp = ft_substr(*ptr, x, ft_strlen(*ptr));
	free (*ptr);
	*ptr = temp;
	return (line);
}

char	*last_line(char **ptr)
{
	char	*line;

	if (*ptr && **ptr)
	{
		line = ft_strdup(*ptr);
		free(*ptr);
		*ptr = NULL;
		return (line);
	}
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*ptr = NULL;
	char		*buf;
	char		*temp;
	int			n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (1)
	{
		if (find_newline(ptr) != -1)
			return (free(buf), return_line(&ptr));
		n = read(fd, buf, BUFFER_SIZE);
		if (n == -1)
			return (free(ptr), ptr = NULL, free(buf), NULL);
		if (n == 0)
			return (free(buf), last_line(&ptr));
		buf[n] = '\0';
		temp = ft_strjoin(ptr, buf);
		free(ptr);
		ptr = temp;
	}
	return (free(buf), NULL);
}