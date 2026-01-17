/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:25:46 by stefuntu          #+#    #+#             */
/*   Updated: 2026/01/17 22:31:22 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include <stdbool.h>

typedef float	t_vec3 __attribute__ ((vector_size ((sizeof(float) * 4))));
typedef union u_type t_type;

typedef enum e_return_code
{
	SUCCES,
	INVALID_VEC3,
	INVALID_FLOAT,
	MALLOC_ERROR,
}			t_return_code;

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

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	float	closest_t;
	t_vec3	attenuation;
}			t_ray;

// COLOR = the final color we see after all the calculations including
// things such as albedo, light, ambient, shadow
// ALBEDO = the color of a specifik material, like red acrylic paint
// would (obviously) be red
// ATTENUATION = how much the light weakens the more it bounces
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_object
{
	bool (*intersect)(t_ray * ray, t_type * obj);
}				t_object;

typedef struct s_sphere
{
	bool 	(*intersect)(t_ray *ray, t_type *obj);
	t_vec3	center;
	float	radius;
	t_color	albedo;
}			t_sphere;

typedef struct s_cylinder
{
	bool 	(*intersect)(t_ray *ray, t_type *obj);
	t_vec3	center;
	float	radius;
	float	height;
	t_vec3	dir_normal;
	t_color	albedo;
}			t_cylinder;

typedef struct s_plane
{
	bool 	(*intersect)(t_ray *ray, t_type *obj);
	t_vec3	center;
	t_vec3	dir_normal;
	t_color	albedo;
}		t_plane;

typedef union u_type
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_plane		plane;
	t_object	object;
}			t_type;

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
	t_type			*objs;
	t_camera		camera;
	t_light			light;
	t_ambient		ambient;
}				t_scene;

#endif