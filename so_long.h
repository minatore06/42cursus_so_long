/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 17:57:15 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/11/30 17:57:20 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct	s_obj {
	int		x;
	int		y;
	int		flip;
	t_img	img[8];
}				t_obj;

typedef struct	s_mlxs {
	void	*mlx;
	void	*win;
	char	**map;
	t_img	terrain;
	t_img	border;
	t_img	wall;
	t_img	collectible;
	t_img	exit_open;
	t_img	exit_close;
	t_img	dead;
	t_img	victory[3];
	t_obj	mc;
	t_obj	enemy;
	t_obj	patrol;
	int		c_collectible;
	int		end;
	int		frame;
	int		movements;
	int		width;
	int		height;
}				t_mlxs;

typedef struct	s_path {
	int gcost;
	int	hcost;
	int	prev_i;
	int	prev_j;
	int	passed;
}				t_path;

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int color);
int		add_tint(double distance, int color);
int		get_opposite(int color);
int		key_press_up(int keycode, t_mlxs *vars);
int		button_press_down(int mbcode, t_mlxs *vars);
int		ft_close(t_mlxs *vars);
void	ft_mlx_pixel_put(t_img *data, int x, int y, int color);
int		render_next_frame(t_mlxs *vars);
void	render_map(t_mlxs *vars);
void    free_map(void **map);
int 	count_collectibles(char **map);
void    get_player(char **map, int *px, int *py);
int		is_path_real(char **map);
void    enemy_pathfinding(t_mlxs *vars);
void    get_enemy_position(char **map, int *ex, int *ey);

#endif
