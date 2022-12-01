/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 16:04:24 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/30 16:04:26 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	main(void)
{
	int		i;
	t_mlxs	mlx_vars;
	char	*capybara_an[8];
	char	*mc_walk[4];

	capybara_an[0] = "./textures/capybara_idle_animation/idle1.xpm";
	capybara_an[1] = "./textures/capybara_idle_animation/idle2.xpm";
	capybara_an[2] = "./textures/capybara_idle_animation/idle3.xpm";
	capybara_an[3] = "./textures/capybara_idle_animation/idle4.xpm";
	capybara_an[4] = "./textures/capybara_idle_animation/idle5.xpm";
	capybara_an[5] = "./textures/capybara_idle_animation/idle6.xpm";
	capybara_an[6] = "./textures/capybara_idle_animation/idle7.xpm";
	capybara_an[7] = "./textures/capybara_idle_animation/idle8.xpm";
	mc_walk[0] = "./textures/mc_walk_animation/walk1.xpm";
	mc_walk[1] = "./textures/mc_walk_animation/walk2.xpm";
	mc_walk[2] = "./textures/mc_walk_animation/walk3.xpm";
	mc_walk[3] = "./textures/mc_walk_animation/walk4.xpm";
	mlx_vars.frame = 0;
	mlx_vars.mlx = mlx_init();
	if (mlx_vars.mlx == NULL)
		return (1);
	mlx_vars.win = mlx_new_window(mlx_vars.mlx, 1920, 1080, "Gioco da GAMING!");
	if (mlx_vars.win == NULL)
	{
		free(mlx_vars.win);
		return (1);
	}
	mlx_vars.img.img = mlx_new_image(mlx_vars.mlx, 1920, 1080);
	mlx_vars.img.addr = mlx_get_data_addr(mlx_vars.img.img, &mlx_vars.img.bpp, &mlx_vars.img.line_len, &mlx_vars.img.endian);

	i = 0;
	mlx_vars.enemy.x = 500;
	mlx_vars.enemy.y = 500;
	while (i < 8)
	{
		mlx_vars.enemy.img[i].img = mlx_xpm_file_to_image(mlx_vars.mlx, capybara_an[i], &mlx_vars.enemy.width[i], &mlx_vars.enemy.height[i]);
		if (!mlx_vars.enemy.img[i].img)
		{
			mlx_destroy_display(mlx_vars.mlx);
			free(mlx_vars.mlx);
			ft_printf("Scoppiato tutto");
			return (1);
		}
		mlx_vars.enemy.img[i].addr = mlx_get_data_addr(mlx_vars.enemy.img[i].img, &mlx_vars.enemy.img[i].bpp, &mlx_vars.enemy.img[i].line_len, &mlx_vars.enemy.img[i].endian);
		i++;
	}
	mlx_vars.mc.x = 1000;
	mlx_vars.mc.y = 500;
	i = 0;
	while (i < 4)
	{
		mlx_vars.mc.img[i].img = mlx_xpm_file_to_image(mlx_vars.mlx, mc_walk[i], &mlx_vars.mc.width[i], &mlx_vars.mc.height[i]);
		if (!mlx_vars.mc.img[i].img)
		{
			mlx_destroy_display(mlx_vars.mlx);
			free(mlx_vars.mlx);
			ft_printf("Scoppiato tutto");
			return (1);
		}
		mlx_vars.mc.img[i].addr = mlx_get_data_addr(mlx_vars.mc.img[i].img, &mlx_vars.mc.img[i].bpp, &mlx_vars.mc.img[i].line_len, &mlx_vars.mc.img[i].endian);
		i++;
	}
	mlx_hook(mlx_vars.win, 2, 1L<<0, key_press_down, &mlx_vars);
	mlx_hook(mlx_vars.win, 17, 0, ft_close, &mlx_vars);
	mlx_loop_hook(mlx_vars.mlx, render_next_frame, &mlx_vars);
	mlx_loop(mlx_vars.mlx);
	mlx_destroy_display(mlx_vars.mlx);
	free(mlx_vars.mlx);
}