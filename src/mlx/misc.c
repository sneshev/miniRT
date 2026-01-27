#include "minirt.h"

#define R 0
#define G 1
#define B 2
// puts int color on the appropriate x/y pixel of window
void	put_image_pixel(t_mlx_data *data, int x, int y, t_vec3 color)
{
	char	*pixel;
	void	*addr;
	int		bpp;
	int		line_length;
	uint8_t	rgb[4];

	addr = data->img_info->addr;
	bpp = data->img_info->bpp;
	line_length = data->img_info->line_length;
	pixel = (char *)addr + (y * line_length + x * (bpp / 8));
	rgb[R] = color[0] * 255.99;
	rgb[G] = color[1] * 255.99;
	rgb[B] = color[2] * 255.99;
	*(uint32_t *)pixel = (uint32_t)rgb[R] << 16 | (uint32_t)rgb[G] << 8 | (uint32_t)rgb[B];
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
