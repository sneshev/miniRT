/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:58:45 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/09 17:08:05 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <sys/time.h>
#include "minirt.h"

void render(t_mlx_data *data, t_scene *scene);

// intersect
bool	intersect_sph(t_ray *ray, t_object *obj);
bool	intersect_pl(t_ray *ray, t_object *obj);
bool	intersect_cyl(t_ray *ray, t_object *obj);
bool	intersect_light(t_ray *ray, t_object *obj);

t_vec3	get_normal(t_object *object, t_vec3 hitpoint);

// utils
float	randf_zero_one(int n);
t_vec3	clamp(t_vec3 color);

#endif

