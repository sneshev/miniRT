/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_compare.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 18:25:57 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/02 18:26:09 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

int vec3_compare(t_vec3 v1, t_vec3 v2)
{
	if (fabs(v1[X] - v2[X]) > 0.001f)
		return (1);
	if (fabs(v1[Y] - v2[Y]) > 0.001f)
		return (1);
	if (fabs(v1[Z] - v2[Z]) > 0.001f)
		return (1);

	return (0);
}

int vec3_diff(t_vec3 v1, t_vec3 v2)
{
    if (fabs(v1[X] - v2[X]) > 0.001f)
		return (1);
    if (fabs(v1[Y] - v2[Y]) > 0.001f)
		return (1);
    if (fabs(v1[Z] - v2[Z]) > 0.001f)
		return (1);

    return (0);
}
