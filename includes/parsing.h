/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:07:25 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/27 17:33:53 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "typedef.h"
# include "minirt.h"

typedef struct e_element
{
	bool	camera;
	bool	ambient;
	bool	light;
}			t_element;

typedef enum e_error
{
	FORMAT,
	CAMERA,
	AMBIENT,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	ELEMENT,
	DOUBLE,
	MALLOC
}			t_error;

// parsing main
void	print_error(t_error error);
bool	valid_input(char *file, t_scene *scene);

// elements
bool	parse_camera(char **info, t_camera *camera);
bool	parse_ambient(char **info, t_ambient *ambient);
bool	parse_light(char **info, t_light *light);

// objects
bool	parse_sphere(char **info, t_scene *scene);
bool	parse_plane(char **info, t_scene *scene);
bool	parse_cylinder(char **info, t_scene *scene);

bool	intersect_pl(t_ray *ray, t_object *obj);
bool	intersect_sph(t_ray *ray, t_object *obj);
bool	intersect_cyl(t_ray *ray, t_object *obj);

// valid info
bool	valid_element(char identifyer, t_element *element);
bool	valid_unit_direction(t_vec3 *dir, char *str);
bool	valid_position(t_vec3 *pos, char *str);
bool	valid_color(t_vec3 *color, char *str);
bool	valid_hfov(float *hfov, char *str);
bool	valid_unit_range(float *f, char *str);
bool	valid_float(float *f, char *str);

// utils
bool	is_comma(char c);
bool	is_whitespace(char c);
bool	is_newline(char c);
int		str_diff(char *s1, char *s2);
void	init_element(t_element *element);

// camera utils
void	setup_camera(t_camera *cam, t_vec3 viewpoint, t_vec3 dir_normal, float hfov);

#endif