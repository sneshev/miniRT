/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 17:19:15 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/02 17:19:15 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>

typedef float	t_vec3 __attribute__ ((vector_size ((sizeof(float) * 4))));

#  define X 0
#  define Y 1
#  define Z 2

# define U 0
# define V 1
# define W 2

# define R 0
# define G 1
# define B 2


float	length(t_vec3 v);
float	squared_length(t_vec3 v);
t_vec3	normalize(t_vec3 v);
float	dot(t_vec3 v1, t_vec3 v2);
t_vec3	cross(t_vec3 v1, t_vec3 v2);
int		vec3_compare(t_vec3 v1, t_vec3 v2);
int		vec3_diff(t_vec3 v1, t_vec3 v2);

#endif