/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 09:53:02 by vparis            #+#    #+#             */
/*   Updated: 2018/02/06 23:46:11 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "fractol.h"

int			manage_key_down(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->env.keydown = keycode;
	if (keycode == K_ESC)
		env_destroy(data);
	return (1);
}

int			manage_key_up(int keycode, void *param)
{
	t_data	*data;

	(void)keycode;
	data = (t_data *)param;
	data->env.keydown = -1;
	if (keycode == K_F)
		data->env.show_fps = !data->env.show_fps;
	if (keycode == K_S)
		data->env.save_img = 1;
	if (keycode == K_I)
	{
		if (data->env.fractal == FRACTAL_MANDEL)
			mandel_init(&(data->env.area));
		else if (data->env.fractal == FRACTAL_JULIA)
			julia_init(&(data->env.area));
		else if (data->env.fractal == FRACTAL_BURN)
			burn_init(&(data->env.area));
		data->env.refresh = 1;
	}
	return (1);
}

int			manage_mouse(int keycode, int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == M_DOWN)
		zoom(&(data->env), 1, x, y);
	else if (keycode == M_UP)
		zoom(&(data->env), -1, x, y);
	data->env.refresh = 1;
	return (1);
}

int			manage_mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->env.fractal != FRACTAL_JULIA || data->env.mmove[0] == 0)
		return (0);
	data->env.mmove[1] = x;
	data->env.mmove[2] = y;
	data->env.refresh = 1;
	return (1);
}
