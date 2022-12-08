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

static int get_hcost(char **map, int x, int y)
{
    int i;
    int j;
    int dist_x;
    int dist_y;
    int cost;

    cost = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'P')
            {
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
                //cost += 14 * dist_y;
                break ;
            }
            j++;
        }
        if (cost)
            break ;
        i++;
    }
    return (cost);
}

static int get_gcost(char **map, int x, int y)
{
    int i;
    int j;
    int dist_x;
    int dist_y;
    int cost;

    cost = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == 'M')
            {
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
                //cost += 14 * dist_y;
                break ;
            }
            j++;
        }
        if (cost)
            break ;
        i++;
    }
    return (cost);
}

void    get_enemy_position(char **map, int *ex, int *ey)
{
    int i;
    int j;

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

static void    get_lowest_cost(char **map, t_path **map_cost, int *x, int *y)
{
    int i;
    int j;
    int min[2];
    int min_fcost;
    int fcost;

    min_fcost = -1;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            fcost = map_cost[i][j].gcost + map_cost[i][j].hcost;
            if (fcost > 0 && (min_fcost < 0 || fcost < min_fcost) && !map_cost[i][j].passed)
            {
                min[0] = i;
                min[1] = j;
                min_fcost = fcost;
            }
            else if (fcost > 0 && (min_fcost < 0 || (fcost == min_fcost && map_cost[i][j].hcost < map_cost[min[0]][min[1]].hcost)) && !map_cost[i][j].passed)
            {
                min[0] = i;
                min[1] = j;
                min_fcost = fcost;
            }
            j++;
        }
        i++;
    }
    map_cost[min[0]][min[1]].passed = 1;
    *x = min[1];
    *y = min[0];
}

void    print_map(char **map, t_path **map_costs)
{
    int i;
    int j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            ft_printf("%d | ", map_costs[i][j].gcost + map_costs[i][j].hcost);
            j++;
        }
        ft_printf("\n");
        i++;
    }
    ft_printf("\n");
}

void    enemy_pathfinding(t_mlxs *vars)
{
    int     i;
    int     j;
    int     mod_i;
    int     mod_j;
    t_path **map_costs;

    map_costs = malloc(sizeof(t_path *) * (vars->height / 64 + 1));
    i = 0;
    while (vars->map[i])
    {
        map_costs[i] = malloc(sizeof(t_path) * (vars->width / 64));
        j = 0;
        while (vars->map[i][j])
        {
            map_costs[i][j].gcost = -1;
            map_costs[i][j].hcost = -1;
            map_costs[i][j++].passed = 0;
        }
        i++;
    }
    map_costs[i] = NULL;
    get_enemy_position(vars->map, &j, &i);
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
                if (vars->map[i][j])
                {
                    if ((vars->map[i][j] == '0' || vars->map[i][j] == 'P') && !map_costs[i][j].passed)
                    {
                        if ((map_costs[i][j].gcost == -1 && map_costs[i][j].hcost == -1) || (get_gcost(vars->map, j, i) <= map_costs[i][j].gcost && get_hcost(vars->map, j, i) < map_costs[i][j].hcost))
                        {
                            map_costs[i][j].gcost = get_gcost(vars->map, j, i);
                            map_costs[i][j].hcost = get_hcost(vars->map, j, i);
                            map_costs[i][j].prev_i = i - mod_i;
                            map_costs[i][j].prev_j = j - mod_j;
                        }
                    }
                    if (vars->map[i][j] == 'P')
                    {
                        print_map(vars->map, map_costs);
                        while(vars->map[map_costs[i][j].prev_i][map_costs[i][j].prev_j] != 'M')
                        {
                            mod_i = map_costs[i][j].prev_i;
                            mod_j = map_costs[i][j].prev_j;
                            i = mod_i;
                            j = mod_j;
                        }
                        if (vars->map[i][j] == 'P')
                        {
                            vars->end = -1;
                            vars->map[i][j] = 'F';
                        }
                        else
                        {
                            vars->map[map_costs[i][j].prev_i][map_costs[i][j].prev_j] = '0';
                            vars->map[i][j] = 'M';
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
        get_lowest_cost(vars->map, map_costs, &j, &i);
    }
}
//1111111111
//10001C0001
//1100C00101
//1M00001111
//1E00100011
//100001C001
//1111111111