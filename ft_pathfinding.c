/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathfinding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:18:13 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/02 18:18:16 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static void	searching(char **map, int *px, int *py, int *to_search)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 1;
		while (map[i][j])
		{
			if (map[i][j] == 'T')
			{
				map[i][j] = 'S';
				*px = j;
				*py = i;
				*to_search = 1;
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	put_tosearch(char **map, int i, int j)
{
	if (map[i + 1][j] == '0')
		map[i + 1][j] = 'T';
	if (map[i][j + 1] == '0')
		map[i][j + 1] = 'T';
	if (map[i - 1][j] == '0')
		map[i - 1][j] = 'T';
	if (map[i][j - 1] == '0')
		map[i][j - 1] = 'T';
}

static void	look_for_search(char **map, int *count)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S')
			{		
				if (is_exit_here(map, j, i))
					(*count)--;
				put_tosearch(map, i, j);
			}
			j++;
		}
		i++;
	}
}

static int	research_path(char **map, int px, int py, int count)
{
	int	to_search;

	to_search = 1;
	while (to_search)
	{
		to_search = 0;
		if (is_exit_here(map, px, py))
			count--;
		put_tosearch(map, py, px);
		look_for_search(map, &count);
		if (!count)
		{
			free_map((void **)map);
			return (1);
		}
		searching(map, &px, &py, &to_search);
	}
	free_map((void **)map);
	return (0);
}

int	is_path_real(char **map)
{
	int		px;
	int		py;
	int		count;
	char	**map_cpy;

	px = 0;
	py = 0;
	map_cpy = dup_map(map);
	get_player(map_cpy, &px, &py);
	count = count_collectibles(map_cpy);
	count++;
	return (research_path(map_cpy, px, py, count));
}
