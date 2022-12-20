/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_pathfinding_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:37:12 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/20 12:37:15 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	get_enemy_position(char **map, int *ex, int *ey)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'M')
			{
				*ex = j;
				*ey = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

void	set_get_lowest_cost_vars(int *min_fcost, int *min, int *i)
{
	*min_fcost = -1;
	min[0] = 0;
	min[1] = 0;
	*i = 0;
}

int	is_lowest_cost(t_path **map_cost, int *min, int *x, int *y)
{
	map_cost[min[0]][min[1]].passed = 1;
	*x = min[1];
	*y = min[0];
	return (1);
}

t_path	**init_map_cost(char **map, t_mlxs *vars)
{
	int		i;
	int		j;
	t_path	**map_costs;

	map_costs = malloc(sizeof(t_path *) * (vars->height / 64 + 1));
	i = 0;
	while (map[i])
		map_costs[i++] = malloc(sizeof(t_path) * (vars->width / 64));
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			map_costs[i][j].gcost = -1;
			map_costs[i][j].hcost = -1;
			map_costs[i][j].passed = 0;
			j++;
		}
		i++;
	}
	map_costs[i] = NULL;
	return (map_costs);
}

int	get_mod_cords(int *n, int *mod, t_cords *cords)
{
	(*n)++;
	if (*n == 1)
	{
		mod[0] = -1;
		mod[1] = 0;
	}
	else if (*n == 2)
	{
		mod[0] = 0;
		mod[1] = 1;
	}
	else if (*n == 3)
	{
		mod[0] = 1;
		mod[1] = 0;
	}
	else
	{
		mod[0] = 0;
		mod[1] = -1;
		*n = 0;
	}
	cords->i += mod[0];
	cords->j += mod[1];
	return (*n);
}
