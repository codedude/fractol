/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/01/12 17:07:25 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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

static int		draw_fun(void *data)
{
	int		row;
	int		end;
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
	t_algo	*algo;
	t_data	*datas;

	algo = (t_algo *)data;
	datas = algo->data;
	init_color(cs, 64);
	max = 64;
	row = algo->start;
	end = row + algo->len;
	while (row < end)
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
				datas->mlx.win[MAIN_WIN].img[row * WIDTH + col] = cs[iter];
			}
			col++;
		}
		row++;
	}
	return (SUCCESS);
}
void			draw_img(t_data *data)
{
	t_algo	pack[16];
	int		n;
	int		i;

	n = HEIGHT / TASKS;
	i = 0;
	while (i < TASKS)
	{
		pack[i].data = data;
		pack[i].start = i * n;
		pack[i].len = i < TASKS - 1 ? n : n + HEIGHT % TASKS;
		tp_add_task(data->env.tp, &draw_fun, &pack[i]);
		i++;
	}
	tp_wait_for_queue(data->env.tp);
}
