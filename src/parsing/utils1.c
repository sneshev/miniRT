/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:46:57 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/26 15:55:51 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_comma(char c)
{
	if (c == ',')
		return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == '\n')
		return (true);
	return (false);
}

bool	is_newline(char c)
{
	if (c == '\n')
		return (true);
	return (false);
}

static bool	is_space(char c)
{
	if (c >= 9 && c <= 13)
		return (true);
	if (c == ' ')
		return (true);
	return (false);
}

bool	is_specifyer(char *str)
{
	if (*str == 'C' || *str == 'A' || *str == 'L')
	{
		if (is_space(*(str + 1)))
			return (true);
	}
	if (!strncmp(str, "sp", 2) || !strncmp(str, "pl", 2)
		|| !strncmp(str, "cy", 2))
	{
		if (is_space(*(str + 2)))
			return (true);
	}
	return (false);
}
