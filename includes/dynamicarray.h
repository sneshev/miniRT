#ifndef DYNAMICARRAY_H
# define DYNAMICARRAY_H

# include <stdlib.h>
# include "minirt.h"

#define ALIGN16 __attribute__((aligned(16)))

typedef struct ALIGN16 s_vec_meta
{
	size_t	count;
	size_t	capacity;
	size_t	elem_size;
}	t_vec_meta;

// dynamic array
void	free_dynamic_array(void *arr_ptr);
size_t	get_count(void	*arr_ptr);
void	*make_dynamic_array(size_t in_capacity, size_t el_size);
int		push(void *arr_ptr, void *elem, size_t el_size);








#endif