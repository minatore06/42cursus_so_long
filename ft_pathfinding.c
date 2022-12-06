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

int count_collectibles(char **map)
{
    int count;
    int i;
    int j;

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

static int is_exit_here(char **map, int x, int y)
{
    if (map[x + 1][y] == 'E' || map[x + 1][y] == 'C')
    {
        map[x + 1][y] = 'T';
        return (1);
    }
    if (map[x][y + 1] == 'E' || map[x][y + 1] == 'C')
    {
        map[x][y + 1] = 'T';
        return (1);
    }
    if (map[x - 1][y] == 'E' || map[x - 1][y] == 'C')
    {
        map[x - 1][y] = 'T';
        return (1);
    }
    if (map[x][y - 1] == 'E' || map[x][y - 1] == 'C')
    {
        map[x][y - 1] = 'T';
        return (1);
    }
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

char    **dup_map(char **map)
{
    int     i;
    char    **dup;

    i = 0;
    while (map[i])
        i++;
    i++;
    dup = malloc(sizeof(char *) * i);
    if (!dup)
        return (NULL);
    dup[i - 1] = 0;
    i = 0;
    while (map[i])
    {
        dup[i] = ft_strdup(map[i]);
        i++;
    }
    return (dup);
}

void    free_map(char **map)
{
    int i;

    i = 0;
    while (map[i])
    {
        free(map[i]);
        i++;
    }
    free(map);
}

void    get_player(char **map, int *px, int *py)
{
    int i;
    int j;

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

int	is_path_real(char **map)
{
	int	    px;
	int	    py;
    int     to_search;
    int     count;
    char    **map_cpy;

    map_cpy = dup_map(map);
    get_player(map_cpy, &px, &py);
    //settare a S celle cercate, settare a T celle da cercare, se E accanto a S fine, ogni 0 attorno a S diventa T
    to_search = 1;
    count = count_collectibles(map_cpy);
    count++;
    while (to_search)
	{
        to_search = 0;
        if (is_exit_here(map_cpy, px, py))
        {
            count--;
            if (!count)
               return (1);
        }
        if (map_cpy[px + 1][py] == '0')
			map_cpy[px + 1][py] = 'T';
		if (map_cpy[px][py + 1] == '0')
			map_cpy[px][py + 1] = 'T';
		if (map_cpy[px - 1][py] == '0')
			map_cpy[px - 1][py] = 'T';
		if (map_cpy[px][py - 1] == '0')
			map_cpy[px][py - 1] = 'T';
		searching(map_cpy, &px, &py, &to_search);
	}
    free_map(map_cpy);
    return (0);
}