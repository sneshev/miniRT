/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:48 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/25 15:47:00 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamicarr.h"
/* create ft_realloc */
/* fix ft_memcpy err */

#include <string.h>

#define DARR_EXPAN_ADD 4
#define DARR_EXPAN_MUL 1


static t_vec_meta	*access_meta(void *arr)
{
	return ((t_vec_meta *)arr) - 1;
}

size_t	get_count(void	*arr_ptr)
{
	t_vec_meta	*meta;

	meta = access_meta(*(void **)arr_ptr);
	return (meta->count);
}

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

int	reallocate_array(t_vec_meta **meta_p, void **arr)
{
	t_vec_meta	*meta;
	size_t		new_size;

	meta = *meta_p;
	meta->capacity = meta->capacity * DARR_EXPAN_MUL + DARR_EXPAN_ADD;
	new_size = sizeof(t_vec_meta) + meta->capacity * meta->elem_size;

	meta = realloc(meta, new_size);
	if (!meta)
		return (-1);

	*meta_p = meta;
	*arr = (void *)(meta + 1);
	return (1);
}

int	push(void *arr_ptr, void *elem, size_t el_size)
{
	t_vec_meta	*meta;
	void 		**arr;

	arr = (void **)arr_ptr;
	meta = ((t_vec_meta *)(*arr)) - 1;
	if (meta->count == meta->capacity)
	{
		if (reallocate_array(&meta, arr) == -1)
			return (-1);
		meta = access_meta(*arr);
	}
	if (el_size <= 0)
		el_size = meta->elem_size;
	memcpy((char *)(*arr) + meta->count * meta->elem_size, elem, el_size);
	// ft_memcpy((char *)(*arr) + meta->count * meta->elem_size, elem, meta->elem_size);
	meta->count++;
	return (1);
}