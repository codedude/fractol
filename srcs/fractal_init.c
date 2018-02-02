/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:30:54 by valentin          #+#    #+#             */
/*   Updated: 2018/02/02 18:26:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"
#include "ft_tpool.h"

void	mandel_init(t_area *area)
{
	area->max = 128;
	area->x1 = -2;
	area->y1 = -2;
	area->x2 = 2;
	area->y2 = 2;
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}

void	julia_init(t_area *area)
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

void	burn_init(t_area *area)
{
	area->max = 128;
	area->x1 = -2;
	area->y1 = -2;
	area->x2 = 2;
	area->y2 = 2;
	area->zoom[0] = (t_f128)WIDTH / (area->x2 - area->x1);
	area->zoom[1] = (t_f128)HEIGHT / (area->y2 - area->y1);
	area->size[0] = WIDTH;
	area->size[1] = HEIGHT;
}
