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
# include "mlx_linux/mlx.h"
# include "libft/libft.h"

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct	s_obj {
	int		x;
	int		y;
	int		width[8];
	int		height[8];
	int		color[8];
	t_img	img[8];
}				t_obj;

typedef struct	s_mlxs {
	void	*mlx;
	void	*win;
	t_img	img;
	t_obj	mc;
	t_obj	enemy;
	int		frame;
}				t_mlxs;

int		create_trgb(int t, int r, int g, int b);
int		get_t(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);
int		add_shade(double distance, int color);
int		add_tint(double distance, int color);
int		get_opposite(int color);
int		key_press_down(int keycode, t_mlxs *vars);
int		button_press_down(int mbcode, t_mlxs *vars);
int		ft_close(t_mlxs *vars);
void	ft_mlx_pixel_put(t_img *data, int x, int y, int color);
int		render_next_frame(t_mlxs *vars);

#endif
