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
	// ray.hitpoint = (t_vec3){0.0f, 0.0f, 0.0f};
	// ray.normal = (t_vec3){0.0f, 0.0f, 0.0f};
	ray.object = NULL;
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
	if (!ray->object)
		return (false);
	return (true);
}

bool	direct_light(t_light *light, t_objs *objs, t_vec3 hitpoint)
{
	t_ray	light_ray;

	if (light->type == NONE)
		return (false);
	light_ray.origin = hitpoint;
	light_ray.unit_dir = normalize(light->origin - hitpoint);
	light_ray.closest_t = FLT_MAX;
	// light_ray.hitpoint = (t_vec3){0.0f, 0.0f, 0.0f};
	// light_ray.normal = (t_vec3){0.0f, 0.0f, 0.0f};
	light_ray.object = NULL;
	hit_object(&light_ray, objs);
	if (light_ray.object->type == LIGHT)
		return (true);
	return (false);
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
bool	is_on_same_plane(t_vec3 *p1, t_vec3 *p2, t_vec3 *normal)
{
	float	d = dot(normalize(*p1 - *p2), normalize(*p1 - *normal));
	if (d < T_MIN && d > -T_MIN)
		return (true);
	return (false);
}

t_vec3	get_cy_normal(t_cylinder *cy, t_vec3 *hitpoint)
{
		t_vec3		p;
		p = cy->center + (cy->unit_dir * (cy->height / 2));
		if (is_on_same_plane(&p, hitpoint, &cy->unit_dir)) {
			return (cy->unit_dir);
		}
		p = cy->center - (cy->unit_dir * (cy->height / 2));
		if (is_on_same_plane(&p, hitpoint, &cy->unit_dir)) {
			return (-cy->unit_dir);
		}
		else
		{
		    t_vec3	cp = *hitpoint - cy->center;
		    float	h = dot(cp, cy->unit_dir);
		    t_vec3	axis_point = cy->center + cy->unit_dir * h;
		    return (normalize(*hitpoint - axis_point));
		}
}

//	doesnt account for hitting back of object yet (needs to flip normal)
t_vec3	get_normal(t_object *object, t_vec3 hitpoint)
{
	t_vec3	normal = (t_vec3){0, 0, 0};

	if (object->type == SPHERE) {
		normal = normalize(hitpoint - ((t_sphere *)object)->center);
	}
	else if (object->type == PLANE)
	{
		normal = ((t_plane *)object)->normal;
	// if (dot(normal, ray.dir) > 0)
	    // normal = normal * -1;
	}
	else if (object->type == CYLINDER)
	{
		normal = get_cy_normal((t_cylinder *)object, &hitpoint);
	}
	return (normal);
}

t_ray	random_scatter_ray(t_vec3 hitpoint, t_vec3 normal)
{
	t_ray	scatter_ray;

	scatter_ray.origin = hitpoint;
	scatter_ray.unit_dir = normal + random_point_in_unit_sphere();
	scatter_ray.closest_t = FLT_MAX;
	// scatter_ray.hitpoint = (t_vec3){0.0f, 0.0f, 0.0f};
	// scatter_ray.normal = (t_vec3){0.0f, 0.0f, 0.0f};
	scatter_ray.object = NULL;
	return (scatter_ray);
}

t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 attenuation, int *depth)
{
	t_vec3	color;
	t_ray	scatter;
	t_vec3	hitpoint;
	t_vec3	normal;
	t_vec3	light_emission;

	color = scene->ambient.lightness * scene->ambient.albedo;
	light_emission = scene->light.brightness * scene->light.albedo;

	if (hit_object(ray, scene->objs) == false)
		return ((t_vec3){0.0f, 0.0f, 0.0f});

	if (ray->object->type == LIGHT)
		return (light_emission * attenuation);

	hitpoint = ray->origin + ray->closest_t * ray->unit_dir;
	normal = get_normal(ray->object, hitpoint);

	if (direct_light(&scene->light, scene->objs, hitpoint) == true)
		color += light_emission * ray->object->albedo * attenuation;

	if (*depth < MAX_DEPTH)
	{
		*depth += 1;
		scatter = random_scatter_ray(hitpoint, normal);
		color += sample_color(scene, &scatter, attenuation, depth);
	}
	return (color);
}

t_vec3	get_color(t_scene *scene, t_ray *ray)
{
	t_vec3	color;
	t_vec3	attenuation;
	int		depth;

	depth = 1;
	attenuation = (t_vec3){1.0f, 1.0f, 1.0f};
	color = sample_color(scene, ray, attenuation, &depth);
	color /= (float)depth;
	color = clamp(color);
	return (color);
}

t_vec3	monte_carlo_color(t_scene *scene, int x, int y)
{
	uint32_t	i;
	t_ray		ray;
	t_vec3		color;
	
	i = 0;
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
	color = clamp(color);
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
