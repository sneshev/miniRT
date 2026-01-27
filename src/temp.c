/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stefuntu <stefuntu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 19:33:12 by winnitytrin       #+#    #+#             */
/*   Updated: 2026/01/27 07:50:04 by stefuntu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_vec3(char const *s, t_vec3 v)
{
	printf("%s: %f, %f, %f\n", s, v[X], v[Y], v[Z]);
}

void	print_color(char const *s, t_color color)
{
	printf("%s: %d, %d, %d\n", s, color.rgb.r, color.rgb.g, color.rgb.b);
}

void	print_camera(t_camera camera)
{
	print_vec3("C origin", camera.origin);
	print_vec3("C upper_left", camera.upper_left);
	print_vec3("C horizontal", camera.horizontal);
	print_vec3("C vertical", camera.vertical);
	printf("\n");	
}

void	print_ambient(t_ambient ambient)
{
	printf("A lightness: %f\n", ambient.lightness);
	print_color("A albedo", ambient.albedo);
	printf("\n");
}

void	print_light(t_light light)
{
	print_vec3("L origin", light.origin);
	printf("L brightness: %f\n", light.brightness);
	print_color("L color", light.albedo);
	printf("\n");
}

void	print_sphere(t_sphere sphere)
{
	print_vec3("sp center", sphere.center);
	printf("sp radius: %f\n", sphere.radius);
	print_color("sp albedo", sphere.albedo);
	printf("\n");
}

void	print_plane(t_plane plane)
{
	print_vec3("pl center", plane.center);
	print_vec3("pl dir", plane.dir);
	print_color("pl albedo", plane.albedo);
	printf("\n");
}

void	print_cylinder(t_cylinder cylinder)
{
	print_vec3("cy center", cylinder.center);
	print_vec3("cy dir", cylinder.dir);
	printf("cy radius: %f\n", cylinder.radius);
	printf("cy height: %f\n", cylinder.height);
	print_color("cy albedo", cylinder.albedo);
	printf("\n");
}

void	print_scene(t_scene *scene)
{
	t_object	obj;
	int			obj_count;
	int			i;

	print_camera(scene->camera);
	print_ambient(scene->ambient);
	print_light(scene->light);
	
	obj_count = get_count(&scene->objs);
	i = 0;
	while (obj_count > i)
	{
		obj = scene->objs[i].object;
		if (obj.type == SP)
			print_sphere(scene->objs[i].sphere);
		else if (obj.type == PL)
			print_plane(scene->objs[i].plane);
		else if (obj.type == CY)
			print_cylinder(scene->objs[i].cylinder);
		i++;	
	}
}

void show_progress_bar (int j) {
	j += 1;
	int progress = 100 * (j) / HEIGHT;
	char buf[64];
	int len = snprintf(buf, sizeof(buf), "\r%d%% (%d / %d)", progress, j*WIDTH, HEIGHT * WIDTH);
	write(STDERR_FILENO, buf, len);
}
