/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:27:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/08 09:07:41 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		init_minilibx(t_mlx_data *data);
void	free_data_exit(t_mlx_data *data, int exitcode);


int main(int argc, char *argv[])
{
	(void)argv;
	(void)argc;

	t_mlx_data data;
	if (!init_minilibx(&data))
		return (free_data_exit(&data, 1), 1);

	mlx_loop(data.mlx);
	
	return (0);
}
