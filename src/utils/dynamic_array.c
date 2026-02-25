/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:48 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/25 11:04:21 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamicarray.h"

#include <string.h>

t_vec_meta	*access_meta(void *arr);
size_t		get_count(void	*arr_ptr);
int			reallocate_array(t_vec_meta **meta_p, void **arr);

void	free_dynamic_array(void *arr_ptr)
{
	t_vec_meta	*meta;
	void		**arr;

	arr = (void **)arr_ptr;
	meta = access_meta(*arr);
	free(meta);
}

void	*make_dynamic_array(size_t in_capacity, size_t el_size)
{
	t_vec_meta	*meta;
	void		*arr;

	if (in_capacity < 1)
		in_capacity = 1;
	meta = malloc(sizeof(t_vec_meta) + in_capacity * el_size);
	if (!meta)
		return (NULL);
	meta->elem_size = el_size;
	meta->capacity = in_capacity;
	meta->count = 0;
	arr = (void *)(meta + 1);
	return (arr);
}

int	push(void *arr_ptr, void *elem, size_t el_size)
{
	t_vec_meta	*meta;
	void		**arr;

	arr = (void **)arr_ptr;
	if (!*arr)
	{
		*arr = make_dynamic_array(3, el_size);
		if (!*arr)
			return (-1);
	}
	meta = ((t_vec_meta *)(*arr)) - 1;
	if (meta->count == meta->capacity)
	{
		if (reallocate_array(&meta, arr) == -1)
			return (-1);
		meta = access_meta(*arr);
	}
	if (el_size <= 0)
		el_size = meta->elem_size;
	ft_memcpy((char *)(*arr) + meta->count * meta->elem_size, elem, el_size);
	meta->count++;
	return (1);
}
