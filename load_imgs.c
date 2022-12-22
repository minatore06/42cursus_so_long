/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:01:08 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/22 16:01:12 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

void	get_img(t_mlxs *v, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(v->mlx, path, &img->width, &img->height);
	if (!img->img)
	{
		ft_destroy_images(v);
		mlx_destroy_display(v->mlx);
		free(v->mlx);
		ft_printf("Error\nProblema col caricamento dell'immagine");
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->ll, &img->endian);
}

void	get_paths(char **sprites)
{
	sprites[0] = "./textures/capybara_idle_animation/idle1.xpm";
	sprites[1] = "./textures/capybara_idle_animation/idle2.xpm";
	sprites[2] = "./textures/capybara_idle_animation/idle3.xpm";
	sprites[3] = "./textures/capybara_idle_animation/idle4.xpm";
	sprites[4] = "./textures/capybara_idle_animation/idle5.xpm";
	sprites[5] = "./textures/capybara_idle_animation/idle6.xpm";
	sprites[6] = "./textures/capybara_idle_animation/idle7.xpm";
	sprites[7] = "./textures/capybara_idle_animation/idle8.xpm";
	sprites[8] = "./textures/mc_walk_animation/walk1.xpm";
	sprites[9] = "./textures/mc_walk_animation/walk2.xpm";
	sprites[10] = "./textures/mc_walk_animation/walk3.xpm";
	sprites[11] = "./textures/mc_walk_animation/walk4.xpm";
	sprites[12] = "./textures/mc_walk_animation/walk_flip1.xpm";
	sprites[13] = "./textures/mc_walk_animation/walk_flip2.xpm";
	sprites[14] = "./textures/mc_walk_animation/walk_flip3.xpm";
	sprites[15] = "./textures/mc_walk_animation/walk_flip4.xpm";
	sprites[16] = "./textures/map/victory1.xpm";
	sprites[17] = "./textures/map/victory2.xpm";
	sprites[18] = "./textures/map/victory3.xpm";
	sprites[19] = "./textures/patrol/enemy_patrol1.xpm";
	sprites[20] = "./textures/patrol/enemy_patrol2.xpm";
	sprites[21] = "./textures/patrol/enemy_patrol3.xpm";
	sprites[22] = "./textures/patrol/enemy_patrol_dead.xpm";
}

void	load_sprites(t_mlxs *vars, char **sprites, int i, int j)
{
	get_img(vars, &vars->terrain, "./textures/map/grass.xpm");
	get_img(vars, &vars->border, "./textures/map/water.xpm");
	get_img(vars, &vars->wall, "./textures/map/rock.xpm");
	get_img(vars, &vars->collectible, "./textures/map/crystal.xpm");
	get_img(vars, &vars->exit_close, "./textures/map/portal_clsd.xpm");
	get_img(vars, &vars->exit_open, "./textures/map/portal_open.xpm");
	get_img(vars, &vars->dead, "./textures/map/dead.xpm");
	i = 0;
	j = 0;
	while (i < 8)
		get_img(vars, &vars->enemy.img[j++], sprites[i++]);
	j = 0;
	while (i < 16)
		get_img(vars, &vars->mc.img[j++], sprites[i++]);
	j = 0;
	while (i < 19)
		get_img(vars, &vars->victory[j++], sprites[i++]);
	j = 0;
	while (i < 23)
		get_img(vars, &vars->patrol.img[j++], sprites[i++]);
	vars->width *= vars->terrain.width;
	vars->height *= vars->terrain.height;
}
