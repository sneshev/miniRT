#include "minirt.h"

#define R 0
#define G 1
#define B 2

void	get_ray(t_camera *cam, t_ray *ray, float h, float v)
{
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray->origin = cam->origin;
	ray->direction = hitpoint - ray->origin;
	normalize(&ray->direction);
	ray->closest_t = FLT_MAX;
	ray->attenuation.value = 0xFFFFFF;
}

t_color	get_color(t_ray *ray, t_type *objs) {
	size_t	i;

	i = 0;
	while (i < get_count(&objs)) {
		t_object *object = &objs[i].object;
		i++;
		if (object->intersect(ray, object) == true)
		{
			
			continue ;
		}
	}
	return (ray->attenuation);
}

#include <sys/time.h>
float	randf_zero_one(int n)
{
	struct timeval	tv;
	long			rand;
	float			frand;
	if (gettimeofday(&tv, NULL) == -1)
		return (0);
	rand = tv.tv_usec;
	rand *= rand * n;
	rand %= 1000;
	frand = (float)rand/1000;
	return (frand);
}

//problem is the next pixel is NOT at +1.0f 
t_color	monte_carlo_color(t_type *objs, int i, int j)
{
	uint64_t	rgb[3];
	t_color		color;
	uint32_t	i;
	t_ray		ray;

	
	i = 0;
	rgb[R] = 0;
	rgb[G] = 0;
	rgb[B] = 0;
	while (i < RAYSPERPIXEL)
	{
		float h = (float)i + randf_zero_one(123)/(float)WIDTH;
		float v = (float)j + randf_zero_one(99912)/(float)HEIGHT;
		get_ray(&scene->camera, &ray, h, v);

		color = get_color(&ray, objs);
		rgb[R] += color.rgb.r;
		rgb[G] += color.rgb.g;
		rgb[B] += color.rgb.b;
		i++;
	}
	color.rgb.r = rgb[R] / RAYSPERPIXEL;
	color.rgb.g = rgb[G] / RAYSPERPIXEL;
	color.rgb.b = rgb[B] / RAYSPERPIXEL;
	return (color);
}

void show_progress_bar (int j);

void render(t_mlx_data *data, t_scene *scene)
{
	int	i;
	int	j;

	j = 0;
	while(j < HEIGHT)
	{
		i = 0;
		while(i < WIDTH)
		{
			t_color color = monte_carlo_color(scene->objs, i, j);
			put_image_pixel(data, i, j, color);
			i++;
		}
		show_progress_bar(j);
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}
