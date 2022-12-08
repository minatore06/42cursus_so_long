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

static void searching(char **map, int *px, int *py, int *to_search)
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

static void look_for_search(char **map, int *count)
{
    int i;
    int j;

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
                if (map[i + 1][j] == '0')
                    map[i + 1][j] = 'T';
                if (map[i][j + 1] == '0')
                    map[i][j + 1] = 'T';
                if (map[i - 1][j] == '0')
                    map[i - 1][j] = 'T';
                if (map[i][j - 1] == '0')
                    map[i][j - 1] = 'T';
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

void    free_map(void **map)
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
            count--;
        if (map_cpy[py + 1][px] == '0')
            map_cpy[py + 1][px] = 'T';
        if (map_cpy[py][px + 1] == '0')
            map_cpy[py][px + 1] = 'T';
        if (map_cpy[py - 1][px] == '0')
            map_cpy[py - 1][px] = 'T';
        if (map_cpy[py][px - 1] == '0')
            map_cpy[py][px - 1] = 'T';
        look_for_search(map_cpy, &count);
        //print_map(map_cpy);
        if (!count)
            return (1);
		searching(map_cpy, &px, &py, &to_search);
	}
    free_map((void **)map_cpy);
    return (0);
}