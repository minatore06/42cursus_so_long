/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:02:26 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/15 12:02:29 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	keyboard_event(char cell, int x, int y, t_mlxs *vars)
{
	if (cell == 'C')
	{
		collect_collectible(vars, x, y);
		return (1);
	}
	else if (cell == 'E')
	{
		get_player(vars->map, &x, &y);
		escape_game(vars, x, y);
		return (1);
	}
	else if (cell == 'N' || cell == 'M')
	{
		get_player(vars->map, &x, &y);
		player_funeral(vars, x, y);
		return (1);
	}
	return (0);
}

int	key_press_up(int keycode, t_mlxs *vars)
{
	if (keycode == 65307)
		ft_close(vars);
	if (keycode == 65361 && !vars->end)
		move_left(vars, vars->mc.x, vars->mc.y);
	else if (keycode == 65362 && !vars->end)
		move_up(vars, vars->mc.x, vars->mc.y);
	else if (keycode == 65363 && !vars->end)
		move_right(vars, vars->mc.x, vars->mc.y);
	else if (keycode == 65364 && !vars->end)
		move_down(vars, vars->mc.x, vars->mc.y);
	return (0);
}

void	ft_destroy_img(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

void	ft_destroy_images(t_mlxs *vars)
{
	int	i;

	ft_destroy_img(vars->mlx, vars->terrain.img);
	ft_destroy_img(vars->mlx, vars->border.img);
	ft_destroy_img(vars->mlx, vars->wall.img);
	ft_destroy_img(vars->mlx, vars->collectible.img);
	ft_destroy_img(vars->mlx, vars->exit_close.img);
	ft_destroy_img(vars->mlx, vars->exit_open.img);
	ft_destroy_img(vars->mlx, vars->dead.img);
	i = 0;
	while (i < 3)
		ft_destroy_img(vars->mlx, vars->victory[i++].img);
	i = 0;
	while (i < 8)
		ft_destroy_img(vars->mlx, vars->mc.img[i++].img);
	i = 0;
	while (i < 8)
		ft_destroy_img(vars->mlx, vars->enemy.img[i++].img);
	i = 0;
	while (i < 4)
		ft_destroy_img(vars->mlx, vars->patrol.img[i++].img);
}

int	ft_close(t_mlxs *vars)
{
	ft_destroy_images(vars);
	if (vars->mlx)
	{
		if (vars->win)
			mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	if (vars->map)
		free_map((void **)vars->map);
	exit(0);
}
