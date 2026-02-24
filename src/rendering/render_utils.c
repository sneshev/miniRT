/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:11:07 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/24 15:03:33 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_vec3	clamp(t_vec3 color)
{
	if (color[R] > 1.0f)
		color[R] = 1.0f;
	if (color[G] > 1.0f)
		color[G] = 1.0f;
	if (color[B] > 1.0f)
		color[B] = 1.0f;
	return (color);
}

t_vec3	get_light_point(t_vec3 light_center)
{
	t_vec3	offset;

	offset = LIGHT_RADIUS * random_point_in_unit_sphere();
	return (light_center + offset);
}

void	show_progress_bar(int j)
{
	int		progress;
	char	buf[64];
	int		len;

	j += 1;
	progress = 100 * (j) / HEIGHT;
	len = snprintf(buf, sizeof(buf), "\r%d%% (%d / %d rays)",
			progress, j * WIDTH * RAYSPERPIXEL, HEIGHT * WIDTH * RAYSPERPIXEL);
	write(STDERR_FILENO, buf, len);
}
