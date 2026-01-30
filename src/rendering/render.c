#include "minirt.h"

// int	open_file(char *file)
// {
// 	int	fd;
// 	// check the extension
// 	fd = open(file, O_RDONLY);
// 	if (fd < 0)
// 	{
// 		print_error(FD);
// 		exit(1);
// 	}
// 	return (fd);	
// }

int vec3_diff(t_vec3 v1, t_vec3 v2)
{
    if (fabs(v1[X] - v2[X]) > 0.001f)
		return 1;
    if (fabs(v1[Y] - v2[Y]) > 0.001f)
		return 1;
    if (fabs(v1[Z] - v2[Z]) > 0.001f)
		return 1;

    return 0;
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

t_ray	get_ray(t_camera *cam, float h, float v)
{
	t_ray	ray;
	t_vec3	hitpoint;

	hitpoint = cam->upper_left + h * cam->horizontal - v * cam->vertical;
	ray.origin = cam->origin;
	ray.unit_dir = normalize(hitpoint - ray.origin);
	ray.closest_t = FLT_MAX;
	ray.object = NULL;
	return (ray);
}

// get the closest hit: the closest t, albedo and pointer to the object
// return false when there is no hit
bool	hit_object(t_ray *ray, t_type *objs)
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
	if (!ray->object)
		return (false);
	return (true);
}

t_vec3	direct_light(t_light *light, t_type *objs, t_vec3 hitpoint)
{
	t_vec3	closest_hit;

	light->ray.origin = hitpoint;
	light->ray.unit_dir = normalize(light->origin - hitpoint);
	light->ray.closest_t = FLT_MAX;
	light->ray.object = NULL;
	hit_object(&light->ray, objs);
	closest_hit = light->ray.origin + light->ray.closest_t * light->ray.unit_dir;
	if (vec3_diff(closest_hit, light->origin))
		return (false);
	return (true);
}

t_vec3	random_point_in_unit_sphere(void)
{
	t_vec3	point;

	while (1)
	{
		point = (t_vec3){randf_zero_one(35), randf_zero_one(356), randf_zero_one(23546)};
		if (squared_length(point) < 1.0f)
			break ;
	}
	return (point);
}


t_vec3	get_normal(t_object *object, t_vec3 hitpoint)
{
	t_vec3	normal;

	if (object->type == SP)
		normal = normalize(hitpoint = object.center);
	else if (object->type == PL)
		normal = object->normal;
	// get the normal for cylinder
	return (normal);
}

t_vec3	random_scatter_ray(t_object *object, t_vec3 hitpoint, t_vec3 normal)
{
	t_ray	ray;

	ray.origin = hitpoint;
	ray.unit_dir = ray->hitpoint + normal + random_point_in_unit_sphere();
	ray.closest_t = FLT_MAX;
	ray.object = NULL;
	return (ray);
}

t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 attenuation, int depth)
{
	t_ray	scatter;
	t_vec3	albedo;
	int		status;
	
	if (direct_light(&scene->light, scene->objs, ray->hitpoint) == true)
		attenuation += scene->light.brightness;

	if (hit_object(scatter, scene->objs) == false)
		return ((t_vec3){0.0f, 0.0f, 0.0f});
	

}

t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 attenuation, int depth)
{
	t_ray	scatter;
	t_vec3	albedo;
	int		status;

	// scatter random bounced ray
	scatter = random_scatter_ray(ray->object, ray->hitpoint, ray->normal);
	status = hit_object(scatter, scene->objs);
	if (status == true)
		albedo = ray->object->albedo;
	if (status == false)
		return (attenuation *= (t_vec3){0.0f, 0.0f, 0.0f});

	// see if we have direct light
	status = direct_light(&scene->light, scene->objs, ray->hitpoint);
	if (status == true)
		attenuation += albedo * scene->light.brightness;
	// if there is no direct light
	if (status == false)
		attenuation *= albedo;
	if (depth < MAX_DEPTH)
		sample_color(scene, &scatter, attenuation, depth);
	return (attenuation);
}


t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 *attenuation, int *depth)
{
	t_ray	scatter;

	// return color if we have direct light
	if (direct_light_hit(&scene->light, scene->objs, ray->hitpoint) == true)
		return (*attenuation += scene->light.brightness * ray->object->albedo);
	
	// if not we scatter a ray to try again
	scatter = random_scatter_ray(ray->object, ray->hitpoint, ray->normal);
	if (hit_object(scatter, scene->objs) == true && *depth < MAX_DEPTH)
		*attenuation *= sample_color(scene, &scatter, *attenuation, (*depth)++);

	return ((t_vec3){0.0f, 0.0f, 0.0f});
}

t_vec3	get_color(t_scene *scene, t_ray *ray)
{
	t_vec3	attenuation;
	int		depth;

	if (hit_object(ray, scene->objs) == false)
		return ((t_vec3){0.0f, 0.0f, 0.0f});
	
	ray->hitpoint = ray->origin + ray->closest_t * ray->unit_dir;
	ray->normal = get_normal(ray->object, ray->hitpoint);

	depth = 0;
	attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
	sample_color(ray, attenuation, depth);
	return (attenuation);
}

t_vec3	monte_carlo_color(t_scene *scene, t_type *objs, int x, int y)
{
	uint32_t	i;
	t_ray		ray;
	t_vec3		color;
	
	i = 0;
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

// t_vec3	get_color(t_scene *scene, t_ray *ray, t_type *objs)
// {
// 	(void)scene;

// 	if (get_closest_hit(ray, objs) == false)
// 		return ((t_vec3){0.0f, 0.0f, 0.0f});
// 	return (ray->object->albedo);
// }

//problem is the next pixel is NOT at +1.0f 
// t_vec3	monte_carlo_color(t_scene *scene, t_type *objs, int x, int y)
// {
// 	uint32_t	i;
// 	// int			depth;
// 	// t_vec3		attenuation;
// 	t_ray		ray;
// 	t_vec3		color;
	
// 	i = 0;
// 	// depth = 0;
// 	// attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
// 	while (i < RAYSPERPIXEL)
// 	{
// 		float h = ((float)x + randf_zero_one(123)) / (float)WIDTH;
// 		float v = ((float)y + randf_zero_one(99912)) / (float)HEIGHT;
// 		ray = get_ray(&scene->camera, h, v);

// 		color += get_color(scene, &ray, objs);
// 		// color += get_color(scene, &ray, objs, depth);
// 		i++;
// 	}
// 	color /= RAYSPERPIXEL;
// 	return (color);
// }

void show_progress_bar (int j);

void render(t_mlx_data *data, t_scene *scene)
{
	t_vec3	color;
	int		x;
	int		y;

	y = 0;
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			color = monte_carlo_color(scene, scene->objs, x, y);
			put_image_pixel(data, x, y, color);
			x++;
		}
		show_progress_bar(y);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}


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

// 	// make boolean
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