#include "minirt.h"

/*	put meta at the back so we can also free() the arr from our code normally	*/
/* create ft_realloc */

#define DARR_EXPAN_ADD 4
#define DARR_EXPAN_MUL 1

typedef struct s_vec_meta
{
	size_t	count;
	size_t	capacity;
	size_t	elem_size;
}	t_vec_meta;

static t_vec_meta	*access_meta(void *arr)
{
	return ((t_vec_meta *)arr) - 1;
}

int	make_dynamic_array(void **arr, size_t in_capacity, size_t el_size) {
	t_vec_meta	*meta;

	meta = malloc(sizeof(t_vec_meta) + in_capacity * el_size);
	if (!meta)
		return (-1);
	if (in_capacity < 1)
		in_capacity = 1;
	meta->elem_size = el_size;
	meta->capacity = in_capacity;
	meta->count = 0;
	*arr = (void *)(meta + 1);
	return (1);
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

int	vec_push(void **arr, void *elem)
{
	t_vec_meta	*meta;

	meta = ((t_vec_meta *)(*arr)) - 1;
	if (meta->count == meta->capacity)
	{
		if (reallocate_array(&meta, arr) == -1)
			return (-1);
		meta = access_meta(*arr);
	}
	ft_memcpy((char *)(*arr) + meta->count * meta->elem_size, elem, meta->elem_size);
	meta->count++;
	return (1);
}
