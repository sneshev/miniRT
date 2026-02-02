/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:46:57 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/02/01 20:09:18 by winnitytrin      ###   ########.fr       */
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
	if (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r')
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
	if (!s1 || !s2)
		return (1);
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	print_error(t_error error)
{
	if (error == ERR_FORMAT)
		printf("Error: Invalid line\n");
	else if (error == ERR_CAMERA)
		printf("Error: Invalid camera\n");
	else if (error == ERR_AMBIENT)
		printf("Error: Invalid ambient\n");
	else if (error == ERR_LIGHT)
		printf("Error: Invalid light\n");
	else if (error == ERR_SPHERE)
		printf("Error: Invalid sphere\n");
	else if (error == ERR_PLANE)
		printf("Error: Invalid plane\n");
	else if (error == ERR_CYLINDER)
		printf("Error: Invalid cylinder\n");
	else if (error == ERR_ELEMENT)
		printf("Error: Invalid element\n");
	else if (error == ERR_DOUBLE)
		printf("Error: Double element\n");
	else if (error == ERR_MALLOC)
		printf("Error: Malloc error\n");
}

