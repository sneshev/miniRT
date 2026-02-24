/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:55 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/24 13:03:35 by sneshev          ###   ########.fr       */
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
