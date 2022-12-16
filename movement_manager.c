/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:00:31 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/15 12:00:32 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	move_left(t_mlxs *vars, int x, int y)
{
	if (keyboard_event(vars->map[y][x - 1], x - 1, y, vars))
		return ;
	if (vars->map[y][x - 1] != '1')
	{
		vars->map[vars->mc.y][vars->mc.x] = '0';
		vars->mc.x--;
		vars->map[vars->mc.y][vars->mc.x] = 'P';
		vars->movements++;
		vars->mc.flip = 1;
	}
}

void	move_right(t_mlxs *vars, int x, int y)
{
	if (keyboard_event(vars->map[y][x + 1], x + 1, y, vars))
		return ;
	if (vars->map[y][x + 1] != '1')
	{
		vars->map[vars->mc.y][vars->mc.x] = '0';
		vars->mc.x++;
		vars->map[vars->mc.y][vars->mc.x] = 'P';
		vars->movements++;
		vars->mc.flip = 0;
	}
}

void	move_up(t_mlxs *vars, int x, int y)
{
	if (keyboard_event(vars->map[y - 1][x], x, y - 1, vars))
		return ;
	if (vars->map[y - 1][x] != '1')
	{
		vars->map[vars->mc.y][vars->mc.x] = '0';
		vars->mc.y--;
		vars->map[vars->mc.y][vars->mc.x] = 'P';
		vars->movements++;
	}
}

void	move_down(t_mlxs *vars, int x, int y)
{
	if (keyboard_event(vars->map[y + 1][x], x, y + 1, vars))
		return ;
	if (vars->map[y + 1][x] != '1')
	{
		vars->map[vars->mc.y][vars->mc.x] = '0';
		vars->mc.y++;
		vars->map[vars->mc.y][vars->mc.x] = 'P';
		vars->movements++;
	}
}
