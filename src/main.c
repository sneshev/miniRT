/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/27 17:42:48 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*	we need functions:
		random_in_unit_sphere
		reflect
*/


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
	// print_scene(&scene);

	if (!init_minilibx(&data))
		return (free_dynamic_array(scene.objs), free_data_exit(&data, 1), 1);

	render(&data, &scene);
	
	free_dynamic_array(&scene.objs);
	free_data_exit(&data, 0);
	return (0);
}

/*add to t_ray:
	t_vec3	 normal; (of hit point)
	? t_vec3 hitpoint; 
	? bool	 hit;

	
*/




