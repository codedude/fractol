/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:34:05 by valentin          #+#    #+#             */
/*   Updated: 2018/01/31 17:43:27 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

t_f128			pix_to_cplex_x(t_area *area, int x)
{
	return (area->x1 + (t_f128)x / area->zoom[0]);
}

t_f128			pix_to_cplex_y(t_area *area, int y)
{
	return (area->y1 + (t_f128)y / area->zoom[1]);
}

t_f128			pix_to_cplex_mdb_x(int x)
{
	return (-2. + (t_f128)x / ((t_f128)WIDTH / 4.));
}

t_f128			pix_to_cplex_mdb_y(int y)
{
	return (-2. + (t_f128)y / ((t_f128)HEIGHT / 4.));
}
