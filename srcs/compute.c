/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/01/15 17:12:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "libft.h"
#include "fractol.h"
#include "ft_mlx.h"
#include "ft_math.h"
#include "ft_complex.h"

void			clean_maps(t_data *data)
{
	ft_bzero((void *)data->mlx.win[MAIN_WIN].img, 4 * WIDTH * HEIGHT);
}

void			init_color(t_color cs[64], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		cs[i] = ft_mlx_getcolor(10 + i * 3, 10 + i * 3, 10 - i * 3);
		i++;
	}
}

static int		draw_mandel(void *data)
{
	int		iter;
	int		col;
	int		row;
	double	py;
	t_cplex	z;
	t_cplex	c;
	double	zr;
	t_algo	*algo;
	t_area	*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	row = algo->start;
	while (row < algo->end)
	{
		col = 0;
		py = row / area->zoom + area->y1;
		while (col < area->size[0])
		{
			ft_cplex_set(&c, col / area->zoom + area->x1, py);
			ft_cplex_set(&z, 0., 0.);
			iter = 0;
			while (ft_cplex_mod_f(&z) < 4. && iter < area->max)
			{
				zr = z.r;
				ft_cplex_set(&z,
					z.r * z.r - z.i * z.i + c.r,
					2 * z.i * zr + c.i
				);
				iter++;
			}
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[row * WIDTH + col]
					= ft_mlx_getcolor(0, 0, iter * 255 / area->max);
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

static int		draw_julia(void *data)
{
	(void)data;
	return (SUCCESS);
}

void			draw_img(t_data *data)
{
	t_algo	pack[TASKS];
	int		n_div;
	int		n_mod;
	int		i;

	i = 0;
	n_div = data->env.area.size[1] / TASKS;
	n_mod = data->env.area.size[1] % TASKS;
	while (i < TASKS)
	{
		pack[i].data = data;
		pack[i].start = i * n_div;
		pack[i].end = i < TASKS - 1 ? n_div : n_div + n_mod;
		pack[i].end += pack[i].start;
		if (data->env.fractal == FRACTAL_MANDEL)
			tp_add_task(data->env.tp, &draw_mandel, &pack[i]);
		else if (data->env.fractal == FRACTAL_JULIA)
			tp_add_task(data->env.tp, &draw_julia, &pack[i]);
		i++;
	}
	tp_wait_for_queue(data->env.tp);
}
