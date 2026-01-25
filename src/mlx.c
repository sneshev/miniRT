#include "minirt.h"

# define ESC 65307

// puts int color on the appropriate x/y pixel of window
void	put_image_pixel(t_mlx_data *data, int x, int y, t_color color)
{
	char	*pixel;
	void	*addr;
	int		bpp;
	int		line_length;

	addr = data->img_info->addr;
	bpp = data->img_info->bpp;
	line_length = data->img_info->line_length;
	pixel = (char *)addr + (y * line_length + x * (bpp / 8));
	*(unsigned int *)pixel = color.value;
}

void	free_data_exit(t_mlx_data *data, int exitcode)
{
	if (data->img_info)
		free(data->img_info);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	printf("\n");
	exit(exitcode);
}

int	close_window(t_mlx_data *data)
{
	free_data_exit(data, 0);
	return (1);
}
int	set_keyhooks(int key, t_mlx_data *data)
{
	if (key == ESC)
		free_data_exit(data, 0);
	return (1);
}

int	init_minilibx(t_mlx_data *data)
{
	t_img_info	*img_info;

	data->mlx = (void *)mlx_init();
	if (!data->mlx)
		return (0);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	if (!data->win)
		return (0);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
		return (0);
	data->img_info = (t_img_info *)malloc(sizeof (t_img_info));
	if (!data->img_info)
		return (0);
	img_info = data->img_info;
	img_info->addr = mlx_get_data_addr(data->img,
			&img_info->bpp, &img_info->line_length, &img_info->endian);
	if (!img_info->addr || !img_info->bpp || !img_info->line_length)
		return (0);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_key_hook(data->win, set_keyhooks, data);
	return (1);
}
