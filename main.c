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

void	put_enemies(t_mlxs *vars)
{
	int	i;
	int	j;
	int	x;
	int	free_space;
	int	space_count;

	space_count = count_zeros(vars->map);
	free_space = sqrt(count_free_space(vars->map));
	x = free_space;
	while (x && space_count)
	{
		i = rand() % (vars->height / 64);
		j = rand() % (vars->width / 64);
		if (vars->map[i][j] != '0')
			continue ;
		vars->map[i][j] = '1';
		if (!is_path_real(vars->map))
		{
			space_count--;
			vars->map[i][j] = '0';
			continue ;
		}
		if (!(x % 5))
			vars->map[i][j] = 'M';
		else
			vars->map[i][j] = 'N';
		x--;
	}
}

void	get_error(int err_code)
{
	if (err_code == 1)
		ft_printf("Mappa aperta, non e' circondata da muri");
	else if (err_code == 2)
		ft_printf("Nella mappa sono presenti caratteri non permessi");
	else if (err_code == 3)
		ft_printf("Uscita non presente");
	else if (err_code == -3)
		ft_printf("Molteplici uscite presenti");
	else if (err_code == 4)
		ft_printf("Posizione iniziale non presente");
	else if (err_code == -4)
		ft_printf("Molteplici posizioni iniziali presenti");
	else if (err_code == 5)
		ft_printf("Nessun collezionabile presente");
	else if (err_code == 6)
		ft_printf("Mappa non rettangolare");
	else if (err_code == 7)
		ft_printf("Mappa impossibile, non e' presente un percorso che ne permetta il completamento");
}

void	get_img(t_mlxs *vars, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(vars->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		ft_printf("Error\nProblema col caricamento dell'immagine");
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

int	main(int argc, char *argv[])
{
	int		i;
	int		err_code;
	t_mlxs	mlx_vars;
	char	*capybara_an[8];
	char	*mc_walk[8];
	char	*victory_an[3];
	char	*patrol_an[4];

	if (argc != 2)
		return (0);
	mlx_vars.map = get_map(argv[1], &mlx_vars);
	err_code = map_check(mlx_vars.map, "01CEP", &mlx_vars);
	if (err_code)
	{
		free_map((void **)mlx_vars.map);
		ft_printf("Error\n");
		get_error(err_code);
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
	victory_an[0] = "./textures/map/victory1.xpm";
	victory_an[1] = "./textures/map/victory2.xpm";
	victory_an[2] = "./textures/map/victory3.xpm";
	patrol_an[0] = "./textures/patrol/enemy_patrol1.xpm";
	patrol_an[1] = "./textures/patrol/enemy_patrol2.xpm";
	patrol_an[2] = "./textures/patrol/enemy_patrol3.xpm";
	patrol_an[3] = "./textures/patrol/enemy_patrol_dead.xpm";
	mlx_vars.frame = 0;
	mlx_vars.movements = 0;
	mlx_vars.end = 0;
	mlx_vars.mlx = mlx_init();
	if (mlx_vars.mlx == NULL)
		return (1);
	get_img(&mlx_vars, &mlx_vars.terrain, "./textures/map/grass.xpm");
	get_img(&mlx_vars, &mlx_vars.border, "./textures/map/water.xpm");
	get_img(&mlx_vars, &mlx_vars.wall, "./textures/map/rock.xpm");
	get_img(&mlx_vars, &mlx_vars.collectible, "./textures/map/crystal.xpm");
	get_img(&mlx_vars, &mlx_vars.exit_close, "./textures/map/portal_closed.xpm");
	get_img(&mlx_vars, &mlx_vars.exit_open, "./textures/map/portal_open.xpm");
	get_img(&mlx_vars, &mlx_vars.dead, "./textures/map/dead.xpm");
	i = 0;
	while (i < 8)
	{
		get_img(&mlx_vars, &mlx_vars.enemy.img[i], capybara_an[i]);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		get_img(&mlx_vars, &mlx_vars.mc.img[i], mc_walk[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		get_img(&mlx_vars, &mlx_vars.victory[i], victory_an[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		get_img(&mlx_vars, &mlx_vars.patrol.img[i], patrol_an[i]);
		i++;
	}
	mlx_vars.width *= mlx_vars.terrain.width;
	mlx_vars.height *= mlx_vars.terrain.height;
	mlx_vars.win = mlx_new_window(mlx_vars.mlx, mlx_vars.width, mlx_vars.height, "Gioco da GAMING!");
	if (mlx_vars.win == NULL)
	{
		free(mlx_vars.win);
		return (1);
	}
	mlx_vars.mc.flip = 0;
	get_player(mlx_vars.map, &mlx_vars.mc.x, &mlx_vars.mc.y);
	put_enemies(&mlx_vars);
	mlx_hook(mlx_vars.win, 3, 1L<<1, key_press_up, &mlx_vars);
	mlx_hook(mlx_vars.win, 17, 0, ft_close, &mlx_vars);
	mlx_loop_hook(mlx_vars.mlx, render_next_frame, &mlx_vars);
	mlx_loop(mlx_vars.mlx);
	ft_close(&mlx_vars);
}