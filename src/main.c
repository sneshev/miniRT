/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/08 09:17:08 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_image_pixel(t_mlx_data *data, int x, int y, int color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

int main(int argc, char *argv[])
{
	(void)argv;
	(void)argc;

	t_mlx_data data;
	if (!init_minilibx(&data))
		return (free_data_exit(&data, 1), 1);

	mlx_loop(data.mlx);
	return (0);
}
