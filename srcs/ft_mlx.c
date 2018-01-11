/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:43:44 by vparis            #+#    #+#             */
/*   Updated: 2018/01/08 11:01:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "mlx.h"
#include "ft_mlx.h"

int		ft_mlx_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	ft_mlx_init(t_mlx *mlx)
{
	if ((mlx->mlx = mlx_init()) == NULL)
		exit(EXIT_FAILURE);
	ft_bzero((void *)mlx->win, sizeof(t_win) * MLX_MAX_WINDOW);
}

int		ft_mlx_win(t_mlx *mlx, int width, int height, char *title)
{
	int	n;
	int	depth;
	int	size_line;
	int	endian;

	depth = sizeof(t_color) * 8;
	size_line = sizeof(t_color) * width;
	endian = 0;
	n = 0;
	while (n < MLX_MAX_WINDOW && mlx->win[n].win != NULL)
		n++;
	if (n == MLX_MAX_WINDOW)
		return (ERROR);
	if ((mlx->win[n].win = mlx_new_window(mlx->mlx, width, height, title))
		== NULL)
		return (ERROR);
	mlx->win[n].width = width;
	mlx->win[n].height = height;
	mlx->win[n].title = ft_strdup(title);
	mlx->win[n].img__ = mlx_new_image(mlx->mlx, width, height);
	mlx->win[n].img = mlx_get_data_addr(mlx->win[n].img__,
		&depth, &size_line, &endian);
	return (n);
}

void	ft_mlx_destroy(t_mlx *mlx, int win)
{
	mlx_destroy_window(mlx->mlx, mlx->win[win].win);
	mlx_destroy_image(mlx->mlx, mlx->win[win].img__);
	ft_strdel(&(mlx->win[win].title));
	ft_bzero((void *)&(mlx->win[win]), sizeof(t_win));
}
