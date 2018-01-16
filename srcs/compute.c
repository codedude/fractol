/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/01/16 16:17:48 by vparis           ###   ########.fr       */
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

t_f64			pix_to_cplex_x(t_area *area, int x)
{
	return (area->x1 + (t_f64)x / area->zoom[0]);
}

t_f64			pix_to_cplex_y(t_area *area, int y)
{
	return (area->y1 + ((t_f64)y * ((t_f64)HEIGHT / (t_f64)WIDTH))
		/ area->zoom[1]);
}

void			zoom(t_env *env, int zoom, int x, int y)
{
	t_f64	pos_x;
	t_f64	pos_y;

	pos_x = pix_to_cplex_x(&(env->area), x);
	pos_y = pix_to_cplex_y(&(env->area), y);
	/*printf("Clic(%d, %d) => %lf, %lf\n", x, y, pos_x, pos_y);*/
	if (zoom == 1)
	{
		env->area.x1 = pos_x - ZOOM * (env->area.x2 - env->area.x1);
		env->area.x2 = pos_x + ZOOM * (env->area.x2 - env->area.x1);
		env->area.y1 = pos_y - ZOOM * (env->area.y2 - env->area.y1);
		env->area.y2 = pos_y + ZOOM * (env->area.y2 - env->area.y1);
	}
	else
	{
		env->area.x1 = pos_x - (1. + ZOOM) * (env->area.x2 - env->area.x1);
		env->area.x2 = pos_x + (1. + ZOOM) * (env->area.x2 - env->area.x1);
		env->area.y1 = pos_y - (1. + ZOOM) * (env->area.y2 - env->area.y1);
		env->area.y2 = pos_y + (1. + ZOOM) * (env->area.y2 - env->area.y1);
	}
	env->area.zoom[0] = (t_f64)WIDTH / (env->area.x2 - env->area.x1);
	env->area.zoom[1] = ((t_f64)HEIGHT / (env->area.y2 - env->area.y1)
		* ((t_f64)HEIGHT / (t_f64)WIDTH)) ;
}

static void		mandel(int max, int *iter, t_cplex *c)
{
	t_cplex	z;
	double	zr;

	ft_cplex_set(&z, 0., 0.);
	*iter = 0;
	while (ft_cplex_mod_f(z.r, z.i) < 4. && *iter < max)
	{
		zr = z.r;
		z.r = z.r * z.r - z.i * z.i + c->r;
		z.i = 2. * z.i * zr + c->i;
		(*iter)++;
	}
}

static int		draw_mandel(void *data)
{
	int		iter;
	int		col;
	int		row;
	t_f64	py;
	t_cplex	c;
	t_algo	*algo;
	t_area	*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	row = algo->start;
	while (row < algo->end)
	{
		col = 0;
		py = pix_to_cplex_y(area, row);
		while (col < area->size[0])
		{
			ft_cplex_set(&c, pix_to_cplex_x(area, col), py);
			mandel(area->max, &iter, &c);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[row * WIDTH + col]
					= algo->data->env.cs[iter % 64];
			col++;
		}
		row++;
	}
	return (SUCCESS);
}

static void		julia(int max, int *iter, t_cplex *c, t_cplex *z)
{
	double	zr;

	*iter = 0;
	while (ft_cplex_mod_f(z->r, z->i) < 4. && *iter < max)
	{
		zr = z->r;
		z->r = z->r * z->r - z->i * z->i + c->r;
		z->i = 2. * z->i * zr + c->i;
		(*iter)++;
	}
}

static int		draw_julia(void *data)
{
	int		iter;
	int		col;
	int		row;
	double	py;
	t_cplex	c;
	t_cplex	z;
	t_algo	*algo;
	t_area	*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	row = algo->start;
	ft_cplex_set(&c, 0.285, 0.01);
	while (row < algo->end)
	{
		col = 0;
		py = pix_to_cplex_y(area, row);
		while (col < area->size[0])
		{
			ft_cplex_set(&z, pix_to_cplex_x(area, col), py);
			julia(area->max, &iter, &c, &z);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[row * WIDTH + col]
					= algo->data->env.cs[iter % 64];
			col++;
		}
		row++;
	}
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
