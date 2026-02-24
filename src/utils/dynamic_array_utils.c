/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:41:10 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 16:41:11 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamicarray.h"

#define DARR_EXPAN_ADD 4
#define DARR_EXPAN_MUL 1

t_vec_meta	*access_meta(void *arr)
{
	return (((t_vec_meta *)arr) - 1);
}

size_t	get_count(void	*arr_ptr)
{
	t_vec_meta	*meta;

	meta = access_meta(*(void **)arr_ptr);
	return (meta->count);
}

int	reallocate_array(t_vec_meta **meta_p, void **arr)
{
	t_vec_meta	*meta;
	size_t		old_size;
	size_t		new_size;

	meta = *meta_p;
	old_size = sizeof(t_vec_meta) + meta->capacity * meta->elem_size;
	meta->capacity = meta->capacity * DARR_EXPAN_MUL + DARR_EXPAN_ADD;
	new_size = sizeof(t_vec_meta) + meta->capacity * meta->elem_size;
	meta = ft_realloc(meta, old_size, new_size);
	if (!meta)
		return (-1);
	*meta_p = meta;
	*arr = (void *)(meta + 1);
	return (1);
}
