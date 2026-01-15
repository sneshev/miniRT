/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/15 17:46:34 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	print_vec3(char const *s, t_vec3 v)
{
	printf("%s: %f, %f, %f\n", s, v[X], v[Y], v[Z]);
}

void	print_obj(t_sphere *sphere)
{
	print_vec3("center", sphere->center);
	printf("radius: %f\n", sphere->radius);
	printf("albedo: %u\n", sphere->albedo.value);
}

void	print_scene(t_scene *scene)
{
	// print camera
	print_vec3("origin", scene->camera.origin);
	print_vec3("upper_left", scene->camera.upper_left);
	print_vec3("horizontal", scene->camera.horizontal);
	print_vec3("vertical", scene->camera.vertical);
	
	// print_sphere(scene->objects->object.sphere);
}

// void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	t_scene scene;
	printf("argv: %s\n", argv[1]);
	if (is_valid_input(argv[1], &scene) == false)
	{	printf("\nINVALID INPUT\n\n");
		return (1);
	}
	printf("\nVALID INPUT\n\n");
	print_scene(&scene);
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