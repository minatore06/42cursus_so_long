#include "so_long.h"

int	key_press_down(int keycode, t_mlxs *vars)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	if (keycode == 65361)
	{
		vars->mc.x -= 32;
		if (vars->mc.x < 0)
			vars->mc.x = 1920;
		vars->mc.x %= 1920;
		ft_printf("left");
	}
	if (keycode == 65362)
	{
		vars->mc.y -= 32;
		if (vars->mc.y < 0)
			vars->mc.y = 1080;
		vars->mc.y %= 1080;
		ft_printf("up");
	}
	if (keycode == 65363)
	{
		vars->mc.x += 32;
		if (vars->mc.x > 1920 - vars->mc.width[0])
			vars->mc.x = 1920 - vars->mc.width[0];
		vars->mc.x %= 1920;
		ft_printf("right");
	}
	if (keycode == 65364)
	{
		vars->mc.y += 32;
		if (vars->mc.y > 1080 - vars->mc.height[0])
			vars->mc.y = 1080 - vars->mc.height[0];
		vars->mc.y %= 1080;
		ft_printf("down");
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
	exit(0);
}