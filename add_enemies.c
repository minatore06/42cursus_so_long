/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_enemies.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 15:59:08 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/22 15:59:12 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	put_enemy_on_map(char **map, int i, int j, int x)
{
	if (!(x % 5))
		map[i][j] = 'M';
	else
		map[i][j] = 'N';
	return (--x);
}

void	put_enemies(t_mlxs *vars)
{
	int	i;
	int	j;
	int	x;
	int	free_space;
	int	space_count;

	space_count = count_zeros(vars->map);
	free_space = sqrt(count_free_space(vars->map));
	x = free_space;
	while (x && space_count)
	{
		i = rand() % (vars->height / 64);
		j = rand() % (vars->width / 64);
		if (vars->map[i][j] != '0')
			continue ;
		vars->map[i][j] = '1';
		if (!is_path_real(vars->map))
		{
			space_count--;
			vars->map[i][j] = '0';
			continue ;
		}
		x = put_enemy_on_map(vars->map, i, j, x);
	}
}
