/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:52:32 by vparis            #+#    #+#             */
/*   Updated: 2018/02/09 11:30:35 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "ft_mlx.h"
#include "fractol.h"

static int	loop(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	check_key(&(data->env));
	data->env.mmove[0] = 0;
	if (data->env.refresh == 1)
	{
		clean_maps(data);
		draw_img(data);
		mlx_put_image_to_window(data->mlx.mlx, data->mlx.win[MAIN_WIN].win,
			data->mlx.win[MAIN_WIN].img__, 0, 0);
	}
	if (save_img(data) == ERROR)
		ft_putstr("Image can't be save\n");
	ft_mlx_fps(data->env.show_fps, data->env.refresh);
	data->env.refresh = 0;
	data->env.mmove[0] = 1;
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
	mlx_hook(data->mlx.win[MAIN_WIN].win, E_MOUSE_MOVE, 0,
		&manage_mouse_move, (void *)data);
	mlx_loop_hook(data->mlx.mlx, &loop, (void *)data);
}

int			main(int argc, char **argv)
{
	t_data	data;
	int		fractal;

	if (argc != 2)
	{
		ft_putstr("fractol : ./fractol FRACTAL\n");
		ft_putstr("FRACTAL : 1 = Mandelbrot, 2 = Julia, 3 = Burning Ship\n");
		return (EXIT_SUCCESS);
	}
	fractal = ft_atoi(argv[1]);
	if (fractal < 1 || fractal > 3)
	{
		ft_putstr("FRACTAL : 1 = Mandelbrot, 2 = Julia, 3 = Burning Ship\n");
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
