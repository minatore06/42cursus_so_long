/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:07:36 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/15 11:08:01 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

static int	get_map_lenght(char *map_file)
{
	int		fd;
	int		i;
	char	*map_ln;

	i = 0;
	fd = open(map_file, O_RDONLY);
	map_ln = NULL;
	while (!i || map_ln)
	{
		if (map_ln)
			free(map_ln);
		map_ln = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

char	**get_map(char *map_file, t_mlxs *vars)
{
	int		fd;
	int		i;
	char	*map_ln;
	char	**map;

	map = malloc(sizeof(char *) * get_map_lenght(map_file));
	i = 0;
	fd = open(map_file, O_RDONLY);
	while (!i || map_ln)
	{
		map_ln = get_next_line(fd);
		map[i] = map_ln;
		i++;
	}
	vars->width = ft_strlen(map[0]);
	vars->height = i - 1;
	close(fd);
	return (map);
}

char	**dup_map(char **map)
{
	int		i;
	char	**dup;

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

void	*free_unfinished_map(void **map, int i)
{
	while (i >= 0)
	{
		free(map[i]);
		i--;
	}
	free(map);
	return (NULL);
}

void	free_map(void **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
