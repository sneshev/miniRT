#include "minirt.h"

# define ESC 65307

int	close_window(t_data *data)
{
	free_data_exit(data, 0);
	return (1);
}
int	set_keyhooks(int key, t_data *data)
{
	if (key == ESC)
		free_data_exit(data, 0);
	return (1);
}

int	init_minilibx(t_data *d)
{
	t_img_info	*img_info;

	d->mlx.mlx = (void *)mlx_init();
	if (!d->mlx.mlx)
		return (0);
	d->mlx.win = mlx_new_window(d->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	if (!d->mlx.win)
		return (0);
	d->mlx.img = mlx_new_image(d->mlx.mlx, WIDTH, HEIGHT);
	if (!d->mlx.img)
		return (0);
	d->mlx.img_info = (t_img_info *)malloc(sizeof (t_img_info));
	if (!d->mlx.img_info)
		return (0);
	img_info = d->mlx.img_info;
	img_info->addr = mlx_get_data_addr(d->mlx.img,
			&img_info->bpp, &img_info->line_length, &img_info->endian);
	if (!img_info->addr || !img_info->bpp || !img_info->line_length)
		return (0);
	mlx_hook(d->mlx.win, 17, 0, close_window, d);
	mlx_key_hook(d->mlx.win, set_keyhooks, d);
	return (1);
}
