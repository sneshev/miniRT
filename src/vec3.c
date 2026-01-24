/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:13:57 by mmisumi           #+#    #+#             */
/*   Updated: 2026/01/24 07:42:06 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

float length(t_vec3 *v)
{
	return (sqrtf(v[0][X] * v[0][X]
		 		+ v[0][Y] * v[0][Y]
				+ v[0][Z] * v[0][Z]));
}

void	normalize(t_vec3 *v)
{
	float len;

	len = length(v);
	if (len == 0.0f)
	{
		*v = (t_vec3){0.0f, 0.0f, 0.0f, 0.0f};
		return ;
	}
	(*v)[X] /= len;
	(*v)[Z] /= len;
	(*v)[Y] /= len;
}

float	dot(t_vec3 *v1, t_vec3 *v2)
{
	return(v1[0][X] * v2[0][X]
		 + v1[0][Y] * v2[0][Y]
		 + v1[0][Z] * v2[0][Z]);
}

t_vec3 cross(t_vec3 *v1, t_vec3 *v2)
{
    t_vec3 v3;

    v3[X] = v1[0][Y] * v2[0][Z] - v1[0][Z] * v2[0][Y];
    v3[Y] = v1[0][Z] * v2[0][X] - v1[0][X] * v2[0][Z];
    v3[Z] = v1[0][X] * v2[0][Y] - v1[0][Y] * v2[0][X];
    return v3;
}
