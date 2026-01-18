/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/18 21:17:03 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	get_ray(t_camera *cam, t_ray *ray, float h, float v)
// {
// 	t_vec3	hitpoint;

// 	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
// 	ray->origin = cam->origin;
// 	ray->direction = hitpoint - ray->origin;
// 	ray->closest_t = -1.0f;
// 	ray->attenuation = ?;
// }

// void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);

//CHANGE GNL TO NOT RETURN NEWLINE
int main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);

	t_scene scene;
	// scene.objs = malloc(3 * sizeof(t_type));
	scene.objs = make_dynamic_array(3, sizeof(t_type));
	if (!scene.objs)
		return (1);
	printf("argv: %s\n", argv[1]);
	if (is_valid_input(argv[1], &scene) == false)
	{	printf("\nINVALID INPUT\n\n");
		free(scene.objs);
		return (1);
	}
	printf("\nVALID INPUT\n\n");
	print_scene(&scene);
	free(scene.objs);
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