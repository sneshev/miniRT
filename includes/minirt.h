/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/14 19:18:26 by winnitytrin      ###   ########.fr       */
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

// parsing
bool	is_valid_input(char *file, t_scene *scene);

// utils
bool	is_space(char c);
bool	is_newline(char c);
bool	is_whitespace(char c);
bool	is_empty_line(char *line);

#endif