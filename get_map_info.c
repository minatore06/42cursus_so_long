/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:39:01 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/15 11:39:03 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	count_zeros(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	count_free_space(char **map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				map[i][j] = '1';
				if (is_path_real(map))
					count++;
				map[i][j] = '0';
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	get_player(char **map, int *px, int *py)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				*px = j;
				*py = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	count_collectibles(char **map)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	is_exit_here(char **map, int x, int y)
{
	if (map[y + 1][x] == 'E' || map[y + 1][x] == 'C')
	{
		map[y + 1][x] = 'T';
		return (1);
	}
	if (map[y][x + 1] == 'E' || map[y][x + 1] == 'C')
	{
		map[y][x + 1] = 'T';
		return (1);
	}
	if (map[y - 1][x] == 'E' || map[y - 1][x] == 'C')
	{
		map[y - 1][x] = 'T';
		return (1);
	}
	if (map[y][x - 1] == 'E' || map[y][x - 1] == 'C')
	{
		map[y][x - 1] = 'T';
		return (1);
	}
	return (0);
}
