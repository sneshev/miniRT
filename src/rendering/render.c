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
	ray->attenuation = (t_vec3){1, 1, 1};
}

t_vec3	get_color(t_ray *ray, t_type *objs) {
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
t_vec3	monte_carlo_color(t_camera *camera, t_type *objs, int x, int y)
{
	t_vec3		color;
	uint32_t	i;
	t_ray		ray;
	
	i = 0;
	color = (t_vec3){0.0f, 0.0f, 0.0f};
	while (i < RAYSPERPIXEL)
	{
		float h = ((float)x + randf_zero_one(123)) / (float)WIDTH;
		float v = ((float)y + randf_zero_one(99912)) / (float)HEIGHT;
		get_ray(camera, &ray, h, v);

		color += get_color(&ray, objs);
		i++;
	}
	color /= RAYSPERPIXEL;
	return (color);
}

void show_progress_bar (int j);

void render(t_mlx_data *data, t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			t_vec3 color = monte_carlo_color(&scene->camera, scene->objs, x, y);
			put_image_pixel(data, x, y, color);
			x++;
		}
		show_progress_bar(y);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}
