/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/13 15:58:32 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"



bool is_valid_input(char *file, t_objects *objects) {
	int fd = /*open the file*/;
	while (/*the file*/) {
		char *line = get_next_line();
		//validate the line
		add_to_array(objects, get_object(line));

	}
}



void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	t_objects *objects;
	if (!is_valid_input(argv[1], &objects))
		return (1);

	t_mlx_data data;
	if (!init_minilibx(&data))
		return (free_data_exit(&data, 1), 1);
	t_color col;
	col.value = 0x0000FF;
	for (int i = 10; i < WIDTH; i++) {
		for (int j = 10; j < HEIGHT; j++) {
			put_image_pixel(&data, i, j, col);
		}
	}


	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}


/*	we need functions:
		make_unit_vector
		dot
		cross
		random_in_unit_sphere
		reflect */