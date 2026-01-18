/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:46:57 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/18 23:02:44 by winnitytrin      ###   ########.fr       */
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
	if (error == FORMAT)
		printf("Error: Invalid line");
	else if (error == CAMERA)
		printf("Error: Invalid camera");
	else if (error == AMBIENT)
		printf("Error: Invalid ambient");
	else if (error == LIGHT)
		printf("Error: Invalid light");
	else if (error == SPHERE)
		printf("Error: Invalid sphere");
	else if (error == PLANE)
		printf("Error: Invalid plane");
	else if (error == CYLINDER)
		printf("Error: Invalid cylinder");
	else if (error == ELEMENT)
		printf("Error: Invalid element");
	else if (error == DOUBLE)
		printf("Error: Double element");
	else if (error == MALLOC)
		printf("Error: Malloc error");
}


