/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:46:57 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 22:04:00 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

bool	is_newline(char c)
{
	if (c == '\n')
		return (true);
	return (false);
}

int	str_diff(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

bool	valid_rgb(int *n, char *str)
{
	if (ft_strlen(str) > 3 || !ft_strlen(str))
		return (false);
	*n = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		*n += (*str - '0');
		str++;
		if (*str)
			*n *= 10;
	}
	if (*n < 0 || *n > 255)
		return (false);
	return (true);
}

bool	valid_decimal(float *d, char *str)
{
	float	divide;

	*d = 0.0f;
	divide = 10.0f;
	if (*str == '.' && !*(str + 1))
		return (false);
	if (*str)
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		*d += (*str - '0');
		str++;
		if (*str)
		{
			*d *= 10.0f;
			divide *= 10.0f;
		}
	}
	*d /= divide;
	return (true);
}
