/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/31 16:28:01 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/libft.h"
# include "dynamicarray.h"
# include "vec3.h"
# include "parsing.h"
# include "typedef.h"
# include <stdio.h>
# include <fcntl.h>
# include <float.h>


# define HEIGHT	350
# define WIDTH	500

# define RAYSPERPIXEL 20
# define MAX_DEPTH 10

#define T_MIN 0.000001f

// render
void render(t_mlx_data *data, t_scene *scene);

// mlx stuff
int		init_minilibx(t_data *d);
void	free_data_exit(t_data *data, int exitcode);
void	put_image_pixel(t_mlx_data *data, int x, int y, t_vec3 color);

// temp
void	print_vec3(char const *s, t_vec3 *v);
// void	print_color(char const *s, t__vec3 color);
// void	print_camera(t_camera camera);
// void	print_ambient(t_ambient ambient);
// void	print_light(t_light light);
// void	print_sphere(t_sphere sphere);
// void	print_plane(t_plane plane);
// void	print_cylinder(t_cylinder cylinder);
// void	print_scene(t_scene *scene);

// utils
void	free_arr(char **arr);
void	print_arr(char **arr);
int		arr_count(char **arr);



#endif