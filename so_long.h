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
# include <math.h>
# include "mlx_linux/mlx.h"
# include "libft/libft.h"

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		width;
	int		height;
}				t_img;

typedef struct s_obj {
	int		x;
	int		y;
	int		flip;
	t_img	img[8];
}				t_obj;

typedef struct s_mlxs {
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

typedef struct s_path {
	int	gcost;
	int	hcost;
	int	prev_i;
	int	prev_j;
	int	passed;
}				t_path;

typedef struct s_cords {
	int	i;
	int	j;
	int	x;
	int	y;
}				t_cords;

char	**get_map(char *map_file, t_mlxs *vars);
int		map_check(char **map, char *set, t_mlxs *vars);
int		count_zeros(char **map);
int		count_free_space(char **map);
void	collect_collectible(t_mlxs *vars, int x, int y);
void	escape_game(t_mlxs *vars, int x, int y);
void	player_funeral(t_mlxs *vars, int x, int y);
void	move_left(t_mlxs *vars, int x, int y);
void	move_right(t_mlxs *vars, int x, int y);
void	move_up(t_mlxs *vars, int x, int y);
void	move_down(t_mlxs *vars, int x, int y);
void	ft_put_image_to_window(t_mlxs *vars, t_img img, int x, int y);
void	load_map(t_mlxs *vars, char **map, int i, int j);
void	load_characters(t_mlxs *vars, int frame, int i, int j);
void	victory_animation(t_mlxs *vars, int i, int j);
int		render_next_frame(t_mlxs *vars);
void	get_player(char **map, int *px, int *py);
int		count_collectibles(char **map);
char	**dup_map(char **map);
void	free_map(void **map);
int		is_exit_here(char **map, int x, int y);
int		is_path_real(char **map);
int		keyboard_event(char cell, int x, int y, t_mlxs *vars);
void	get_enemy_position(char **map, int *ex, int *ey);
void	set_get_lowest_cost_vars(int *min_fcost, int *min);
int		is_lowest_cost(t_path **map_cost, int *min, int *x, int *y);
t_path	**init_map_cost(char **map, t_mlxs *vars);
int		get_mod_cords(int *n, int *mod);
int		do_the_random_move(char **map, int n, int x, int y);
void	random_move(char **map, int x, int y);
int		get_hcost(char **map, int x, int y);
int		get_gcost(int x, int y, int i, int j);
int		min_cost(t_path cell_cost, t_path min_cell, int *min_fcost);
int		get_lowest_cost(char **map, t_path **map_cost, int *x, int *y);
void	enemy_pathfinding(t_mlxs *vars, char **map, int x, int y);
void	enemy_manager(t_mlxs *vars);
void	ft_destroy_images(t_mlxs *vars);
void	put_enemies(t_mlxs *vars);
void	get_img(t_mlxs *v, t_img *img, char *path);
void	get_paths(char **sprites);
void	load_sprites(t_mlxs *vars, char **sprites, int i, int j);
int		ft_close(t_mlxs *vars);
int		key_press_up(int keycode, t_mlxs *vars);
int		button_press_down(int mbcode, t_mlxs *vars);
void	render_map(t_mlxs *vars);
void	ft_mlx_pixel_put(t_img *data, int x, int y, int color);
void	*free_unfinished_map(void **map, int i);

#endif
