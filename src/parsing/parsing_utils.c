/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 20:46:57 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/15 22:46:12 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	to_vec3(t_vec3 *vec3, char *str)
{
	char 	**split;
	float	f[3];

	split = ft_split(str, ',');
	if (!split)
		return (printf("split error\n"), false);
	if (arr_count(split) != 3)
		return (printf("invalid arr count\n"), false);
	if (!to_float(&(f[0]), split[0]))
		return (printf("invalid f[0]\n"), false);
	printf("f[0]: %f\n", f[0]);
	if (!to_float(&(f[1]), split[1]))
		return (printf("invlaid f[1]\n"), false);
	printf("f[1]: %f\n", f[1]);
	if (!to_float(&(f[2]), split[2]))
		return (printf("invalid f[2]\n"), false);
	printf("f[2]: %f\n", f[2]);
	*vec3 = (t_vec3){f[0], f[1], f[2]};
	return (true);
}