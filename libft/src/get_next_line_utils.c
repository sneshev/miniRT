/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 16:44:18 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 16:44:25 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_newline(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while(str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

t_status	exit_status(char **ptr, t_status status)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
	return (status);
}
