/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/14 16:03:12 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

int main(int argc, char *argv[])
{
	(void)argc;
	// if (argc != 2)
	// 	return (1);

	t_scene scene;
	printf("argv: %s\n", argv[1]);
	if (is_valid_input(argv[1], &scene) == false)
		return (1);

	// t_mlx_data data;
	// if (!init_minilibx(&data))
	// 	return (free_data_exit(&data, 1), 1);
	// t_color col;
	// col.value = 0x0000FF;
	// for (int i = 10; i < WIDTH; i++) {
	// 	for (int j = 10; j < HEIGHT; j++) {
	// 		put_image_pixel(&data, i, j, col);
	// 	}
	// }

	// mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	// mlx_loop(data.mlx);
	return (0);
}


/*	we need functions:
		make_unit_vector
		dot
		cross
		random_in_unit_sphere
		reflect
*/