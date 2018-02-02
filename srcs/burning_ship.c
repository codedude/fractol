/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:39:33 by valentin          #+#    #+#             */
/*   Updated: 2018/02/02 18:26:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"
#include "ft_mlx.h"
#include "ft_complex.h"

static t_u32	burn(t_u32 max, t_cplex_v c)
{
	t_cplex_v	z;
	t_cplex_v	t;
	t_f128		p;
	t_u32		iter;

	z = (t_cplex_v){0., 0.};
	t = z;
	iter = 0;
	while (1)
	{
		t = z * z;
		if (t[0] + t[1] >= 4. || iter++ == max)
			break ;
		p = z[1] * z[0];
		if (p < 0)
			p = -p;
		z[0] = t[0] - t[1] + c[0];
		z[1] = p + p + c[1];
	}
	return (iter - 1);
}

int				draw_burn(void *data)
{
	t_u32		iter;
	t_u32		pos[2];
	t_cplex_v	c;
	t_algo		*algo;
	t_area		*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	pos[1] = algo->start;
	while (pos[1]++ < algo->end)
	{
		pos[0] = 0;
		c[1] = pix_to_cplex_y(area, pos[1] - 1);
		while (pos[0]++ < area->size[0])
		{
			c[0] = pix_to_cplex_x(area, pos[0] - 1);
			iter = burn(area->max, c);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[
					(pos[1] - 1) * WIDTH + pos[0] - 1] = algo->data->env.cs[iter
					% 16];
		}
	}
	return (SUCCESS);
}
