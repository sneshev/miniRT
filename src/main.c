/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/03 18:36:18 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int main(int argc, char *argv[])
{
	t_data	data;

	if (argc != 2)
		return (1);
	data.scene.objs = make_dynamic_array(3, sizeof(t_objs));
	if (!data.scene.objs)
		return (1);

	if (valid_input(argv[1], &data.scene) == false)
		return (free_dynamic_array(&data.scene.objs), 1);

	if (!init_minilibx(&data))
		return (free_data_exit(&data, 1), 1);

	render(&data.mlx, &data.scene);
	free_dynamic_array(&data.scene.objs);
	return (0);
}

/*	
	.check for .rt extension
	
	.add to t_ray:
		? t_vec3 hitpoint; 
		? bool	 hit;

*/




