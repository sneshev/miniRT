/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sneshev <sneshev@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:32:04 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/24 13:36:46 by sneshev          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/time.h>

bool	direct_light(t_ray *ray, t_light *light, t_objs *objs)
{
	t_ray	light_ray;

	if (light->type == NONE)
		return (false);
	light_ray.origin = ray->hit.hitpoint;
	light_ray.unit_dir = normalize(light->origin + LIGHT_RADIUS*random_point_in_unit_sphere() - ray->hit.hitpoint);
	light_ray.closest_t = FLT_MAX;
	light_ray.hit.type = NONE;
	// we dont know why this would ever happen but it does
	if (!hit_object(&light_ray, objs))
		return (false);
	if (light_ray.hit.type == LIGHT && dot(ray->hit.normal, light_ray.unit_dir) > 0)
		return (true);
	return (false);
}

t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 attenuation, int depth)
{
	t_vec3	color;
	t_ray	scatter;

	if (!hit_object(ray, scene->objs))
		return (new_vec3(0.0f, 0.0f, 0.0f));

	if (ray->hit.type == LIGHT)
		return (scene->light.emission * attenuation);

	color = new_vec3(0.0f, 0.0f, 0.0f);
	if (depth == 0)
		color = scene->ambient.emission * ray->hit.albedo;

	if (direct_light(ray, &scene->light, scene->objs))
		color += (scene->light.emission * ray->hit.albedo * attenuation);

	if (depth < MAX_DEPTH)
	{
		attenuation *= ray->hit.albedo;
		scatter = random_scatter_ray(ray);
		color += sample_color(scene, &scatter, attenuation, depth+1);
	}
	return (color);
}

t_vec3	get_average_color(t_scene *scene, t_ray *ray)
{
	t_vec3	color;
	t_vec3	attenuation;
	int		depth;

	depth = 0;
	attenuation = new_vec3(1.0f, 1.0f, 1.0f);
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
	color = new_vec3(0.0f, 0.0f, 0.0f);
	while (i < RAYSPERPIXEL)
	{
		float h = ((float)x + randf_zero_one(123)) / (float)WIDTH;
		float v = ((float)y + randf_zero_one(99912)) / (float)HEIGHT;
		ray = get_ray(&scene->camera, h, v);
		color += get_average_color(scene, &ray);
		i++;
	}
	color /= RAYSPERPIXEL;
	return (color);
}

void render(t_mlx_data *data, t_scene *scene)
{
	t_vec3	color;
	int		x;
	int		y;

	color = new_vec3(0.0f, 0.0f, 0.0f);
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
