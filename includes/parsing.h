/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 17:07:25 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/17 22:04:10 by winnitytrin      ###   ########.fr       */
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

// parse utils
bool	is_space(char c);
bool	is_newline(char c);
int		str_diff(char *s1, char *s2);
bool	valid_rgb(int *n, char *str);
bool	valid_decimal(float *d, char *str);


// parse info
bool	valid_hfov(float *hfov, char *str);
bool	valid_float(float *f, char *str);
bool	valid_dir_normal(t_vec3 *dir_normal, char *str);
bool	valid_position(t_vec3 *pos, char *str);
bool	valid_color(t_color *color, char *str);

// parsing main
bool	is_valid_input(char *file, t_scene *scene);

// parse objects
bool	parse_sphere(char **info, t_scene *scene);

// parse camera
bool	parse_camera(char **info, t_camera *camera);

#endif