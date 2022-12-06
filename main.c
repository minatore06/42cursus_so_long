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

char	**get_map(char *map_file, t_mlxs *vars)
{
	int		fd;
	int		i;
	char	*map_ln;
	char	**map;

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
	map = malloc(sizeof(char *) * i);
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
	return (map);
}

//controlla che la mappa sia un rettangolo, 0 rettangolo; 1 non rettangolo
int	check_map_lenght(char **map)
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
//err 1: no bordi; 2: char extra; 3/-3: no/too much E; 4/-4: no/too much P; 5: no collectibles; 6: no rettangolo
int	map_check(char **map, char *set, t_mlxs *vars)
{
	int	i;
	int	j;
	int	exit;
	int	start_pos;
	int	collectibles;

	exit = 0;
	start_pos = 0;
	collectibles = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strchr(map[i], 'E') != ft_strrchr(map[i], 'E'))
			return (-3);
		else if (ft_strchr(map[i], 'E'))
			exit++;
		if (exit > 1)
			return (-3);
		if (ft_strchr(map[i], 'P') != ft_strrchr(map[i], 'P'))
			return (-4);
		else if (ft_strchr(map[i], 'P'))
			start_pos++;
		if (start_pos > 1)
			return (-4);
		if (ft_strchr(map[i], 'C'))
			collectibles++;
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if ((i == 0 || j == 0 || i == vars->height || j == vars->width) && map[i][j] != '1')
				return (1);
			if (!ft_strchr(set, map[i][j]))
				return (2);
			
			j++;
		}
		i++;
	}
	if (!exit)
		return (3);
	if (!start_pos)
		return (4);
	if (!collectibles)
		return (5);
	if (check_map_lenght(map))
		return (6);
	if (!is_path_real(map))
		return (7);
	return (0);
}

