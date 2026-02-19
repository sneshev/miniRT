/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:11:07 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/19 17:28:49 by mmisumi          ###   ########.fr       */
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
