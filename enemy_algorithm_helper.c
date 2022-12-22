/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_algorithm_helper.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:40:17 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/20 12:40:19 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	get_hcost(char **map, int x, int y)
{
	int	i;
	int	j;
	int	dist_x;
	int	dist_y;
	int	cost;

	cost = 0;
	get_player(map, &j, &i);
	dist_y = i - y;
	dist_x = j - x;
	if (dist_y < 0)
		dist_y *= -1;
	if (dist_x < 0)
		dist_x *= -1;
	while (dist_y || dist_x)
	{
		cost += 10;
		if (dist_y)
			dist_y--;
		else if (dist_x)
			dist_x--;
	}
	return (cost);
}

int	get_gcost(int x, int y, int i, int j)
{
	int	dist_x;
	int	dist_y;
	int	cost;

	cost = 0;
	dist_y = i - y;
	dist_x = j - x;
	if (dist_y < 0)
		dist_y *= -1;
	if (dist_x < 0)
		dist_x *= -1;
	while (dist_y || dist_x)
	{
		cost += 10;
		if (dist_y)
			dist_y--;
		else if (dist_x)
			dist_x--;
	}
	return (cost);
}

int	min_cost(t_path cell_cost, t_path min_cell, int *min_fcost)
{
	int	fcost;

	fcost = cell_cost.gcost + cell_cost.hcost;
	if (fcost > 0 && ((*min_fcost) < 0 || fcost < (*min_fcost))
		&& !cell_cost.passed)
	{
		(*min_fcost) = fcost;
		return (1);
	}
	else if (fcost > 0 && ((*min_fcost) < 0 || (fcost == (*min_fcost)
				&& cell_cost.hcost < min_cell.hcost)) && !cell_cost.passed)
	{
		(*min_fcost) = fcost;
		return (1);
	}
	return (0);
}

int	get_lowest_cost(char **map, t_path **map_cost, int *x, int *y)
{
	int	i;
	int	j;
	int	min[2];
	int	min_fcost;

	set_get_lowest_cost_vars(&min_fcost, min);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (min_cost(map_cost[i][j], map_cost[min[0]][min[1]], &min_fcost))
			{
				min[0] = i;
				min[1] = j;
			}
			j++;
		}
		i++;
	}
	if (min_fcost != -1)
		return (is_lowest_cost(map_cost, min, x, y));
	return (0);
}