int	main(int argc, char *argv[])
{
	int		i;
	int		err_code;
	t_mlxs	mlx_vars;
	char	*capybara_an[8];
	char	*mc_walk[8];

	if (argc != 2)
		return (0);
	mlx_vars.map = get_map(argv[1], &mlx_vars);
	err_code = map_check(mlx_vars.map, "01CEP", &mlx_vars);
	if (err_code)
	{
		ft_printf("Error\n%d", err_code);
		return (0);
	}
	mlx_vars.c_collectible = count_collectibles(mlx_vars.map);

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
	mc_walk[4] = "./textures/mc_walk_animation/walk_flip1.xpm";
	mc_walk[5] = "./textures/mc_walk_animation/walk_flip2.xpm";
	mc_walk[6] = "./textures/mc_walk_animation/walk_flip3.xpm";
	mc_walk[7] = "./textures/mc_walk_animation/walk_flip4.xpm";
	mlx_vars.frame = 0;
	mlx_vars.movements = 0;
	mlx_vars.mlx = mlx_init();
	if (mlx_vars.mlx == NULL)
		return (1);
	mlx_vars.terrain.img[0].img = mlx_xpm_file_to_image(mlx_vars.mlx, "./textures/map/grass.xpm", &mlx_vars.terrain.width[0], &mlx_vars.terrain.height[0]);
	if (!mlx_vars.terrain.img[0].img)
	{
		mlx_destroy_display(mlx_vars.mlx);
		free(mlx_vars.mlx);
		ft_printf("Scoppiato tutto");
		return (1);
	}
	mlx_vars.terrain.img[0].addr = mlx_get_data_addr(mlx_vars.terrain.img[0].img, &mlx_vars.terrain.img[0].bpp, &mlx_vars.terrain.img[0].line_len, &mlx_vars.terrain.img[0].endian);
	mlx_vars.border.img[0].img = mlx_xpm_file_to_image(mlx_vars.mlx, "./textures/map/water.xpm", &mlx_vars.border.width[0], &mlx_vars.border.height[0]);
	if (!mlx_vars.border.img[0].img)
	{
		mlx_destroy_display(mlx_vars.mlx);
		free(mlx_vars.mlx);
		ft_printf("Scoppiato tutto");
		return (1);
	}
	mlx_vars.border.img[0].addr = mlx_get_data_addr(mlx_vars.border.img[0].img, &mlx_vars.border.img[0].bpp, &mlx_vars.border.img[0].line_len, &mlx_vars.border.img[0].endian);
	mlx_vars.wall.img[0].img = mlx_xpm_file_to_image(mlx_vars.mlx, "./textures/map/rock.xpm", &mlx_vars.wall.width[0], &mlx_vars.wall.height[0]);
	if (!mlx_vars.wall.img[0].img)
	{
		mlx_destroy_display(mlx_vars.mlx);
		free(mlx_vars.mlx);
		ft_printf("Scoppiato tutto");
		return (1);
	}
	mlx_vars.wall.img[0].addr = mlx_get_data_addr(mlx_vars.wall.img[0].img, &mlx_vars.wall.img[0].bpp, &mlx_vars.wall.img[0].line_len, &mlx_vars.wall.img[0].endian);
	mlx_vars.collectible.img[0].img = mlx_xpm_file_to_image(mlx_vars.mlx, "./textures/map/crystal.xpm", &mlx_vars.collectible.width[0], &mlx_vars.collectible.height[0]);
	if (!mlx_vars.collectible.img[0].img)
	{
		mlx_destroy_display(mlx_vars.mlx);
		free(mlx_vars.mlx);
		ft_printf("Scoppiato tutto");
		return (1);
	}
	mlx_vars.collectible.img[0].addr = mlx_get_data_addr(mlx_vars.collectible.img[0].img, &mlx_vars.collectible.img[0].bpp, &mlx_vars.collectible.img[0].line_len, &mlx_vars.collectible.img[0].endian);
	mlx_vars.exit.img[0].img = mlx_xpm_file_to_image(mlx_vars.mlx, "./textures/map/portal_closed.xpm", &mlx_vars.exit.width[0], &mlx_vars.exit.height[0]);
	if (!mlx_vars.exit.img[0].img)
	{
		mlx_destroy_display(mlx_vars.mlx);
		free(mlx_vars.mlx);
		ft_printf("Scoppiato tutto");
		return (1);
	}
	mlx_vars.exit.img[0].addr = mlx_get_data_addr(mlx_vars.exit.img[0].img, &mlx_vars.exit.img[0].bpp, &mlx_vars.exit.img[0].line_len, &mlx_vars.exit.img[0].endian);
	mlx_vars.exit.img[1].img = mlx_xpm_file_to_image(mlx_vars.mlx, "./textures/map/portal_open.xpm", &mlx_vars.exit.width[1], &mlx_vars.exit.height[1]);
	if (!mlx_vars.exit.img[1].img)
	{
		mlx_destroy_display(mlx_vars.mlx);
		free(mlx_vars.mlx);
		ft_printf("Scoppiato tutto");
		return (1);
	}
	mlx_vars.exit.img[1].addr = mlx_get_data_addr(mlx_vars.exit.img[1].img, &mlx_vars.exit.img[1].bpp, &mlx_vars.exit.img[1].line_len, &mlx_vars.exit.img[1].endian);
	mlx_vars.width *= mlx_vars.terrain.width[0];
	mlx_vars.height *= mlx_vars.terrain.height[0];
	mlx_vars.win = mlx_new_window(mlx_vars.mlx, mlx_vars.width, mlx_vars.height, "Gioco da GAMING!");
	if (mlx_vars.win == NULL)
	{
		free(mlx_vars.win);
		return (1);
	}
	i = 0;
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
	i = 0;
	while (i < 8)
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
	mlx_vars.mc.flip = 0;
	get_player(mlx_vars.map, &mlx_vars.mc.x, &mlx_vars.mc.y);
	ft_printf("x %d, y %d\n", mlx_vars.mc.x, mlx_vars.mc.y);
	mlx_vars.enemy.x = 500;
	mlx_vars.enemy.y = 500;
	render_map(&mlx_vars);
	mlx_hook(mlx_vars.win, 3, 1L<<1, key_press_up, &mlx_vars);
	mlx_hook(mlx_vars.win, 17, 0, ft_close, &mlx_vars);
	mlx_loop_hook(mlx_vars.mlx, render_next_frame, &mlx_vars);
	mlx_loop(mlx_vars.mlx);
	mlx_destroy_display(mlx_vars.mlx);
	free(mlx_vars.mlx);
}