/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/01/23 19:11:01 by valentin         ###   ########.fr       */
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

t_f128			pix_to_cplex_x(t_area *area, t_u32 x)
{
	return (area->x1 + (t_f128)x / area->zoom[0]);
}

t_f128			pix_to_cplex_y(t_area *area, t_u32 y)
{
	return (area->y1 + ((t_f128)y * ((t_f128)HEIGHT / (t_f128)WIDTH))
		/ area->zoom[1]);
}

void			zoom(t_env *env, int zoom, t_u32 x, t_u32 y)
{
	t_f128	pos_x;
	t_f128	pos_y;

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
	/*printf("%.21Lf, %.21Lf, %.21Lf, %.21Lf\n", env->area.x1, env->area.y1,
		env->area.x2, env->area.y2);*/
	env->area.zoom[0] = (t_f128)WIDTH / (env->area.x2 - env->area.x1);
	env->area.zoom[1] = ((t_f128)HEIGHT / (env->area.y2 - env->area.y1)
		* ((t_f128)HEIGHT / (t_f128)WIDTH));
}

/*
** Classic opti
*/

static t_u32	mandel(t_u32 max, t_cplex_v c)
{
	t_cplex_v	z;
	t_cplex_v	t;
	t_f128		p;
	t_u32		iter;

	z = (t_cplex_v){0., 0.};
	t = z;
	iter = 0;
	while (1)
	{
		t = z * z;
		if (t[0] + t[1] >= 4. || iter++ == max)
			break ;
		p = z[1] * z[0];
		z[0] = t[0] - t[1] + c[0];
		z[1] = p + p + c[1];
	}
	return (iter - 1);
}

/* Periodic check (slower)*
static t_u32	mandel(t_u32 max, t_cplex_v c)
{
	t_cplex_v	z;
	t_cplex_v	t;
	t_cplex_v	z_p;
	t_f128		p;
	t_u32		iter;
	t_u32		iter_add;

	z = (t_cplex_v){0., 0.};
	t = z;
	iter = 0;
	iter_add = 4;
	while (iter_add != max)
	{
		iter_add += iter_add;
		if (iter_add > max)
			iter_add = max;
		while (iter++ < iter_add)
		{
			t = z * z;
			if (t[0] + t[1] >= 4.)
				return (iter);
			p = z[1] * z[0];
			z_p[0] = t[0] - t[1] + c[0];
			z_p[1] = p + p + c[1];
			if (z_p[0] == z[0] && z_p[1] == z[1])
				return (max);
			z = z_p;
		}
	}
	return (iter - 1);
}
*/

static int		draw_mandel(void *data)
{
	t_u32		iter;
	t_u32		col;
	t_u32		row;
	t_cplex_v	c;
	t_algo		*algo;
	t_area		*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	row = algo->start;
	while (row++ < algo->end)
	{
		col = 0;
		c[1] = pix_to_cplex_y(area, row);
		while (col++ < area->size[0])
		{
			c[0] = pix_to_cplex_x(area, col);
			iter = mandel(area->max, c);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[row * WIDTH + col]
					= algo->data->env.cs[iter % 64];
		}
	}
	return (SUCCESS);
}
/*
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
*/

static int		draw_mandel_perturbed(t_data *data)
{
	t_cplex_v	z;
	t_cplex_v	a;
	t_cplex_v	b;
	t_cplex_v	c;
	t_cplex_v	d;
	t_f128		d0;
	t_f128		yn;
}

void			draw_img(t_data *data)
{
	t_algo	pack[512];
	int		n_div;
	int		n_mod;
	int		i;
	int		tasks;

	i = 0;
	tasks = TASKS/*data->env.area.size[1] / 8*/;
	n_div = data->env.area.size[1] / tasks;
	n_mod = data->env.area.size[1] % tasks;
	while (i < tasks)
	{
		pack[i].data = data;
		pack[i].start = i * n_div;
		pack[i].end = i < tasks - 1 ? n_div : n_div + n_mod;
		pack[i].end += pack[i].start;
		if (data->env.fractal == FRACTAL_MANDEL)
			tp_add_task(data->env.tp, &draw_mandel, &pack[i]);
		/*else if (data->env.fractal == FRACTAL_JULIA)
			tp_add_task(data->env.tp, &draw_julia, &pack[i]);*/
		i++;
	}
	tp_wait_for_queue(data->env.tp);
}
