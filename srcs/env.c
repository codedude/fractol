/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 00:26:13 by vparis            #+#    #+#             */
/*   Updated: 2018/02/02 18:26:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "ft_mlx.h"
#include "fractol.h"
#include "ft_tpool.h"

void	color_rot(t_color cs[16])
{
	t_color	tmp;
	int		i;

	i = 0;
	tmp = cs[0];
	while (i < 15)
	{
		cs[i] = cs[i + 1];
		i++;
	}
	cs[i] = tmp;
}

void	init_color(t_color cs[16])
{
	cs[0] = ft_mlx_getcolor(66, 30, 15);
	cs[1] = ft_mlx_getcolor(25, 7, 26);
	cs[2] = ft_mlx_getcolor(9, 1, 47);
	cs[3] = ft_mlx_getcolor(4, 4, 73);
	cs[4] = ft_mlx_getcolor(0, 7, 100);
	cs[5] = ft_mlx_getcolor(12, 44, 138);
	cs[6] = ft_mlx_getcolor(24, 82, 177);
	cs[7] = ft_mlx_getcolor(57, 125, 209);
	cs[8] = ft_mlx_getcolor(134, 181, 229);
	cs[9] = ft_mlx_getcolor(211, 236, 248);
	cs[10] = ft_mlx_getcolor(241, 233, 191);
	cs[11] = ft_mlx_getcolor(248, 201, 95);
	cs[12] = ft_mlx_getcolor(255, 170, 0);
	cs[13] = ft_mlx_getcolor(204, 128, 0);
	cs[14] = ft_mlx_getcolor(153, 87, 0);
	cs[15] = ft_mlx_getcolor(106, 52, 3);
}

int		env_init(t_env *env, int fractal, int width, int height)
{
	if ((env->tp = tp_create(THREADS, TP_ON_START)) == NULL)
		return (ERROR);
	env->keydown = -1;
	env->refresh = 1;
	env->show_fps = 0;
	env->mmove[0] = 0;
	env->mmove[1] = WIDTH / 2;
	env->mmove[2] = HEIGHT / 2;
	env->fractal = fractal;
	env->width = width;
	env->height = height;
	init_color(env->cs);
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
