/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/15 22:43:25 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include "../libft/libft.h"
// # include "../mlx_linux/mlx.h"
// # include "../mlx_linux/mlx_int.h"
# include "vec3.h"
# include "typedef.h"
# include <fcntl.h>


# define HEIGHT	500
# define WIDTH	750

// mlx stuff
// int		init_minilibx(t_mlx_data *data);
// void	free_data_exit(t_mlx_data *data, int exitcode);
// void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);

// main
void	print_vec3(char const *s, t_vec3 v);

// parsing
bool	is_valid_input(char *file, t_scene *scene);

// utils
void	free_arr(char **arr);
void	print_arr(char **arr);
int		arr_count(char **arr);
bool	is_space(char c);
bool	is_newline(char c);
int		ft_strcmp(char *s1, char *s2);
bool	to_float(float *f, char *str);

// parsing
bool	parse_camera(char **info, t_camera *camera);
bool	to_color(t_color *color, char *str);
bool	to_vec3(t_vec3 *vec3, char *str);

#endif