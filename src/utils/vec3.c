/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:57 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/15 16:13:57 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

float length(t_vec3 v)
{
	return (sqrtf(v[X] * v[X]
		 		+ v[Y] * v[Y]
				+ v[Z] * v[Z]));
}

void	normalize(t_vec3 *v)
{
	float len = length(*v);
	if (len == 0.0f) {
		*v = (t_vec3){0.0f, 0.0f, 0.0f, 0.0f};
		return ;
	}
	(*v)[X] /= len;
	(*v)[Z] /= len;
	(*v)[Y] /= len;
}

float	dot(t_vec3 v1, t_vec3 v2)
{
	return(v1[X] * v2[X]
		 + v1[Y] * v2[Y]
		 + v1[Z] * v2[Z]);
}

t_vec3 cross(t_vec3 v1, t_vec3 v2)
{
    t_vec3 v3;

    v3[X] = v1[Y] * v2[Z] - v1[Z] * v2[Y];
    v3[Y] = v1[Z] * v2[X] - v1[X] * v2[Z];
    v3[Z] = v1[X] * v2[Y] - v1[Y] * v2[X];
    return v3;
}
