#ifndef STRUCTS_H
# define STRUCTS_H

#ifdef __APPLE__   // macOS
#  include "../mlx_mac/mlx.h" 
#  include "../mlx_mac/mlx_int.h" 
#  include "../mlx_mac/mlx_new_window.h" 
#  include "../mlx_mac/mlx_opengl.h" 
#  include "../mlx_mac/mlx_png.h" 
# else              // Linux
#  include "../mlx_linux/mlx.h"
#  include "../mlx_linux/mlx_int.h"
#endif

typedef struct s_img_info
{
	int		bpp;
	int		line_length;
	int		endian;
	char	*addr;
}	t_img_info;

typedef struct s_mlx_data
{
	void		*mlx;
	void		*win;
	void		*img;
	t_img_info	*img_info;
}	t_mlx_data;

#endif