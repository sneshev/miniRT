/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rand.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:05:55 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 16:10:19 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define SEED_UNDEFINED 0xFFFFFFFFu

float	randf_zero_one(void)
{
	static uint32_t	state = SEED_UNDEFINED;
	const uint32_t	a = 1140671485;
	const uint32_t	c = 12820163;
	const uint32_t	mask = (1 << 24) - 1;
	struct timeval	tv;

	if (state == SEED_UNDEFINED)
	{
		gettimeofday(&tv, NULL);
		state = tv.tv_usec & 0xFFFFFF;
		if (state == 0)
			state = 1;
	}
	state = (a * state + c) & mask;
	return ((float)state / (float)(1 << 24));
}

float	randf_none_one(void)
{
	float	m;

	m = randf_zero_one();
	return (m * 2 - 1);
}

t_vec3	random_point_in_unit_sphere(void)
{
	t_vec3	point;

	while (1)
	{
		point = new_vec3
			(randf_none_one(), randf_none_one(), randf_none_one());
		if (squared_length(point) < 1.0f)
			return (point);
	}
}
