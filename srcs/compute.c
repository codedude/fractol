/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 14:47:10 by vparis            #+#    #+#             */
/*   Updated: 2018/01/31 17:42:11 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

void			clean_maps(t_data *data)
{
	int		*tmp;
	size_t	i;

	tmp = (t_color *)data->mlx.win[MAIN_WIN].img;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		tmp[i] = 0;
		i++;
	}
}

void			zoom(t_env *env, int zoom, int x, int y)
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
