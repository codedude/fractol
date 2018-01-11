/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 16:37:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "fractol.h"
#include "ft_mlx.h"
#include "ft_math.h"

void			clean_maps(t_data *data)
{
	ft_bzero((void *)data->mlx.win[MAIN_WIN].img, 4 * WIDTH * HEIGHT);
}

void			init_color(t_color cs[200], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		cs[i] = ft_mlx_getcolor(10 + i * 3, 10 + i * 3, 10 - i * 3);
		i++;
	}
}

void			draw_img(t_data *data)
{
	int		row;
	int		col;
	int		iter;
	int		max;
	double	c_re;
	double	c_im;
	double	x;
	double	y;
	double	x_new;
	t_color	*tmp;
	t_color	cs[64];

	init_color(cs, 64);
	max = 64;
	row = 0;
	while (row < HEIGHT)
	{
		col = 0;
		while (col < WIDTH)
		{
			c_re = (col - WIDTH / 2.) * 4. / WIDTH;
			c_im = (row - HEIGHT / 2.) * 4. / WIDTH;
			x = 0;
			y = 0;
			iter = 0;
			while (x*x+y*y <= 4 && iter < max) {
				x_new = x*x - y*y + c_re;
				y = 2*x*y + c_im;
				x = x_new;
				iter++;
			}
			if (iter < max)
			{
				tmp = (t_color *)(data->mlx.win[MAIN_WIN].img
					+ (row * (WIDTH * 4) + col * 4));
				*tmp = cs[iter];
			}
			col++;
		}
		row++;
	}
}
