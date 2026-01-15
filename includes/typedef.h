/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:25:46 by stefuntu          #+#    #+#             */
/*   Updated: 2026/01/15 18:09:13 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include <stdint.h>
# include <stdlib.h>
# include <stdbool.h>

typedef float	t_vec3 __attribute__ ((vector_size ((sizeof(float) * 4))));

typedef struct s_img_info
{
	int		bpp;
	int		line_length;
	int		endian;
	char	*addr;
}				t_img_info;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	void		*img;
	t_img_info	*img_info;
}				t_mlx_data;

typedef enum e_obj_type
{
	SPHERE,
	CYLINDER,
	PLANE
}			t_obj_type;

typedef struct s_rgb
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}			t_rgb;

typedef union u_color
{
	uint32_t	value;
	t_rgb		rgb;
}			t_color;

typedef struct s_sphere
{
	t_vec3	center;
	float	radius;
	t_color	albedo;
}			t_sphere;

typedef struct s_cylinder
{
	t_vec3	center;
	float	radius;
	float	height;
	t_vec3	dir_normal;
	t_color	albedo;
}			t_cylinder;

typedef struct s_plane
{
	t_vec3	center;
	t_vec3	dir_normal;
	t_color	albedo;
}			t_plane;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	float	closest_t;
	t_vec3	attenuation;
}			t_ray;

typedef union s_object
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_plane		plane;
	// t_object	object;
}			t_object;

typedef struct s_objects
{
	bool (*intersect)(t_ray * ray, t_object * obj);
	t_object	type;
}				t_objects;


typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	upper_left;
	t_vec3	horizontal;
	t_vec3	vertical;
}			t_camera;

typedef struct s_light
{
	t_vec3	origin;
	float	brightness;
}			t_light;

typedef struct s_ambient
{
	float	color;
	t_color	albedo;
}			t_ambient;

typedef struct s_scene
{
	t_objects		*objs;
	t_camera		camera;
	t_light			light;
	t_ambient		ambient;
}				t_scene;

#endif