/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaiazzo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 12:09:33 by scaiazzo          #+#    #+#             */
/*   Updated: 2022/12/01 12:09:34 by scaiazzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "so_long.h"

int	add_shade(double distance, int color)
{
	distance = 1 - distance;
	return (create_trgb(get_t(color), get_r(color) * distance, get_g(color) * distance, get_b(color) * distance));
}

int	add_tint(double distance, int color)
{
	return (create_trgb(get_t(color), (255 - get_r(color)) * distance, (255 - get_g(color)) * distance, (255 - get_b(color)) * distance));
}

int	get_opposite(int color)
{
	return (create_trgb(get_t(color), (255 - get_r(color)), (255 - get_g(color)), (255 - get_b(color))));
}