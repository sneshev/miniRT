/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/18 21:44:31 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vec3(char const *s, t_vec3 *v)
{
	printf("%s: %f, %f, %f\n", s, v[0][X], v[0][Y], v[0][Z]);
}

void	print_color(char const *s, t_color color)
{
	printf("%s: %d, %d, %d\n", s, color.r, color.g, color.b);
}

void	put_image_pixel(t_mlx_data *data, int x, int y, uint32_t color);
// 		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);


t_color	get_color(t_ray *ray_in, t_type *objs) {
	int	i;
	t_color color = (t_color){255, 255, 0};

	i = 0;
	while (i < get_count(&objs)) {
		t_object *object = &objs[i];
		if (object->intersect(ray_in, object) == true) {
			continue ;
		}
	}
	return (color);
}

//CHANGE GNL TO NOT RETURN NEWLINE
int main(int argc, char *argv[])
{
	// if (argc != 2)
	// 	return (1);
	(void)argc;
	(void)argv;

	t_vec3 upper_left = (t_vec3){-2, 1, -1};
	t_vec3 origin = 	(t_vec3){0, 0, 0};
	t_mlx_data data;
	if (!init_minilibx(&data))
		return (free_data_exit(&data, 1), 1);
	
	uint32_t color = 0x0000FF;

	for (int j = HEIGHT - 1; j >= 0; j--) {
		for (int i = 0; i < WIDTH; i++) {
			float v = 4.0f * i / WIDTH;
			float u = -2.0f * j / HEIGHT;
			t_vec3 direction = upper_left + (t_vec3){v, u, 0.0};
			t_ray ray = new_ray(&origin, &direction);
			t_type *world = make_dynamic_array(3, sizeof(t_type)); if (!world) return (1);
			// t_type sph = new_sphere((t_vec3){}, 0.5, (t_color){});
			t_type pl = new_plane();
			t_color color = get_color(&ray, world);
			put_image_pixel(&data, i, HEIGHT - j, color);
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
		reflect
*/