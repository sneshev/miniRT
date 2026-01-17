/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/16 12:30:43 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	print_vec3(char const *s, t_vec3 v)
{
	printf("%s: %f, %f, %f\n", s, v[X], v[Y], v[Z]);
}

void	print_color(char const *s, t_color color)
{
	printf("%s: %d, %d, %d\n", s, color.r, color.g, color.b);
}

void	print_scene(t_scene *scene)
{
	// print camera
	print_vec3("C origin", scene->camera.origin);
	print_vec3("C upper_left", scene->camera.upper_left);
	print_vec3("C horizontal", scene->camera.horizontal);
	print_vec3("C vertical", scene->camera.vertical);
	
	// print sphere
	print_vec3("sp center", scene->objs->sphere.center);
	printf("sp radius: %f\n", scene->objs->sphere.radius);
	print_color("sp albedo", scene->objs->sphere.albedo);
}

// void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

//CHANGE GNL TO NOT RETURN NEWLINE
int main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	t_scene scene;
	scene.objs = malloc(2 * sizeof(t_object));
	if (!scene.objs)
		return (1);
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