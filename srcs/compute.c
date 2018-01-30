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
	return (area->y1 + (t_f128)y / area->zoom[1]);
}

t_f128			pix_to_cplex_mdb_x(t_area *area, t_u32 x)
{
	return (-2. + (t_f128)x / ((t_f128)WIDTH / 4.));
}

t_f128			pix_to_cplex_mdb_y(t_area *area, t_u32 y)
{
	return (-2. + (t_f128)y / ((t_f128)HEIGHT / 4.));
}

void			zoom(t_env *env, int zoom, t_u32 x, t_u32 y)
{
	t_f128	pos_x;
	t_f128	pos_y;
	t_f128	delta;

	pos_x = pix_to_cplex_x(&(env->area), x);
	pos_y = pix_to_cplex_y(&(env->area), y);
	if (zoom == 1)
	{
		delta = ZOOM * (env->area.x2 - env->area.x1);
		env->area.x1 = pos_x - delta;
		env->area.x2 = pos_x + delta;
		env->area.y1 = pos_y - delta;
		env->area.y2 = pos_y + delta;
	}
	else
	{
		delta = (env->area.x2 - env->area.x1) / DEZOOM;
		env->area.x1 = pos_x - delta;
		env->area.x2 = pos_x + delta;
		env->area.y1 = pos_y - delta;
		env->area.y2 = pos_y + delta;
	}
	env->area.zoom[0] = (t_f128)WIDTH / (env->area.x2 - env->area.x1);
	env->area.zoom[1] = env->area.zoom[0];
}

/*
** Classic opti
*/

t_u32	mandel(t_u32 max, t_cplex_v c)
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

t_color	get_color(t_u32 iter, t_u32 max, t_env *env)
{
    int	c;

    c = (iter * 255) / max;
	if (iter < 128)
		return (env->cs1[c]);
	else
		return (env->cs2[c % 256]);
	/*
	if (iter & 0x01)
		return (C_BLACK);
	else
		return (C_WHITE);
	*/
	/*
	algo->data->env.cs[iter % 64]
	*/
}

int		draw_mandel(void *data)
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
		c[1] = pix_to_cplex_y(area, row - 1);
		while (col++ < area->size[0])
		{
			c[0] = pix_to_cplex_x(area, col - 1);
			iter = mandel(area->max, c);
			if (iter != area->max)
			{
				algo->data->mlx.win[MAIN_WIN].img[(row - 1) * WIDTH + col - 1]
					= get_color(iter, area->max, &(algo->data->env));
			}
		}
	}
	return (SUCCESS);
}
<<<<<<< HEAD
/*
static void		julia(int max, int *iter, t_cplex *c, t_cplex *z)
=======

static t_u32	julia(t_u32 max, t_cplex_v c, t_cplex_v z)
>>>>>>> 6b898c26e9dcb280d81f399aad9bbb20e6e417cd
{
	t_cplex_v	t;
	t_f128		p;
	t_u32		iter;

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

static int		draw_julia(void *data)
{
	t_u32		iter;
	t_u32		col;
	t_u32		row;
	t_cplex_v	c;
	t_cplex_v	z;
	t_algo		*algo;
	t_area		*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	row = algo->start;
	c = (t_cplex_v){pix_to_cplex_mdb_x(area, algo->data->env.mmove[1]),
		pix_to_cplex_mdb_y(area, algo->data->env.mmove[2])};
	while (row++ < algo->end)
	{
		col = 0;
		z[1] = pix_to_cplex_y(area, row - 1);
		while (col++ < area->size[0])
		{
			z[0] = pix_to_cplex_x(area, col - 1);
			iter = julia(area->max, c, z);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[(row - 1) * WIDTH + col - 1]
					= get_color(iter, area->max, &(algo->data->env));
		}
	}
	return (SUCCESS);
}

static t_u32	burn(t_u32 max, t_cplex_v c)
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
		if (p < 0)
			p = -p;
		z[0] = t[0] - t[1] + c[0];
		z[1] = p + p + c[1];
	}
	return (iter - 1);
}

static int		draw_burn(void *data)
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
		c[1] = pix_to_cplex_y(area, row - 1);
		while (col++ < area->size[0])
		{
			c[0] = pix_to_cplex_x(area, col - 1);
			iter = burn(area->max, c);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[(row - 1) * WIDTH + col - 1]
					= get_color(iter, area->max, &(algo->data->env));
		}
	}
	return (SUCCESS);
}

void			draw_img(t_data *data)
{
	t_algo	pack[TASKS];
	int		n_div;
	int		n_mod;
	int		i;
	int		tasks;

	i = 0;
	tasks = TASKS;
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
		else if (data->env.fractal == FRACTAL_JULIA)
			tp_add_task(data->env.tp, &draw_julia, &pack[i]);
		else if (data->env.fractal == FRACTAL_BURN)
			tp_add_task(data->env.tp, &draw_burn, &pack[i]);
		i++;
	}
	tp_wait_for_queue(data->env.tp);
}
