/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/08 09:53:02 by vparis            #+#    #+#             */
/*   Updated: 2018/01/31 17:25:55 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "fractol.h"

void		check_key(t_env *env)
{
	env->refresh += 1;
	if (env->keydown == K_T)
		env->area.max += 5;
	else if (env->keydown == K_G)
	{
		if (env->area.max > 5)
			env->area.max -= 5;
	}
	else if (env->keydown == K_Y)
		env->area.max += 30;
	else if (env->keydown == K_H)
	{
		if (env->area.max > 30)
			env->area.max -= 30;
	}
	else if (env->keydown == K_R)
		color_rot(env->cs);
	else
		env->refresh = (env->refresh == 2) ? 1 : 0;
	if (env->refresh == 1)
	{
		ft_putstr("MAX : ");
		ft_putnbr((int)env->area.max);
		ft_putchar('\n');
	}
}

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
