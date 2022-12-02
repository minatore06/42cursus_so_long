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

static void    reset_map(char **map)
{
    int i;
    int j;

    i = 1;
    while (map[i])
    {
        j = 1;
        while (map[i][j])
        {
            if (map[i][j] == 'S' || map[i][j] == 'T')
                map[i][j] = '0';
            j++;
        }
        i++;
    }
}

static int is_exit_here(char **map, int x, int y)
{
    if (map[x + 1][y] == 'E')
        return (1);
    if (map[x][y + 1] == 'E')
        return (1);
    if (map[x - 1][y] == 'E')
        return (1);
    if (map[x][y - 1] == 'E')
        return (1);
    return (0);
}

static void    searching(char **map, int *px, int *py, int *to_search)
{
    int i;
    int j;

    i = 1;
    while (map[i])
    {
        j = 1;
        while (map[i][j])
        {
            if (map[i][j] == 'T')
            {
                map[i][j] = 'S';
                *px = i;
                *py = j;
                *to_search = 1;
                return ;
            }
            j++;
        }
        i++;
    }
}

int	is_path_real(char **map)
{
	int	i;
	int	j;
	int	px;
	int	py;
    int to_search;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
				break;
			j++;
		}
		if (map[i][j] == 'P')
			break;
		i++;
	}
	px = i;
	py = j;//settare a S celle cercate, settare a T celle da cercare, se E accanto a S fine, ogni 0 attorno a S diventa T
    to_search = 1;
    while (to_search)
	{
        to_search = 0;
        if (is_exit_here(map, px, py))
        {
            reset_map(map);
            return (1);
        }
        if (map[px + 1][py] == '0')
			map[px + 1][py] = 'T';
		if (map[px][py + 1] == '0')
			map[px][py + 1] = 'T';
		if (map[px - 1][py] == '0')
			map[px - 1][py] = 'T';
		if (map[px][py - 1] == '0')
			map[px][py - 1] = 'T';
		searching(map, &px, &py, &to_search);
	}
    reset_map(map);
    return (0);
}