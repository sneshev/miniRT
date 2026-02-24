/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:16:03 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 16:36:31 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	swapf(float *a, float *b)
{
	float	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	solve_quadratic_ez(float b, float c, float roots[2])
{
	float	disc;
	float	sqrt_disc;

	disc = b * b - c;
	if (disc > 0.0f)
	{
		sqrt_disc = sqrtf(disc);
		roots[0] = -b - sqrt_disc;
		roots[1] = -b + sqrt_disc;
		return (2);
	}
	else if (disc == 0)
	{
		roots[0] = -b;
		roots[1] = -1;
		return (1);
	}
	else
	{
		roots[0] = -1;
		roots[1] = -1;
		return (0);
	}
}

int	solve_quadratic(float a, float b, float c, float roots[2])
{
	float	disc;
	float	rev_denom;
	float	sqrt_disc;

	disc = b * b - 4 * a * c;
	if (disc > 0)
	{
		sqrt_disc = sqrtf(disc);
		rev_denom = 0.5f / a;
		roots[0] = (-b + sqrt_disc) * rev_denom;
		roots[1] = (-b - sqrt_disc) * rev_denom;
		if (roots[0] > roots[1])
			swapf(&roots[0], &roots[1]);
		return (2);
	}
	else if (disc == 0)
	{
		roots[0] = -b / (2 * a);
		roots[1] = -1;
		return (1);
	}
	else
	{
		return (roots[0] = -1, roots[1] = -1, 0);
	}
}
