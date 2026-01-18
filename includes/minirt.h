/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/18 19:33:32 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
// # include "../mlx_linux/mlx.h"
// # include "../mlx_linux/mlx_int.h"
# include "vec3.h"
# include "parsing.h"
# include "typedef.h"
# include <stdio.h>
# include <fcntl.h>


# define HEIGHT	500
# define WIDTH	750

// mlx stuff
// int		init_minilibx(t_mlx_data *data);
// void	free_data_exit(t_mlx_data *data, int exitcode);
// void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);

// temp
void	print_vec3(char const *s, t_vec3 v);
void	print_color(char const *s, t_color color);
void	print_camera(t_camera camera);
void	print_ambient(t_ambient ambient);
void	print_light(t_light light);
void	print_sphere(t_sphere sphere);
void	print_plane(t_plane plane);
void	print_cylinder(t_cylinder cylinder);
void	print_scene(t_scene *scene);

// utils
void	free_arr(char **arr);
void	print_arr(char **arr);
int		arr_count(char **arr);


#endif