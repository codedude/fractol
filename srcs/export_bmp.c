/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:01:14 by vparis            #+#    #+#             */
/*   Updated: 2018/02/05 12:18:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "mlx.h"
#include "ft_mlx.h"
#include "fractol.h"

static void	write_int(int fd, int n, int bytes)
{
	if (bytes == 4)
	{
		ft_putchar_fd((n & 0xFF000000) >> 24, fd);
		ft_putchar_fd((n & 0x00FF0000) >> 16, fd);
	}
	ft_putchar_fd((n & 0x00FF00) >> 8, fd);
	ft_putchar_fd((n & 0x000000FF), fd);
}

static int	write_header(int fd, int size[2])
{
	write_int(fd, 0x424D, 2);
	write_int(fd, size[0] * size[1] * sizeof(t_color) + 55, 4);
	write_int(fd, 0x00, 2);
	write_int(fd, 0x00, 2);
	write_int(fd, 0x37, 4);
	return (SUCCESS);
}

static int	write_dibheader(int fd, int size[2])
{
	write_int(fd, 0x28, 4);
	write_int(fd, size[1], 4);
	write_int(fd, size[0], 4);
	write_int(fd, 0x01, 2);
	write_int(fd, 0x20, 2);
	write_int(fd, 0x00, 4);
	write_int(fd, size[0] * size[1] * sizeof(t_color), 4);
	write_int(fd, size[0], 4);
	write_int(fd, size[1], 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x00, 4);
	ft_putchar_fd('\n', fd)
	return (SUCCESS);
}

int			save_img(t_data *data)
{
	int		size[2];
	t_color	*img;
	int		fd;

	size[0] = data->mlx.win[MAIN_WIN].height;
	size[1] = data->mlx.win[MAIN_WIN].width;
	img = data->mlx.win[MAIN_WIN].img;
	if ((fd = open(FILE_NAME, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		return (ERROR);
	write_header(fd, size);
	write_dibheader(fd, size);
	close(fd);
	data->env.save_img = 0;
	return (SUCCESS);
}
