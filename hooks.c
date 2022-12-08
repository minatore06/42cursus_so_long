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
	//ft_printf("ps %d | %d", vars->c_collectible, vars->end);
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
		ft_printf("Movements: %d\n", vars->movements);
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
		ft_printf("Movements: %d\n", vars->movements);
	}
	if (keycode == 65363 && !vars->end)
	{
		if (vars->map[vars->mc.y][vars->mc.x + 1] == 'C')
			collect_collectible(vars, vars->mc.x + 1, vars->mc.y);
		else if (vars->map[vars->mc.y - 1][vars->mc.x] == 'E')
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
		ft_printf("Movements: %d\n", vars->movements);
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
		ft_printf("Movements: %d\n", vars->movements);
	}
	ft_printf("Key pressed %d\n", keycode);
	return (0);
}

int	button_press_down(int mbcode, t_mlxs *vars)
{
	if (mbcode && vars)
	{
		write(1, ft_itoa(mbcode), ft_strlen(ft_itoa(mbcode)));
		return (1);
	}
	return (0);
}

int	ft_close(t_mlxs *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	free_map((void **)vars->map);
	exit(0);
}