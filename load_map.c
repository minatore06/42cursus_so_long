/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:16:02 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/16 11:16:03 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	load_map(t_mlxs *vars, char **map, int i, int j)
{
	if (map[i / 64][j / 64] == '1' && (i == 0 || j == 0
		|| i == vars->height - 64 || j == vars->width - 64))
		ft_put_image_to_window(vars, vars->border, j, i);
	else if (map[i / 64][j / 64] == '1')
		ft_put_image_to_window(vars, vars->wall, j, i);
	else if (map[i / 64][j / 64] == 'C')
		ft_put_image_to_window(vars, vars->collectible, j, i);
	else if (map[i / 64][j / 64] == 'E' && vars->c_collectible)
		ft_put_image_to_window(vars, vars->exit_close, j, i);
	else if (map[i / 64][j / 64] == 'E')
		ft_put_image_to_window(vars, vars->exit_open, j, i);
	else
		ft_put_image_to_window(vars, vars->terrain, j, i);
}

void	load_characters(t_mlxs *vars, int frame, int i, int j)
{
	if (vars->map[i / 64][j / 64] == 'N')
		ft_put_image_to_window(vars, vars->enemy.img[frame % 8], j, i + 16);
	else if (vars->map[i / 64][j / 64] == 'M' && vars->end < 1)
		ft_put_image_to_window(vars, vars->patrol.img[frame % 3], j, i);
	else if (vars->map[i / 64][j / 64] == 'M' && vars->end > 0)
		ft_put_image_to_window(vars, vars->patrol.img[3], j, i);
	else if (vars->map[i / 64][j / 64] == 'F' && vars->end == -1)
		ft_put_image_to_window(vars, vars->dead, j, i + 8);
	else if (vars->map[i / 64][j / 64] == 'F' && vars->end > 0)
		victory_animation(vars, i, j);
	else if (vars->map[i / 64][j / 64] == 'P' && !vars->mc.flip)
		ft_put_image_to_window(vars, vars->mc.img[frame % 4], j + 16, i);
	else if (vars->map[i / 64][j / 64] == 'P' && vars->mc.flip)
		ft_put_image_to_window(vars, vars->mc.img[frame % 4 + 4], j + 16, i);
}
