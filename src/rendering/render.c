#include "minirt.h"
#include <sys/time.h>

t_ray	get_ray(t_camera *cam, float h, float v)
{
	t_ray	ray;
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray.origin = cam->origin;
	ray.unit_dir = normalize(hitpoint - ray.origin);
	ray.closest_t = FLT_MAX;
	ray.hit.type = NONE;
	return (ray);
}

bool	hit_object(t_ray *ray, t_objs *objs)
{
	size_t		i;
	t_object	*object;

	i = 0;
	while (i < get_count(&objs))
	{
		object = &objs[i].object;
		object->intersect(ray, object);
		i++;
	}
	if (ray->hit.type == NONE)
		return (false);
	return (true);
}

t_vec3	random_point_in_unit_sphere(void)
{
	t_vec3	point;

	while (1)
	{
		point = (t_vec3){randf_none_one(35), randf_none_one(356), randf_none_one(23546)};
		if (squared_length(point) < 1.0f)
			return (point);
	}
}

bool	direct_light(t_ray *ray, t_light *light, t_objs *objs)
{
	t_ray	light_ray;

	if (light->type == NONE)
		return (false);
	light_ray.origin = ray->hit.hitpoint;
	light_ray.unit_dir = normalize(light->origin + random_point_in_unit_sphere()) - ray->hit.hitpoint;
	light_ray.closest_t = FLT_MAX;
	light_ray.hit.type = NONE;
	// we dont know why this would ever happen but it does
	if (!hit_object(&light_ray, objs))
		return (false);
	if (dot(ray->hit.normal, light_ray.hit.normal) > 0)
		return (false);
	return (true);
}

t_ray	random_scatter_ray(t_ray *ray)
{
	t_ray	scatter_ray;

	scatter_ray.origin = ray->hit.hitpoint;
	scatter_ray.unit_dir = normalize(ray->hit.normal + random_point_in_unit_sphere());
	scatter_ray.closest_t = FLT_MAX;
	scatter_ray.hit.type = NONE;
	return (scatter_ray);
}

t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 attenuation, int depth)
{
	t_vec3	color;
	t_ray	scatter;

	if (!hit_object(ray, scene->objs))
		return ((t_vec3){0.0f, 0.0f, 0.0f});

	if (ray->hit.type == LIGHT)
		return (scene->light.emission * attenuation);

	color = (t_vec3){0.0f, 0.0f, 0.0f};
	if (depth == 0)
		color = scene->ambient.emission * ray->hit.albedo;

	if (direct_light(ray, &scene->light, scene->objs))
		color += (scene->light.emission * ray->hit.albedo * attenuation);

	if (depth < MAX_DEPTH)
	{
		attenuation *= ray->hit.albedo;
		scatter = random_scatter_ray(ray);
		color += sample_color(scene, &scatter, attenuation, depth++);
	}
	return (color);
}

t_vec3	get_color(t_scene *scene, t_ray *ray)
{
	t_vec3	color;
	t_vec3	attenuation;
	int		depth;

	depth = 0;
	attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
	color = sample_color(scene, ray, attenuation, depth);
	color = clamp(color);
	return (color);
}

t_vec3	monte_carlo_color(t_scene *scene, int x, int y)
{
	uint32_t	i;
	t_ray		ray;
	t_vec3		color;
	
	i = 1;
	color = (t_vec3){0.0f, 0.0f, 0.0f};
	while (i < RAYSPERPIXEL)
	{
		float h = ((float)x + randf_zero_one(123)) / (float)WIDTH;
		float v = ((float)y + randf_zero_one(99912)) / (float)HEIGHT;
		ray = get_ray(&scene->camera, h, v);
		color += get_color(scene, &ray);
		i++;
	}
	color /= RAYSPERPIXEL;
	return (color);
}

void show_progress_bar (int j);

void render(t_mlx_data *data, t_scene *scene)
{
	t_vec3	color;
	int		x;
	int		y;

	color = (t_vec3){0.0f, 0.0f, 0.0f};
	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			color = monte_carlo_color(scene, x, y);
			put_image_pixel(data, x, y, color);
			x++;
		}
		show_progress_bar(y);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}
