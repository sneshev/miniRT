/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:51 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/13 16:49:28 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include "../libft/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "vec3.h"
# include "typedef.h"

# define HEIGHT	500
# define WIDTH	750

// mlx stuff
int		init_minilibx(t_mlx_data *data);
void	free_data_exit(t_mlx_data *data, int exitcode);
void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);


//utils
bool	is_space(char c);

#endif