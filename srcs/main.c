/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 15:21:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "ft_mlx.h"
#include "fractol.h"

static int	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	compute_img(&(data->env));
	clean_maps(data);
	draw_img(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win[MAIN_WIN].win,
		data->mlx.win[MAIN_WIN].img__, 0, 0);
	return (1);
}

int			main(int argc, char **argv)
{
	t_data	data;
	char	buff[3];

	fgets(buff, 2, stdin);
	if (argc != 2)
	{
		ft_putstr("fdf : ./fdf MAP\n");
		return (EXIT_SUCCESS);
	}
	if (env_init(&(data.env), WIDTH, HEIGHT) == ERROR)
		return (EXIT_FAILURE);
	ft_mlx_init(&(data.mlx));
	if (ft_mlx_win(&(data.mlx), WIDTH, HEIGHT, TITLE) == ERROR)
		exit(EXIT_FAILURE);
	mlx_loop(&(data.mlx));
	return (EXIT_SUCCESS);
}
