/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/23 08:18:41 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/libft.h"
# include "dynamicarr.h"
# include "vec3.h"
# include "parsing.h"
# include "typedef.h"
# include <stdio.h>
# include <fcntl.h>


# define HEIGHT	500
# define WIDTH	750

// intersect
bool	intersect_objs(t_ray *ray, t_type objs[]);

// mlx stuff
int		init_minilibx(t_mlx_data *data);
void	free_data_exit(t_mlx_data *data, int exitcode);
void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);

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