/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 00:26:13 by vparis            #+#    #+#             */
/*   Updated: 2018/01/15 17:10:19 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "fractol.h"
#include "ft_tpool.h"

void	mandel_init(t_area *area)
{
	int	w_min[2];

	area->max = 128;
	area->x1 = -2.1;
	area->y1 = -1.2;
	area->x2 = 0.6;
	area->y2 = 1.2;
	w_min[0] = WIDTH / (area->x2 - area->x1);
	w_min[1] = HEIGHT / (area->y2 - area->y1);
	area->zoom = ft_min(w_min[0], w_min[1]);
	area->size[0] = (area->x2 - area->x1) * area->zoom;
	area->size[1] = (area->y2 - area->y1) * area->zoom;
}

void	julia_init(t_area *area)
{
	int	w_min[2];

	area->max = 128;
	area->x1 = -1;
	area->y1 = -1.2;
	area->x2 = 1;
	area->y2 = 1.2;
	w_min[0] = WIDTH / (area->x2 - area->x1);
	w_min[1] = HEIGHT / (area->y2 - area->y1);
	area->zoom = ft_min(w_min[0], w_min[1]);
	area->size[0] = (area->x2 - area->x1) * area->zoom;
	area->size[1] = (area->y2 - area->y1) * area->zoom;
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
