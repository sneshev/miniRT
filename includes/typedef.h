/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: winnitytrinnity <winnitytrinnity@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:25:46 by stefuntu          #+#    #+#             */
/*   Updated: 2026/01/31 16:00:37 by winnitytrin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPEDEF_H
# define TYPEDEF_H

# include <stdbool.h>
# include <stdint.h>

typedef float	t_vec3 __attribute__ ((vector_size (sizeof(float) * 4)));
typedef union 	u_type t_type;
typedef struct	s_object t_object;

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
	t_vec3		origin;
	t_vec3		unit_dir;
	float		closest_t;
	t_vec3		hitpoint;
	t_vec3		normal;
	t_object	*object;
}			t_ray;

typedef enum e_obj_type
{
	SP,
	PL,
	CY,
	L
}			t_obj_type;

typedef struct s_object
{
	t_obj_type	type;
	bool 		(*intersect)(t_ray * ray, t_object * obj);
	t_vec3		albedo;
}				t_object;

typedef struct s_sphere
{
	t_obj_type	type;
	bool 		(*intersect)(t_ray *ray, t_object *obj);
	t_vec3		albedo;
	t_vec3		center;
	float		radius;
}			t_sphere;

typedef struct s_cylinder
{
	t_obj_type	type;
	bool 		(*intersect)(t_ray *ray, t_object *obj);
	t_vec3		albedo;
	t_vec3		center;
	float		radius;
	float		height;
	t_vec3		unit_dir;
}			t_cylinder;

typedef struct s_plane
{
	t_obj_type	type;
	bool 		(*intersect)(t_ray *ray, t_object *obj);
	t_vec3		albedo;
	t_vec3		point;
	t_vec3		normal;
}		t_plane;

typedef struct s_light
{
	t_obj_type	type;
	bool		(*intersect)(t_ray *ray, t_object *obj);
	t_vec3		origin;
	float		brightness;
	t_vec3		albedo;
}			t_light;

typedef union u_type
{
	t_sphere	sphere;
	t_cylinder	cylinder;
	t_plane		plane;
	t_light		light;
	t_object	object;
}			t_type;

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	upper_left;
	t_vec3	horizontal;
	t_vec3	vertical;
}			t_camera;

typedef struct s_ambient
{
	float	lightness;
	t_vec3	albedo;
}			t_ambient;


typedef struct s_scene
{
	t_type			*objs;
	t_camera		camera;
	t_light			light;
	t_ambient		ambient;
}				t_scene;

typedef struct s_data
{
	t_scene		scene;
	t_mlx_data	mlx;
}				t_data;

#endif