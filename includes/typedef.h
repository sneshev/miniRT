/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typedef.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:25:46 by stefuntu          #+#    #+#             */
/*   Updated: 2026/01/09 19:50:10 by stefuntu         ###   ########.fr       */
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
	t_color	albedo;
}			t_cylinder;

typedef struct s_plane
{
	t_vec3	center;
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
	t_object	object;
}			t_object;

bool sphere_intersect(t_ray * ray, t_object * obj)
{
	t_sphere *sph = (t_sphere *)obj;
	//...
	if (/*there is a t*/) {
		ray->closest_t = t;
		ray->attenuation = sph->albedo;
		return (true);
	}
	else
		return (false);
}

bool plane_intersect(t_ray * ray, t_object * obj)
{
	t_plane plane = (t_plane *)obj;
	plane. ...

	return ();
}


t_object *init_sphere() {
	t_objects *object;
	object->intersect = sphere_intersect;
	object->object = malloc(sizeof(t_sphere));
}

bool find_closest_intersection(t_objects object[], t_ray *ray) {
	if (object->intersect(ray, object[i]))
		//...;
}


typedef struct s_objects
{
	bool (*intersect)(t_ray * ray, t_object * obj);
	t_object	object;
}				t_objects;

#endif