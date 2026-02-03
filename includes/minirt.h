/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/03 19:14:55 by mmisumi          ###   ########.fr       */
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
# include "render.h"
# include <stdio.h>
# include <fcntl.h>
# include <float.h>


# define HEIGHT	500
# define WIDTH	750

# define RAYSPERPIXEL 10
# define MAX_DEPTH 10

#define T_MIN 0.000001f

// render
void render(t_mlx_data *data, t_scene *scene);

// mlx stuff
int		init_minilibx(t_data *d);
void	free_data_exit(t_data *data, int exitcode);
void	put_image_pixel(t_mlx_data *data, int x, int y, t_vec3 color);

// utils
void	free_arr(char **arr);
void	print_arr(char **arr);
int		arr_count(char **arr);



#endif