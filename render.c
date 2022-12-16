/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 11:05:49 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/16 11:05:52 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	ft_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_len + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	victory_animation(t_mlxs *vars, int i, int j)
{
	t_img	*img;

	vars->end++;
	if (vars->end < 4)
	{
		img = vars->victory[vars->end - 1].img;
		mlx_put_image_to_window(vars->mlx, vars->win, img, j, i + 8);
	}
	if (vars->end == 6)
		ft_close(vars);
}

void	ft_put_image_to_window(t_mlxs *vars, t_img img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, x, y);
}

void	render_map(t_mlxs *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->height)
	{
		j = 0;
		while (j < vars->width)
		{
			load_map(vars, vars->map, i, j);
			load_characters(vars, vars->frame / 20000, i, j);
			j += 64;
		}
		i += 64;
	}
}

int	render_next_frame(t_mlxs *vars)
{
	char	*string;
	char	*poststr;

	vars->frame++;
	if (!(vars->frame % 20000))
	{
		mlx_clear_window(vars->mlx, vars->win);
		render_map(vars);
		poststr = ft_itoa(vars->movements);
		string = ft_strjoin("Movements: ", poststr);
		mlx_string_put(vars->mlx, vars->win, 5, 20, 0, string);
		free(poststr);
		free(string);
	}
	if (!(vars->frame % 50000) && !vars->end)
		enemy_manager(vars);
	if (!(vars->frame % 200000) && vars->end < 0)
		ft_close(vars);
	return (0);
}
