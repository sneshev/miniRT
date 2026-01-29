#include "minirt.h"

# define ESC 65307

int	close_window(t_mlx_data *mlx)
{
	free_data_exit(mlx, 0);
	return (1);
}
int	set_keyhooks(int key, t_mlx_data *mlx)
{
	if (key == ESC)
		free_data_exit(mlx, 0);
	return (1);
}

int	init_minilibx(t_mlx_data *mlx)
{
	t_img_info	*img_info;

	mlx->mlx = (void *)mlx_init();
	if (!mlx->mlx)
		return (0);
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "miniRT");
	if (!mlx->win)
		return (0);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!mlx->img)
		return (0);
	mlx->img_info = (t_img_info *)malloc(sizeof (t_img_info));
	if (!mlx->img_info)
		return (0);
	img_info = mlx->img_info;
	img_info->addr = mlx_get_data_addr(mlx->img,
			&img_info->bpp, &img_info->line_length, &img_info->endian);
	if (!img_info->addr || !img_info->bpp || !img_info->line_length)
		return (0);
	mlx_hook(mlx->win, 17, 0, close_window, mlx);
	mlx_key_hook(mlx->win, set_keyhooks, mlx);
	return (1);
}
