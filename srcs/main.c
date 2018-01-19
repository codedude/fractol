/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/01/19 17:55:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "ft_mlx.h"
#include "fractol.h"
#include "ft_complex.h"

static int	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	clean_maps(data);
	check_key(&(data->env));
	draw_img(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win[MAIN_WIN].win,
		data->mlx.win[MAIN_WIN].img__, 0, 0);
	ft_mlx_fps(data->env.show_fps);
	return (1);
}

static void	set_hook(t_data *data)
{
	mlx_hook(data->mlx.win[MAIN_WIN].win, E_KEY_UP, 0,
		&manage_key_up, (void *)data);
	mlx_hook(data->mlx.win[MAIN_WIN].win, E_KEY_DOWN, 0,
		&manage_key_down, (void *)data);
	mlx_hook(data->mlx.win[MAIN_WIN].win, E_MOUSE_DOWN, 0,
		&manage_mouse, (void *)data);
	mlx_loop_hook(data->mlx.mlx, &loop, (void *)data);
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		fractal;
/*
	char	buff[3];
	fgets(buff, 2, stdin);
*/

	/*t_cplex_v	z;
	t_cplex_v	t;
	z = (t_cplex_v){1., 2.};
	t = (t_cplex_v)z * z;
	printf("%lf, %lf\n", z[0], z[1]);
	return (0);*/
	if (argc != 2)
	{
		ft_putstr("fractol : ./fractol FRACTAL\n");
		return (EXIT_SUCCESS);
	}
	fractal = ft_atoi(argv[1]);
	if (fractal < 1 || fractal > 3)
	{
		ft_putstr("fractal number between 1 and 3\n");
		return (EXIT_SUCCESS);
	}
	if (env_init(&(data.env), fractal, WIDTH, HEIGHT) == ERROR)
		return (EXIT_FAILURE);
	ft_mlx_init(&(data.mlx));
	if (ft_mlx_win(&(data.mlx), data.env.width, data.env.height, TITLE)
		== ERROR)
		exit(EXIT_FAILURE);
	set_hook(&data);
	mlx_loop(&(data.mlx));
	return (EXIT_SUCCESS);
}
