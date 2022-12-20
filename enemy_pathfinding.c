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

void	path_to_player(t_path **m_costs, char **map, t_cords c, int *mod)
{
	if ((map[c.i][c.j] == '0' || map[c.i][c.j] == 'P')
				&& !m_costs[c.i][c.j].passed)
	{
		if ((m_costs[c.i][c.j].gcost == -1 && m_costs[c.i][c.j].hcost == -1)
				|| (get_gcost(c.j, c.i, c.y, c.x) <= m_costs[c.i][c.j].gcost
					&& get_hcost(map, c.j, c.i) < m_costs[c.i][c.j].hcost))
		{
			m_costs[c.i][c.j].gcost = get_gcost(c.j, c.i, c.y, c.x);
			m_costs[c.i][c.j].hcost = get_hcost(map, c.j, c.i);
			m_costs[c.i][c.j].prev_i = c.i - mod[0];
			m_costs[c.i][c.j].prev_j = c.j - mod[1];
		}
	}
}

int	found_player(t_path **m_cst, t_mlxs *v, t_cords c, int *mod)
{
	if (v->map[c.i][c.j] == 'P')
	{
		while (v->map[m_cst[c.i][c.j].prev_i][m_cst[c.i][c.j].prev_j] != 'M')
		{
			mod[0] = m_cst[c.i][c.j].prev_i;
			mod[1] = m_cst[c.i][c.j].prev_j;
			c.i = mod[0];
			c.j = mod[1];
		}
		if (v->map[c.i][c.j] == 'P')
		{
			v->end = -1;
			v->map[c.i][c.j] = 'F';
		}
		else
		{
			v->map[m_cst[c.i][c.j].prev_i][m_cst[c.i][c.j].prev_j] = '0';
			v->map[c.i][c.j] = 'M';
		}
		free_map((void **)m_cst);
		return (1);
	}
	return (0);
}
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
void	enemy_pathfinding(t_mlxs *vars, char **map, int x, int y)
{
	t_cords	cords;
	int		mod[2];
	int		n;
	t_path	**map_costs;

	map_costs = init_map_cost(map, vars);
	cords.i = y;
	cords.j = x;
	cords.x = x;
	cords.y = y;
	n = 0;
	while (1)
	{
		while (get_mod_cords(&n, mod, &cords))
		{
			if (map[cords.i][cords.j])
			{
				path_to_player(map_costs, map, cords, mod);
				if (found_player(map_costs, vars, cords, mod))
					return ;
			}
		}
		print_map(map, map_costs);
		if (!get_lowest_cost(vars->map, map_costs, &cords.j, &cords.i))
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
