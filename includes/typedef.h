#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdint.h>
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
} t_obj_type;

typedef struct s_rgb
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;
}			t_rgb;

typedef union u_union
{
	uint32_t	value;
	t_rgb		rgb;
} t_color;


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
} t_object;


typedef struct s_objects
{
	bool (*intersect)(t_ray *ray, t_object *obj);
	t_object	object;
}				t_objects;



#endif