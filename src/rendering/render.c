#include "minirt.h"

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
			float h = (float)i/(float)WIDTH;
			float v = (float)j/(float)HEIGHT;
			t_ray ray;
			get_ray(&scene->camera, &ray, h, v);

			t_color color = get_color(&ray, scene->objs);
			put_image_pixel(data, i, j, color);
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_loop(data->mlx);
}
