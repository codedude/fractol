/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 18:26:03 by vparis            #+#    #+#             */
/*   Updated: 2018/02/05 11:00:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "fractol.h"

void		check_key2(t_env *env)
{
	t_f128	size;

	if (env->keydown == K_RIGHT || env->keydown == K_LEFT)
	{
		size = MOVE * (env->area.x2 - env->area.x1);
		if (env->keydown == K_LEFT)
			size = -size;
		env->area.x1 += size;
		env->area.x2 += size;
	}
	else if (env->keydown == K_UP || env->keydown == K_DOWN)
	{
		size = MOVE * (env->area.y2 - env->area.y1);
		if (env->keydown == K_UP)
			size = -size;
		env->area.y1 += size;
		env->area.y2 += size;
	}
	else
		env->refresh = (env->refresh == 2) ? 1 : 0;
	if (env->keydown == K_S)
		env->save_img = 1;
}

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
		check_key2(env);
	if (env->refresh == 1 && env->show_fps == 1)
	{
		ft_putstr("MAX : ");
		ft_putnbr((int)env->area.max);
		ft_putchar('\n');
	}
}
