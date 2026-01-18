/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:15:51 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/18 19:10:43 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	valid_hfov(float *hfov, char *str)
{
	if (!valid_float(hfov, str))
		return (false);
	if (*hfov < 1.0f || *hfov > 179.0f)
		return (false);
	return (true);
}

bool	valid_unit_range(float *f, char *str)
{
	if (!valid_float(f, str))
		return (false);
	if (*f < 0.0f || *f > 1.0f)
		return (false);
	return (true);
}

bool	valid_decimal(float *d, char *str)
{
	float	factor;

	*d = 0.0f;
	factor = 0.1f;
	if (*str == '.' && !*(str + 1))
		return (false);
	if (*str)
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		*d += factor * (*str - '0');
		factor *= 0.1f;
		str++;
	}
	return (true);
}

bool	valid_float(float *f, char *str)
{
	float	sign;
	float	d;

	*f = 0.0f;
	sign = 1.0f;
	if (*str == '-')
		sign = -1.0f;
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '.' || !ft_strlen(str) || ft_strlen(str) > 7)
		return (false);
	while (*str && *str != '.')
	{
		if (!ft_isdigit(*str))
			return (false);
		*f = *f * 10 + (*str - '0');
		str++;
	}
	if (!valid_decimal(&d, str))
		return (false);
	*f = (*f + d) * sign;
	return (true);
}
