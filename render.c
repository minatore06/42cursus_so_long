#include "so_long.h"

void	ft_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render_next_frame(t_mlxs *vars)
{
	int	i;
	int	j;
	int	rainbow[6];

	rainbow[0] = create_trgb(0, 255, 0, 0);
	rainbow[1] = create_trgb(0, 255, 165, 0);
	rainbow[2] = create_trgb(0, 255, 255, 0);
	rainbow[3] = create_trgb(0, 0, 255, 0);
	rainbow[4] = create_trgb(0, 0, 0, 255);
	rainbow[5] = create_trgb(0, 128, 0, 128);
	i = 0;
	if (!(vars->frame % (60 * 2)))
	{
		while (i < 1920)
		{
			j = 0;
			while (j < 1080)
			{
				if (i < 192 || j < 108 || i > 1728 || j > 972)
				{
					ft_mlx_pixel_put(&vars->img, i, j, rainbow[vars->frame / (60 * 2) % 6]);
				}
				j++;
			}
			i++;
		}
	}
	if (!(vars->frame % 60))
		vars->enemy.x += 32;
	vars->frame++;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->mc.img[vars->frame / 60 % 4].img, vars->mc.x, vars->mc.y);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->enemy.img[vars->frame / 60 % 8].img, vars->enemy.x, vars->enemy.y);
	return (0);
}