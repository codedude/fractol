/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 00:26:13 by vparis            #+#    #+#             */
/*   Updated: 2018/01/30 23:16:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "fractol.h"
#include "ft_tpool.h"

void	init_color(t_color cs1[255], t_color cs2[255])
{
	int	i;

	i = 0;
	while (i < 255)
	{
		cs1[i] = ft_mlx_getcolor(15, i, 15);
		cs2[i] = ft_mlx_getcolor(i, 240, i);
		i++;
	}
}

void	mandel_init(t_area *area)
{
	area->max = 1024;
	area->x1 = -2;
	area->y1 = -2;
	area->x2 = 2;
	area->y2 = 2;
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

void	julia_init(t_area *area)
{
	area->max = 64;
	area->x1 = -1.5;
	area->y1 = -1.5;
	area->x2 = 1.5;
	area->y2 = 1.5;
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

void	burn_init(t_area *area)
{
	area->max = 512;
	area->x1 = -2;
	area->y1 = -2;
	area->x2 = 2;
	area->y2 = 2;
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

int		env_init(t_env *env, int fractal, int width, int height)
{
	if ((env->tp = tp_create(THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	env->keydown = -1;
	env->refresh = 1;
	env->show_fps = 0;
	env->mmove[0] = 0;
	env->mmove[1] = 400;
	env->mmove[2] = 400;
	env->fractal = fractal;
	env->width = width;
	env->height = height;
	init_color(env->cs1, env->cs2);
	if (fractal == FRACTAL_MANDEL)
		mandel_init(&(env->area));
	else if (fractal == FRACTAL_JULIA)
		julia_init(&(env->area));
	else if (fractal == FRACTAL_BURN)
		burn_init(&(env->area));
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
