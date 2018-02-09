/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 09:53:02 by vparis            #+#    #+#             */
/*   Updated: 2018/02/09 12:44:50 by vparis           ###   ########.fr       */
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

static void	manage_key_up2(int keycode, t_env *env)
{
	if (keycode == K_1)
	{
		env->refresh = 1;
		init_color(env->cs);
	}
	else if (keycode == K_2)
	{
		env->refresh = 1;
		init_color_r(env->cs);
	}
}
int			manage_key_up(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->env.keydown = -1;
	if (keycode == K_F)
		data->env.show_fps = !data->env.show_fps;
	else if (keycode == K_S)
		data->env.save_img = 1;
	else if (keycode == K_I)
	{
		if (data->env.fractal == FRACTAL_MANDEL)
			mandel_init(&(data->env.area));
		else if (data->env.fractal == FRACTAL_JULIA)
			julia_init(&(data->env.area));
		else if (data->env.fractal == FRACTAL_BURN)
			burn_init(&(data->env.area));
		data->env.refresh = 1;
	}
	else
		manage_key_up2(keycode, &(data->env));
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
