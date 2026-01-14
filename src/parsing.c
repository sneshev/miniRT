#include "minirt.h"

#define BUFFER_SIZE 42

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
		}
		i++;
	}
	free(arr);
}

// float	add_decimals(char *str)
// {
// 	int		i;
// 	float	nbr;
// 	int		divide;

// 	i = 0;
// 	nbr = 0;
// 	divide = 10;
// 	while (str[i] != '.' && str[i])
// 		i++;
// 	if (str[i] == '.')
// 		i++;
// 	while (str[i])
// 	{
// 		nbr += str[i] - '0';
// 		if (str[i + 1] != '\0')
// 		{
// 			nbr *= 10;
// 			divide *= 10;
// 		}
// 		i++;
// 	}
// 	nbr /= divide;
// 	return (nbr);
// }

// float	to_float(char *str)
// {
// 	int		i;
// 	int		sign;
// 	float	nbr;

// 	i = 0;
// 	sign = 1;
// 	nbr = 0;
// 	if (str[i] == '-')
// 		sign = -1;
// 	if (str[i] == '+' || str[i] == '-')
// 		i++;
// 	while (str[i] && str[i] != '.')
// 	{
// 		nbr += (str[i] - '0');
// 		if (str[i + 1] != '\0' && str[i + 1] != '.')
// 			nbr *= 10;
// 		i++;
// 	}
// 	return ((nbr + add_decimals(str)) * sign);
// }

// void	fill_vec3(t_vec3 *vec3, char **split)
// {
// 	vec3[X] = ft_atoi(split[0]);
// 	vec3[Y] = ft_atoi(split[1]);
// 	vec3[Z] = ft_atoi(split[2]);
// }

// //NEED TO CHANGE FT_ATOI TO FT_ATOF
// char	**receive_information(char **line)
// {
// 	char	*temp;
// 	int		temp_len;
// 	char	**split;

// 	while (is_splace(**line) == true)
// 		(*line)++;
// 	temp = ft_strtrim(*line, " ");
// 	if (!temp)
// 		return NULL;
// 	split = ft_split(temp, ",");
// 	if (!split)
// 		return NULL;
// 	temp_len = ft_strlen(temp);
// 	while (temp_len > 0)
// 	{
// 		(*char)++;
// 		temp_len--;
// 	}
// 	return (split);
// }

// int vec3_compare(t_vec3 v1, t_vec3 v2)
// {
//     if (fabs(v1[X] - v2[X]) > 0.001f)
// 		return 1;
//     if (fabs(v1[Y] - v2[Y]) > 0.001f)
// 		return 1;
//     if (fabs(v1[Z] - v2[Z]) > 0.001f)
// 		return 1;

//     return 0;
// }

// t_vec3	get_orthogonal_base(t_vec3 dir_normal)
// {
// 	t_vec3	up;
// 	t_vec3	uvw;

// 	uvw[W] = dir_normal;
// 	up = (t_vec3){0.0f, 1.0f, 0.0f};
// 	if (vec3_compare(up, uvw[W]) == 0)
// 		up = (t_vec3){0.0f, 0.0f, -1.0f};
// 	uvw[U] = cross(up, cam->w);
// 	normalize(&uvw[U]);
// 	uvw[V] = cross(uvw[W], uvw[U]);
// 	normalize(&uvw[V]);
// 	return uvw;
// }

// void	setup_camera(t_camera *camera, t_vec3 viewpoint, t_vec3 dir_normal, float hfov)
// {
// 	float	theta;
// 	float	width;
// 	float	height;
// 	t_vec3	uvw;
// 	t_vec3	center;


// 	theta = hfov * M_PI / 180;
// 	width = 2 * tan(theta/2);
// 	height = width / ((float)WIDTH / (float)HEIGHT);

// 	uvw = get_orthogonal_base(dir_normal);

// 	cam->origin = viewpoint;
// 	center = cam->origin + uvw[W];
// 	cam->horizontal = width * uvw[U];
// 	cam->vertical = height * uvw[V];
// 	cam->upper_left = center - 0.5f * cam->horizontal + 0.5f * cam->vertical;
// }

// void	parse_camera(t_camera *camera, char *line)
// {
// 	char	**split;
// 	t_vec3	viewpoint;
// 	t_vec3	dir_normal;
// 	float	hfov;

// 	split = receive_information(&line);
// 	if (!split)
// 		return NULL;
// 	fill_vec3(&viewpoint, split);
// 	free(split);
// 	split = receive_information(&line);
// 	if (!split)
// 		return NULL;
// 	fill_vec3(&dir_normal, split);
// 	free(split);
// 	hfov = ft_atoi(line);
// 	setup_camera(camera, viewpoint, dir_normal, hfov);
// }

// void	parse_sphere(t_sphere *sphere, char *line)
// {
// 	char	**split;

// 	split = receive_information(&line);
// 	if (!split)
// 		return NULL;
// 	fill_vec3(sphere.)
// }

// void	parse_element(char *line, t_scene *scene)
// {
// 	while (is_space(*line) == true)
// 		line++;
// 	if (*line == 'C')
// 		parse_camera(scene->camera, line++);
// 	else if (*line == 's')
// 	{
// 		scene->objects[x]. = 
// 		parse_sphere(scene->objects[], line += 2);
// }

// bool	is_valid_float(char *str)
// {

// }

// bool	is_valid_vec3(char *str)
// {

// }

bool	is_valid_line(char *line)
{
	(void)line;
	return (true);
}

bool	parse_line(char *line, t_scene *scene)
{
	(void)line;
	(void)scene;
	return (true);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\v' || c == '\t')
		return (true);
	return (false);

}

bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (is_whitespace(*line) == false)
			return (false);
		line++;
	}
	return (true);
}



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


bool	is_valid_input(char *file, t_scene *scene)
{
	int		fd;
	char	*line;
	char	**split;

	fd = open(file, O_RDONLY);
	printf("succesful opening fd\n");
	if (fd < 0)
		return (printf("invalid fd\n"), false);
	line = get_next_line(fd);
	if (!line)
		return (printf("no line\n"), false);
	printf("succesful line\n");
	if (is_empty_line(line) == true)
	{
		printf("empty line\n");
		return false;
	}
	printf("nonempty line\n");
	while (line)
	{
		if (is_empty_line(line) == false)
		{
			split = ft_split(line, ' ');
			if (!split)
				return (free(line), false);
			if (is_valid_line(line) == false)
				return (free(line), free_arr(split), false);
			parse_line(line, scene);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
