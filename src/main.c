/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/29 16:10:55 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*	we need functions:
		random_in_unit_sphere
		reflect
*/


int main(int argc, char *argv[])
{
	t_data	d;

	if (argc != 2)
		return (1);
	d.scene.objs = make_dynamic_array(3, sizeof(t_type));
	if (!d.scene.objs)
		return (1);
	if (valid_input(argv[1], &d.scene) == false)
		return (free_dynamic_array(&d.scene), 1);
	// print_scene(&scene);

	if (!init_minilibx(&d.mlx))
		return (free_dynamic_array(d.scene.objs), free_data_exit(&d.mlx, 1), 1);

	render(&d.mlx, &d.scene);
	free_dynamic_array(d.scene.objs);
	return (0);
}

/*	.add to t_ray:
		? t_vec3 hitpoint; 
		? bool	 hit;

	.free_dynamic array on free_data_exit()
		->need to do it from the keyhook, no code after mlx_loop in render()


	.close fd:
==12892== FILE DESCRIPTORS: 8 open (3 std) at exit.
==12892== Open file descriptor 3: test
==12892==    at 0x4BC41A5: open (open64.c:41)
==12892==    by 0x10B964: valid_input (parsing_main.c:110)
==12892==    by 0x10A9B2: main (main.c:31)
	
*/




