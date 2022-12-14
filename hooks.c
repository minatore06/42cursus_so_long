#include "so_long.h"

void	collect_collectible(t_mlxs *vars, int x, int y)
{
	vars->map[y][x] = '0';
	vars->c_collectible--;
}

void	escape_game(t_mlxs *vars, int x, int y)
{
	if (!vars->c_collectible)
	{
		vars->movements++;
		vars->map[y][x] = 'F';
		vars->end = 1;
	}
}

void	player_funeral(t_mlxs *vars, int x, int y)
{
	vars->map[y][x] = 'F';
	vars->end = -1;
}

int	key_press_up(int keycode, t_mlxs *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	if (keycode == 65361 && !vars->end)
	{
		if (vars->map[vars->mc.y][vars->mc.x - 1] == 'C')
			collect_collectible(vars, vars->mc.x - 1, vars->mc.y);
		else if (vars->map[vars->mc.y][vars->mc.x - 1] == 'E')
			escape_game(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y][vars->mc.x - 1] == 'N')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y][vars->mc.x - 1] == 'M')
			player_funeral(vars, vars->mc.x, vars->mc.y);
 		else if (vars->map[vars->mc.y][vars->mc.x - 1] != '1')
		{
			vars->map[vars->mc.y][vars->mc.x] = '0';
			vars->mc.x--;
			vars->map[vars->mc.y][vars->mc.x] = 'P';
			vars->movements++;
			vars->mc.flip = 1;
		}
	}
	if (keycode == 65362 && !vars->end)
	{
		if (vars->map[vars->mc.y - 1][vars->mc.x] == 'C')
			collect_collectible(vars, vars->mc.x, vars->mc.y - 1);
		else if (vars->map[vars->mc.y - 1][vars->mc.x] == 'E')
			escape_game(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y - 1][vars->mc.x] == 'N')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y - 1][vars->mc.x] == 'M')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y - 1][vars->mc.x] != '1')
		{	
			vars->map[vars->mc.y][vars->mc.x] = '0';
			vars->mc.y--;
			vars->map[vars->mc.y][vars->mc.x] = 'P';
			vars->movements++;
		}
	}
	if (keycode == 65363 && !vars->end)
	{
		if (vars->map[vars->mc.y][vars->mc.x + 1] == 'C')
			collect_collectible(vars, vars->mc.x + 1, vars->mc.y);
		else if (vars->map[vars->mc.y][vars->mc.x + 1] == 'E')
			escape_game(vars, vars->mc.x, vars->mc.y);	
		else if (vars->map[vars->mc.y][vars->mc.x + 1] == 'N')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y][vars->mc.x + 1] == 'M')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y][vars->mc.x + 1] != '1')
		{
			vars->map[vars->mc.y][vars->mc.x] = '0';
			vars->mc.x++;
			vars->map[vars->mc.y][vars->mc.x] = 'P';
			vars->movements++;
			vars->mc.flip = 0;
		}
	}
	if (keycode == 65364 && !vars->end)
	{
		if (vars->map[vars->mc.y + 1][vars->mc.x] == 'C')
			collect_collectible(vars, vars->mc.x, vars->mc.y + 1);
		else if (vars->map[vars->mc.y + 1][vars->mc.x] == 'E')
			escape_game(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y + 1][vars->mc.x] == 'N')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y + 1][vars->mc.x] == 'M')
			player_funeral(vars, vars->mc.x, vars->mc.y);
		else if (vars->map[vars->mc.y + 1][vars->mc.x] != '1')
		{
			vars->map[vars->mc.y][vars->mc.x] = '0';
			vars->mc.y++;
			vars->map[vars->mc.y][vars->mc.x] = 'P';
			vars->movements++;
		}
	}
	return (0);
}

int	ft_close(t_mlxs *vars)
{
	int	i;

	mlx_destroy_image(vars->mlx, vars->terrain.img);
	mlx_destroy_image(vars->mlx, vars->border.img);
	mlx_destroy_image(vars->mlx, vars->wall.img);
	mlx_destroy_image(vars->mlx, vars->collectible.img);
	mlx_destroy_image(vars->mlx, vars->exit_close.img);
	mlx_destroy_image(vars->mlx, vars->exit_open.img);
	mlx_destroy_image(vars->mlx, vars->dead.img);
	i = 0;
	while (i < 3)
		mlx_destroy_image(vars->mlx, vars->victory[i++].img);
	i = 0;
	while (i < 8)
		mlx_destroy_image(vars->mlx, vars->mc.img[i++].img);
	i = 0;
	while (i < 8)
		mlx_destroy_image(vars->mlx, vars->enemy.img[i++].img);
	i = 0;
	while (i < 4)
		mlx_destroy_image(vars->mlx, vars->patrol.img[i++].img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_map((void **)vars->map);
	exit(0);
}