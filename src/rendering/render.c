/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmisumi <mmisumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 13:32:04 by sneshev           #+#    #+#             */
/*   Updated: 2026/02/26 15:32:35 by mmisumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <sys/time.h>

bool	direct_light(t_ray *ray, t_light *light, t_objs *objs)
{
	t_ray	light_ray;
	t_vec3	direction;

	if (light->type == NONE)
		return (false);
	direction = get_light_point(light->origin) - ray->hit.hitpoint;
	light_ray = new_ray(ray->hit.hitpoint, direction);
	if (hit_object(&light_ray, objs))
	{
		if (light_ray.hit.type == LIGHT)
		{
			if (dot(ray->hit.normal, light_ray.unit_dir) > 0)
				return (true);
		}
	}
	return (false);
}

t_vec3	sample_color(t_scene *scene, t_ray *ray, t_vec3 attenuation, int depth)
{
	t_vec3	color;
	t_ray	scatter;

	if (!hit_object(ray, scene->objs))
		return (new_vec3(0.0f, 0.0f, 0.0f));
	color = new_vec3(0.0f, 0.0f, 0.0f);
	if (ray->hit.type == LIGHT)
	{
		if (depth == 0)
			return (scene->light.albedo);
		return (scene->light.emission * attenuation);
	}
	if (depth == 0)
		color = scene->ambient.emission * ray->hit.albedo;
	if (direct_light(ray, &scene->light, scene->objs))
		color += (scene->light.emission * ray->hit.albedo * attenuation);
	if (depth < MAX_DEPTH)
	{
		attenuation *= ray->hit.albedo;
		scatter = random_scatter_ray(ray);
		color += sample_color(scene, &scatter, attenuation, depth + 1);
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
	float		h;
	float		v;

	i = 1;
	color = new_vec3(0.0f, 0.0f, 0.0f);
	while (i < RAYSPERPIXEL)
	{
		h = ((float)x + randf_zero_one()) / (float)WIDTH;
		v = ((float)y + randf_zero_one()) / (float)HEIGHT;
		ray = get_cam_ray(&scene->camera, h, v);
		color += get_average_color(scene, &ray);
		i++;
	}
	color /= RAYSPERPIXEL;
	return (color);
}

void	render(t_mlx_data *data, t_scene *scene)
{
	t_vec3	color;
	int		x;
	int		y;

	color = new_vec3(0.0f, 0.0f, 0.0f);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
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
