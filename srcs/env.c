/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 00:26:13 by vparis            #+#    #+#             */
/*   Updated: 2018/01/19 17:48:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "fractol.h"
#include "ft_tpool.h"

void			init_color(t_color cs[64], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		cs[i] = ft_mlx_getcolor(10 + i * 3, 10 + i * 3, 250 - i * 3);
		i++;
	}
}

void	mandel_init(t_area *area)
{
	area->max = 512;

	area->x1 = -2.1;
	area->y1 = -1.2;
	area->x2 = 0.6;
	area->y2 = 1.2;
	/*
	area->x1 = -0.562186437092202240316;
	area->y1 = -0.642821004666185002877;
	area->x2 = -0.562186413453443144912;
	area->y2 = -0.642820963096796605665;
*/
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1)
					* ((t_f128)HEIGHT / (t_f128)WIDTH);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

void	julia_init(t_area *area)
{
	area->max = 75;
	area->x1 = -1.5;
	area->y1 = -1.5;
	area->x2 = 1.5;
	area->y2 = 1.5;
	area->zoom[0] = WIDTH / (area->x2 - area->x1);
	area->zoom[1] = HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

int		env_init(t_env *env, int fractal, int width, int height)
{
	if ((env->tp = tp_create(THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	env->keydown = -1;
	env->show_fps = 0;
	env->fractal = fractal;
	env->width = width;
	env->height = height;
	init_color(env->cs, 64);
	if (fractal == FRACTAL_MANDEL)
		mandel_init(&(env->area));
	else if (fractal == FRACTAL_JULIA)
		julia_init(&(env->area));
	return (SUCCESS);
}

void	env_destroy(t_data *data)
{
	int	i;

	tp_destroy(&(data->env.tp));
	i = 0;
	while (i < MLX_MAX_WINDOW)
	{
		ft_mlx_destroy(&(data->mlx), i);
		i++;
	}
	ft_mlx_exit();
}
