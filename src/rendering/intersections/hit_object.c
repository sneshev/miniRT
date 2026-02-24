/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:42:20 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 13:42:20 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_object(t_ray *ray, t_objs *objs)
{
	size_t		i;
	t_object	*object;

	i = 0;
	while (i < get_count(&objs))
	{
		object = &objs[i].object;
		object->intersect(ray, object);
		i++;
	}
	if (ray->hit.type == NONE)
		return (false);
	return (true);
}
