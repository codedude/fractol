/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:38:46 by valentin          #+#    #+#             */
/*   Updated: 2018/02/06 23:41:43 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"
#include "ft_mlx.h"
#include "ft_complex.h"

void			julia_init(t_area *area)
{
	area->max = 32;
	area->x1 = -2;
	area->y1 = -2;
	area->x2 = 2;
	area->y2 = 2;
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

static t_u32	julia(t_u32 max, t_cplex_v c, t_cplex_v z)
{
	t_cplex_v	t;
	t_f128		p;
	t_u32		iter;

	iter = 0;
	while (1)
	{
		t = z * z;
		if (t[0] + t[1] >= 4. || iter++ == max)
			break ;
		p = z[1] * z[0];
		z[0] = t[0] - t[1] + c[0];
		z[1] = p + p + c[1];
	}
	return (iter - 1);
}

int				draw_julia(void *data)
{
	t_u32		iter;
	t_u32		pos[2];
	t_cplex_v	cz[2];
	t_algo		*algo;
	t_area		*area;

	algo = (t_algo *)data;
	area = &(algo->data->env.area);
	pos[1] = algo->start;
	cz[0] = (t_cplex_v){pix_to_cplex_mdb_x(algo->data->env.mmove[1]),
		pix_to_cplex_mdb_y(algo->data->env.mmove[2])};
	while (pos[1]++ < algo->end)
	{
		pos[0] = 0;
		cz[1][1] = pix_to_cplex_y(area, pos[1] - 1);
		while (pos[0]++ < area->size[0])
		{
			cz[1][0] = pix_to_cplex_x(area, pos[0] - 1);
			iter = julia(area->max, cz[0], cz[1]);
			if (iter != area->max)
				algo->data->mlx.win[MAIN_WIN].img[(pos[1] - 1) * WIDTH + pos[0]
					- 1] = algo->data->env.cs[iter % 16];
		}
	}
	return (SUCCESS);
}
