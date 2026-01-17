/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:55 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/16 13:58:36 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		if (arr[i])
		{
			free(arr[i]);
		}
		i++;
	}
	free(arr);
}

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}
}

int	arr_count(char **arr)
{
	int	i;
	int	count;

	if (!arr)
		return (0);
	i = 0;
	count = 0;
	while (arr[i])
	{
		i++;
		count++;
	}
	return (count);
}

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

int	ft_strcmp(char *s1, char *s2)
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

bool	to_decimal(float *d, char *str)
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

bool	to_float(float *f, char *str)
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
		*f += (*str - '0');
		str++;
		if (*str && *str != '.')
			*f *= 10.0f;
	}
	if (!to_decimal(&d, str))
		return (false);
	*f = (*f + d) * sign;
	return (true);
}
