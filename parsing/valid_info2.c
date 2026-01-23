/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 18:15:51 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/18 22:37:49 by winnitytrin      ###   ########.fr       */
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

bool	valid_unit_direction(t_vec3 *dir, char *str)
{
	char	**split;
	float	f[3];

	split = ft_split(str, is_comma);
	if (!split)
		return (false);
	if (arr_count(split) != 3)
		return (free_arr(split), false);
	if (!valid_float(&(f[0]), split[0]))
		return (free_arr(split), false);
	if (!valid_float(&(f[1]), split[1]))
		return (free_arr(split), false);
	if (!valid_float(&(f[2]), split[2]))
		return (free_arr(split), false);
	*dir = (t_vec3){f[0], f[1], f[2]};
	if (length(*dir) != 1.0f)
		return (free_arr(split), false);
	free_arr(split);
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
