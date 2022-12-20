/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_random_move.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 12:38:20 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/20 12:38:22 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

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
