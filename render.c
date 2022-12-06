#include "so_long.h"

void	ft_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}



void	render_map(t_mlxs *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			if (vars->map[i / 64][j / 64] == '1' && (i == 0 || j == 0 || i == vars->height - 64 || j == vars->width - 64))
				mlx_put_image_to_window(vars->mlx, vars->win, vars->border.img[0].img, j, i);
			else if (vars->map[i / 64][j / 64] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall.img[0].img, j, i);
			else if (vars->map[i / 64][j / 64] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->collectible.img[0].img, j, i);
			else if (vars->map[i / 64][j / 64] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->exit.img[0].img, j, i);
			else
				mlx_put_image_to_window(vars->mlx, vars->win, vars->terrain.img[0].img, j, i);
			if (vars->map[i / 64][j / 64] == 'P' && !vars->mc.flip)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->mc.img[vars->frame / 20000 % 4].img, j + 16, i);
			else if (vars->map[i / 64][j / 64] == 'P' && vars->mc.flip)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->mc.img[vars->frame / 20000 % 4 + 4].img, j + 16, i);
			j += 64;
		}
		i += 64;
	}
}

int	render_next_frame(t_mlxs *vars)
{
	int	rainbow[6];

	rainbow[0] = create_trgb(0, 255, 0, 0);
	rainbow[1] = create_trgb(0, 255, 165, 0);
	rainbow[2] = create_trgb(0, 255, 255, 0);
	rainbow[3] = create_trgb(0, 0, 255, 0);
	rainbow[4] = create_trgb(0, 0, 0, 255);
	rainbow[5] = create_trgb(0, 128, 0, 128);

	if (!(vars->frame % 20000))
	{
		if (!vars->c_collectible)
			vars->exit.img[0] = vars->exit.img[1];
		mlx_clear_window(vars->mlx, vars->win);
		render_map(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->enemy.img[vars->frame / 8000 % 8].img, vars->enemy.x * 64 + 16, vars->enemy.y * 64);
		vars->enemy.x += 64;
	}
	vars->frame++;
return (0);
}