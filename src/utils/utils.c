/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:55 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/24 16:32:22 by sneshev          ###   ########.fr       */
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

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	t_vec_meta	*new_meta;

	if (new_size < 1 || new_size <= old_size)
		return (ptr);
	new_meta = (t_vec_meta *)malloc(new_size);
	if (!new_meta)
		return (NULL);
	ft_memmove(new_meta, ptr, old_size);
	free(ptr);
	return (new_meta);
}
