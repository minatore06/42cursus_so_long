/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_pathfinding.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:33:19 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/08 12:33:22 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	get_hcost(char **map, int x, int y)
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

static int	get_gcost(int x, int y, int i, int j)
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

int	min_cost(t_path cell_cost, t_path min_cell, int *min_fcost)
{
	int	fcost;

	fcost = cell_cost.gcost + cell_cost.hcost;
	if (fcost > 0 && (*min_fcost < 0 || fcost < *min_fcost)
		&& !cell_cost.passed)
	{
		*min_fcost = fcost;
		return (1);
	}
	else if (fcost > 0 && (*min_fcost < 0 || (fcost == *min_fcost
				&& cell_cost.hcost < min_cell.hcost)) && !cell_cost.passed)
	{
		*min_fcost = fcost;
		return (1);
	}
	return (0);
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

static int	get_lowest_cost(char **map, t_path **map_cost, int *x, int *y)
{
	int	i;
	int	j;
	int	min[2];
	int	min_fcost;

	set_get_lowest_cost_vars(&min_fcost, min, &i);
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

int	do_the_random_move(char **map, int n, int x, int y)
{
	if (n == 0 && map[y + 1][x] == '0')
	{
		map[y + 1][x] = 'M';
		map[y][x] = '0';
		return (1);
	}
	if (n == 1 && map[y][x + 1] == '0')
	{
		map[y][x + 1] = 'M';
		map[y][x] = '0';
		return (1);
	}
	if (n == 2 && map[y - 1][x] == '0')
	{
		map[y - 1][x] = 'M';
		map[y][x] = '0';
		return (1);
	}
	if (n == 3 && map[y][x - 1] == '0')
	{
		map[y][x - 1] = 'M';
		map[y][x] = '0';
		return (1);
	}
	return (0);
}

void	random_move(char **map, int x, int y)
{
	int	n;

	while (1)
	{
		n = rand() % 4;
		if (do_the_random_move(map, n, x, y))
			return ;
	}
}

void	init_map_cost(char **map, t_path **map_costs)
{
	int	i;
	int	j;

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
}

void	enemy_pathfinding(t_mlxs *vars, char **map, int x, int y)
{
	int		i;
	int		j;
	int		mod_i;
	int		mod_j;
	t_path	**map_costs;

	map_costs = malloc(sizeof(t_path *) * (vars->height / 64 + 1));
	i = 0;
	while (map[i])
		map_costs[i++] = malloc(sizeof(t_path) * (vars->width / 64));
	init_map_cost(map, map_costs);
	map_costs[i] = NULL;
	i = y;
	j = x;
	while (1)
	{
		mod_i = -1;
		while (mod_i < 2)
		{
			i += mod_i;
			mod_j = -1;
			while (mod_j < 2)
			{
				if (mod_j == mod_i || mod_j - mod_i == 2 || mod_j - mod_i == -2)
				{
					mod_j++;
					continue ;
				}
				j += mod_j;
				if (map[i][j])
				{
					if ((map[i][j] == '0' || map[i][j] == 'P')
						&& !map_costs[i][j].passed)
					{
						if ((map_costs[i][j].gcost == -1
							&& map_costs[i][j].hcost == -1)
									|| (get_gcost(j, i, y, x) <= map_costs[i][j].gcost
										&& get_hcost(map, j, i) < map_costs[i][j].hcost))
						{
							map_costs[i][j].gcost = get_gcost(j, i, y, x);
							map_costs[i][j].hcost = get_hcost(map, j, i);
							map_costs[i][j].prev_i = i - mod_i;
							map_costs[i][j].prev_j = j - mod_j;
						}
					}
					if (map[i][j] == 'P')
					{
						while (map[map_costs[i][j].prev_i][map_costs[i][j].prev_j] != 'M')
						{
							mod_i = map_costs[i][j].prev_i;
							mod_j = map_costs[i][j].prev_j;
							i = mod_i;
							j = mod_j;
						}
						if (map[i][j] == 'P')
						{
							vars->end = -1;
							map[i][j] = 'F';
						}
						else
						{
							map[map_costs[i][j].prev_i][map_costs[i][j].prev_j] = '0';
							map[i][j] = 'M';
						}
						free_map((void **)map_costs);
						return ;
					}
				}
				j -= mod_j;
				mod_j++;
			}
			i -= mod_i;
			mod_i++;
		}
		if (!get_lowest_cost(vars->map, map_costs, &j, &i))
			break ;
	}
	random_move(vars->map, x, y);
	free_map((void **)map_costs);
}

void	enemy_manager(t_mlxs *vars)
{
	int		i;
	int		j;
	char	**map_cpy;

	map_cpy = dup_map(vars->map);
	i = 0;
	while (map_cpy[i])
	{
		j = 0;
		while (map_cpy[i][j])
		{
			if (map_cpy[i][j] == 'M')
				enemy_pathfinding(vars, vars->map, j, i);
			j++;
		}
		i++;
	}
	free_map((void **)map_cpy);
}

/*
void	print_map(char **map, t_path **map_costs)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ft_printf("%d+%d=%d %d| ", map_costs[i][j].gcost, map_costs[i][j].hcost, map_costs[i][j].gcost + map_costs[i][j].hcost, map_costs[i][j].passed);
			j++;
		}
		ft_printf("<\n");
		i++;
	}
	ft_printf("\n");
}
*/
