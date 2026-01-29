/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/29 16:39:45 by stefuntu         ###   ########.fr       */
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
		return (free_dynamic_array(&d.scene.objs), 1);
	// print_scene(&scene);

	if (!init_minilibx(&d))
		return (free_data_exit(&d, 1), 1);

	render(&d.mlx, &d.scene);
	free_dynamic_array(d.scene.objs);
	return (0);
}

/*	
	.check for .rt extension
	
	.add to t_ray:
		? t_vec3 hitpoint; 
		? bool	 hit;

*/




