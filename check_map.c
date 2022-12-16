/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:10:07 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/15 11:10:09 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	check_map_lenght(char **map)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
			j++;
		if (!i)
			tmp = j;
		else if (j != tmp)
			return (1);
		i++;
	}
	return (0);
}

static int	check_exit(char **map)
{
	int	i;
	int	exit;

	exit = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], 'E') != ft_strrchr(map[i], 'E'))
			exit += 2;
		else if (ft_strchr(map[i], 'E'))
			exit++;
		i++;
	}
	if (!exit)
		return (3);
	if (exit > 1)
		return (-3);
	return (0);
}

static int	check_start(char **map)
{
	int	i;
	int	start_pos;

	start_pos = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], 'P') != ft_strrchr(map[i], 'P'))
			start_pos += 2;
		else if (ft_strchr(map[i], 'P'))
			start_pos++;
		i++;
	}
	if (!start_pos)
		return (4);
	if (start_pos > 1)
		return (-4);
	return (0);
}

static int	check_map_content(char **map, char *set, t_mlxs *vars)
{
	int	i;
	int	j;
	int	collectibles;

	collectibles = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if ((i == 0 || j == 0 || i == vars->height
					|| j == vars->width) && map[i][j] != '1')
				return (1);
			if (!ft_strchr(set, map[i][j]))
				return (2);
			if (map[i][j] == 'C')
				collectibles++;
			j++;
		}
		i++;
	}
	if (!collectibles)
		return (5);
	return (0);
}

int	map_check(char **map, char *set, t_mlxs *vars)
{
	int	err;

	err = check_exit(map);
	if (err)
		return (err);
	err = check_start(map);
	if (err)
		return (err);
	err = check_map_content(map, set, vars);
	if (err)
		return (err);
	if (check_map_lenght(map))
		return (6);
	if (!is_path_real(map))
		return (7);
	return (0);
}
