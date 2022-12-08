#include "so_long.h"

void	ft_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	victory_animation(t_mlxs *vars, int i, int j)
{
	mlx_put_image_to_window(vars->mlx, vars->win, vars->victory[vars->end - 1].img, j, i + 8);
	vars->end++;
	if (vars->end == 4)
		vars->map[i / 64][j / 64] = '0';
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
				mlx_put_image_to_window(vars->mlx, vars->win, vars->border.img, j, i);
			else if (vars->map[i / 64][j / 64] == '1')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->wall.img, j, i);
			else if (vars->map[i / 64][j / 64] == 'C')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->collectible.img, j, i);
			else if (vars->map[i / 64][j / 64] == 'E' && vars->c_collectible)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->exit_close.img, j, i);
			else if (vars->map[i / 64][j / 64] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->exit_open.img, j, i);
			else
				mlx_put_image_to_window(vars->mlx, vars->win, vars->terrain.img, j, i);
			if (vars->map[i / 64][j / 64] == 'N')
				mlx_put_image_to_window(vars->mlx, vars->win, vars->enemy.img[vars->frame / 20000 % 8].img, j, i + 16);
			else if (vars->map[i / 64][j / 64] == 'M' && vars->end < 1)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->patrol.img[vars->frame / 20000 % 3].img, j, i);
			else if (vars->map[i / 64][j / 64] == 'M' && vars->end > 0)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->patrol.img[3].img, j, i);
			else if (vars->map[i / 64][j / 64] == 'F' && vars->end == -1)
				mlx_put_image_to_window(vars->mlx, vars->win, vars->dead.img, j, i + 8);
			else if (vars->map[i / 64][j / 64] == 'F' && vars->end > 0)
				victory_animation(vars, i, j);
			else if (vars->map[i / 64][j / 64] == 'P' && !vars->mc.flip)
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

	vars->frame++;
	if (!(vars->frame % 20000))
	{
		mlx_clear_window(vars->mlx, vars->win);
		render_map(vars);
	}
	if (!(vars->frame % 50000) && !vars->end)
		enemy_pathfinding(vars);
	return (0);
}