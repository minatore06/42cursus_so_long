/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:42:36 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/15 11:42:38 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
