/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/23 08:35:55 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*	we need functions:
		random_in_unit_sphere
		reflect
*/

void	get_ray(t_camera *cam, t_ray *ray, float h, float v)
{
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray->origin = cam->origin;
	ray->direction = hitpoint - ray->origin;
	ray->closest_t = -1.0f;
	ray->attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
}

// void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);


t_color	get_color(t_ray *ray, t_type *objs) {
	size_t	i;
	t_color	color;
	color.value = 0xFFFF00;

	i = 0;
	while (i < get_count(&objs)) {
		t_object *object = &objs[i].object;
		i++;
		if (object->intersect(ray, object) == true)
		{
			color.value = 0x0000FF;
			continue ;
		}
	}
	return (color);
}



int main(int argc, char *argv[])
{
	t_scene scene;
	t_mlx_data data;

	if (argc != 2)
		return (1);
	scene.objs = make_dynamic_array(3, sizeof(t_type));
	if (!scene.objs)
		return (1);
	if (valid_input(argv[1], &scene) == false)
		return (free_dynamic_array(&scene), 1);
	print_scene(&scene);
	if (!init_minilibx(&data))
		return (free_dynamic_array(scene.objs), free_data_exit(&data, 1), 1);

	for (int j = HEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < WIDTH; i++) {
			t_ray ray;
			get_ray(&scene.camera, &ray, i, j);

			t_color color = get_color(&ray, scene.objs);
			put_image_pixel(&data, i, HEIGHT - j, color);
		}
	}

	
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
	free_dynamic_array(&scene);
	free_data_exit(&data, 0);
	return (0);
}






