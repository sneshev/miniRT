/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:11:07 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/24 13:45:08 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

float	randf_zero_one(int n)
{
	(void)n;
	return (drand48());
	// struct timeval	tv;
	// long			rand;
	// float			frand;
	// if (gettimeofday(&tv, NULL) == -1)
	// 	return (0);
	// rand = tv.tv_usec;
	// rand *= rand * n;
	// rand %= 1000;
	// frand = (float)rand/1000;
	// return (frand);
}

float	randf_none_one(int n)
{
	float	m;

	m = randf_zero_one(n);
	return (m * 2 - 1);
}

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

t_vec3	random_point_in_unit_sphere(void)
{
	t_vec3	point;

	while (1)
	{
		point = new_vec3(randf_none_one(35), randf_none_one(356), randf_none_one(23546));
		if (squared_length(point) < 1.0f)
			return (point);
	}
}

void show_progress_bar (int j) {
	int progress;
	char buf[64];
	int len;

	j += 1;
	progress = 100 * (j) / HEIGHT;
	len = snprintf(buf, sizeof(buf), "\r%d%% (%d / %d rays)",
		progress, j * WIDTH * RAYSPERPIXEL, HEIGHT * WIDTH * RAYSPERPIXEL);
	write(STDERR_FILENO, buf, len);
}
