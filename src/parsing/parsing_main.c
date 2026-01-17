/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:14:01 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/17 13:48:17 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define BUFFER_SIZE 33

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

	if (*ptr)
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

// typedef enum e_status
// {
// 	GNL_OK,
// 	GNL_EOF,
// 	GNL_ERROR
// }			t_status;

// int	find_newline(const char *str)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == '\n')
// 			return (i + 1);
// 		i++;
// 	}
// 	return (0);
// }

// t_status	exit_status(char **ptr, t_status status)
// {
// 	if (*ptr && **ptr)
// 		free(*ptr);
// 	*ptr = NULL;
// 	return (status);
// }

// t_status	last_line(char **line, char *ptr)
// {
// 	*line = ft_strdup(ptr);
// 	if (!*line)
// 		return (exit_status(&ptr, GNL_ERROR));
// 	if (!**line)
// 		*line = NULL;
// 	return (exit_status(&ptr, GNL_EOF));
// }

// t_status	return_line(char **line, char **ptr)
// {
// 	int		x;
// 	char	*temp;

// 	x = find_newline(*ptr);
// 	*line = ft_substr(*ptr, 0, x);
// 	if (!*line)
// 		return (exit_status(ptr, GNL_ERROR));
// 	temp = ft_substr(*ptr, x, ft_strlen(*ptr));
// 	free(*ptr);
// 	*ptr = temp;
// 	return (GNL_OK);
// }

// t_status	get_next_line(char **line, int fd)
// {
// 	static char	*ptr = NULL;
// 	char		*buf;
// 	int			n;

// 	if (!fd || BUFFER_SIZE < 1)
// 		return (GNL_ERROR);
// 	while (1)
// 	{
// 		if (find_newline(ptr))
// 			return (return_line(line, &ptr));
// 		buf = malloc(BUFFER_SIZE + 1);
// 		if (!buf)
// 			return (exit_status(&ptr, GNL_ERROR));
// 		n = read(fd, buf, BUFFER_SIZE);
// 		if (n == -1)
// 			return (free(buf), exit_status(&ptr, GNL_ERROR));
// 		if (n == 0)
// 			return (free(buf), last_line(line, ptr));
// 		buf[n] = '\0';
// 		ptr = ft_strjoin(ptr, buf);
// 		if (!ptr)
// 			return (free(buf), exit_status(&ptr, GNL_ERROR));
// 		free(buf);
// 		buf = NULL;
// 	}
// }

// int	main(void)
// {
// 	int			fd;
// 	char		*line;
// 	t_status	status;
	
// 	fd = open("test", O_RDONLY);
// 	while (get_next_line(&line, fd) != GNL_ERROR)
// 	{
// 		if (!line)
// 			break ;
// 		printf("%s", line);
// 		free(line);
// 	}
// 	return (0);
// }

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
	char	*line;
	int		len;

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
