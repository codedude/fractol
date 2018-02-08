/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:44:22 by valentin          #+#    #+#             */
/*   Updated: 2018/02/08 13:59:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fractol.h"

static void	get_int(int n, char *buff, int bytes)
{
	buff[0] = n & 0x000000FF;
	buff[1] = (n & 0x0000FF00) >> 8;
	if (bytes == 4)
	{
		buff[2] = (n & 0x00FF0000) >> 16;
		buff[3] = (n & 0xFF000000) >> 24;
	}
}

void		write_int(int fd, int n, int bytes)
{
	char	buff[4];

	get_int(n, (char *)buff, bytes);
	write(fd, buff, bytes);
}

int			write_img(int fd, int size[2], t_color *map)
{
	int		i;
	int		n;
	char	buff[BMP_BUFF];

	i = 0;
	n = 0;
	while (i < size[0] * size[1])
	{
		get_int(map[i], (char *)&buff[n], 4);
		n += 4;
		if (n == BMP_BUFF)
		{
			write(fd, buff, BMP_BUFF);
			n = 0;
		}
		i++;
	}
	if (n > 0)
		write(fd, buff, n);
	return (SUCCESS);
}
