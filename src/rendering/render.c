#include "minirt.h"

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

void	get_ray(t_camera *cam, t_ray *ray, float h, float v)
{
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray->origin = cam->origin;
	ray->unit_dir = normalize(hitpoint - ray->origin);
	ray->closest_t = FLT_MAX;
	ray->attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
}

// // get the closest hit: the closest t, albedo and pointer to the object
// void	get_closest_hit(t_ray *ray, t_type *objs)
// {
// 	size_t		i;
// 	t_object	*object;

// 	i = 0;
// 	while (i < get_count(&objs))
// 	{
// 		object = &objs[i].object;
// 		object->intersect(ray, object);
// 		i++;
// 	}
// }

// t_vec3	random_point_in_unit_sphere(void)
// {
// 	t_vec3	point;

// 	while (1)
// 	{
// 		point = (t_vec3){randf_zero_one(35), randf_zero_one(356), randf_zero_one(23546)};
// 		if (squared_length(point) < 1.0f)
// 			break ;
// 	}
// 	return (point);
// }

// t_vec3	random_scatter_ray(t_ray *ray)
// {
// 	t_vec3	normal;
// 	t_vec3	center;
// 	t_ray	scatter;

// 	if (ray->object.type == SP)
// 		normal = normalize(ray->hitpoint - ray->object.center);
// 	else if (ray->object.type == PL)
// 		normal = ray->object.normal;
// 	// nothing for cylinder yet

// 	scatter.origin = ray->hitpoint;
// 	scatter.unit_dir = ray->hitpoint + normal + random_point_in_unit_sphere();
// 	scatter.closest_t = FLT_MAX;
// 	scatter.attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
// 	return (scatter);
// }

// t_vec3	get_light_ray(t_light *light, t_ray *ray)
// {
// 	t_ray	l_ray;

// 	l_ray.origin = ray->hitpoint;
// 	l_ray.unit_dir = normalize(light->origin - ray->hitpoint);
// 	l_ray.closest_t = FLT_MAX;
// 	l_ray.attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
// 	return (l_ray);
// }

// t_vec3	get_color(t_scene *scene, t_ray *ray, t_type *objs, int depth)
// {
// 	t_vec3	hitpoint;
// 	t_ray	l_ray;
// 	t_ray	scatter_ray;
// 	t_vec3	color;

// 	get_closest_hit(ray, objs);
// 	ray->hitpoint = ray->origin + ray->closest_t * ray->unit_dir;
// 	l_ray = get_light_ray(&scene->light, ray);
// 	get_closest_t(&l_ray, objs);
// 	scatter_ray = random_scatter_ray(ray);
// 	if (scene->light.center == l_ray->hitpoint)
// 		return (color += att * scene->light.brightness);
// 	if (depth == DEPTH)
// 			return (color *= att);
// 	get_color(scene, &scatter_ray, depth++);
// }

t_vec3	get_color(t_scene *scene, t_ray *ray, t_type *objs)
{
	(void)scene;
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

//problem is the next pixel is NOT at +1.0f 
t_vec3	monte_carlo_color(t_scene *scene, t_type *objs, int x, int y)
{
	t_vec3		color;
	uint32_t	i;
	t_ray		ray;
	// int			depth;
	
	i = 0;
	// depth = 0;
	color = (t_vec3){0.0f, 0.0f, 0.0f};
	while (i < RAYSPERPIXEL)
	{
		float h = ((float)x + randf_zero_one(123)) / (float)WIDTH;
		float v = ((float)y + randf_zero_one(99912)) / (float)HEIGHT;
		get_ray(&scene->camera, &ray, h, v);

		color += get_color(scene, &ray, objs);
		// color += get_color(scene, &ray, objs, depth);
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
			t_vec3 color = monte_carlo_color(scene, scene->objs, x, y);
			put_image_pixel(data, x, y, color);
			x++;
		}
		show_progress_bar(y);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}
