/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:48:34 by vparis            #+#    #+#             */
/*   Updated: 2018/01/08 10:04:35 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_mlx.h"

t_color	ft_mlx_getcolor(int r, int g, int b)
{
	t_color		c;

	c = 0;
	c |= (b & 0xFF);
	c |= (g & 0xFF) << 8;
	c |= (r & 0xFF) << 16;
	return (c);
}

void	ft_mlx_pixel(t_mlx *mlx, int win, t_pixel *pix)
{
	mlx_pixel_put(mlx->mlx, mlx->win[win].win, pix->x, pix->y, pix->c);
}

void	ft_mlx_string(t_mlx *mlx, int win, t_pixel *pix, char *str)
{
	mlx_string_put(mlx->mlx, mlx->win[win].win, pix->x, pix->y, pix->c, str);
}

void	ft_mlx_clear(t_mlx *mlx, int win)
{
	mlx_clear_window(mlx->mlx, mlx->win[win].win);
}
