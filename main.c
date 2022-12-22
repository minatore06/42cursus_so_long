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

static void	get_error(int err_code, char **map)
{
	if (!err_code)
		return ;
	free_map((void **)map);
	ft_printf("Error\n");
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
		ft_printf("Mappa impossibile, non e' possibile raggiungere la fine");
	exit (0);
}

static void	init_vars(t_mlxs *vars)
{
	vars->c_collectible = count_collectibles(vars->map);
	vars->frame = 0;
	vars->movements = 0;
	vars->end = 0;
	vars->mlx = mlx_init();
	vars->mc.flip = 0;
}

static void	game_loop(t_mlxs *vars)
{
	mlx_hook(vars->win, 3, 1L << 1, key_press_up, vars);
	mlx_hook(vars->win, 17, 0, ft_close, vars);
	mlx_loop_hook(vars->mlx, render_next_frame, vars);
	mlx_loop(vars->mlx);
	ft_close(vars);
}

int	main(int argc, char *argv[])
{
	t_mlxs	vars;
	char	*sprites[23];

	if (argc != 2)
		return (0);
	vars.map = get_map(argv[1], &vars);
	get_error(map_check(vars.map, "01CEP", &vars), vars.map);
	init_vars(&vars);
	if (vars.mlx == NULL)
	{
		free_map((void **)vars.map);
		return (1);
	}
	get_paths(sprites);
	load_sprites(&vars, sprites, 0, 0);
	vars.win = mlx_new_window(vars.mlx, vars.width, vars.height, "GAMING!");
	if (vars.win == NULL)
		ft_close(&vars);
	get_player(vars.map, &vars.mc.x, &vars.mc.y);
	put_enemies(&vars);
	game_loop(&vars);
}
