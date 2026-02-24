/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:58:45 by mmisumi           #+#    #+#             */
/*   Updated: 2026/02/24 16:08:38 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include <sys/time.h>
#include "minirt.h"

void render(t_mlx_data *data, t_scene *scene);

//rays
t_ray	new_ray(t_vec3 inOrigin, t_vec3 inDirection);
t_ray	get_cam_ray(t_camera *cam, float h, float v);
t_ray	random_scatter_ray(t_ray *ray);

// intersect
bool	hit_object(t_ray *ray, t_objs *objs);
bool	intersect_sph(t_ray *ray, t_object *obj);
bool	intersect_pl(t_ray *ray, t_object *obj);
bool	intersect_cyl(t_ray *ray, t_object *obj);
bool	intersect_light(t_ray *ray, t_object *obj);

//rand
float	randf_zero_one(void);
float	randf_none_one(void);
t_vec3	random_point_in_unit_sphere(void);

// utils
void	show_progress_bar (int j);
t_vec3	clamp(t_vec3 color);
t_vec3	get_light_point(t_vec3 light_center);

#endif

