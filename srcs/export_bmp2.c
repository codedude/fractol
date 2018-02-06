/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:44:22 by valentin          #+#    #+#             */
/*   Updated: 2018/02/06 13:51:50 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

static void	write_int(int fd, int n, int bytes)
{
	ft_putchar_fd((n & 0x000000FF), fd);
	if (bytes > 1)
		ft_putchar_fd((n & 0x0000FF00) >> 8, fd);
	if (bytes == 4)
	{
		ft_putchar_fd((n & 0x00FF0000) >> 16, fd);
		ft_putchar_fd((n & 0xFF000000) >> 24, fd);
	}
}

int			write_header(int fd, int size[2])
{
	write_int(fd, 0x42, 1);
	write_int(fd, 0x4D, 1);
	write_int(fd, size[0] * size[1] * sizeof(t_color) + 54, 4);
	write_int(fd, 0x00, 2);
	write_int(fd, 0x00, 2);
	write_int(fd, 0x36, 4);
	return (SUCCESS);
}

int			write_dibheader(int fd, int size[2])
{
	write_int(fd, 0x28, 4);
	write_int(fd, size[1], 4);
	write_int(fd, size[0], 4);
	write_int(fd, 0x01, 2);
	write_int(fd, 0x20, 2);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x0B13, 4);
	write_int(fd, 0x0B13, 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x00, 4);
	return (SUCCESS);
}

int			write_img(int fd, int size[2], t_color *map)
{
	int		i;

	i = 0;
	while (i < size[0] * size[1])
	{
		write_int(fd, map[i], 4);
		i++;
	}
	return (SUCCESS);
}
