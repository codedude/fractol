/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:01:14 by vparis            #+#    #+#             */
/*   Updated: 2018/02/06 14:05:35 by valentin         ###   ########.fr       */
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

static void	get_filename(int nb, char *filename)
{
	ft_bzero(filename, 26);
	ft_strcpy(filename, FILE_NAME);
	filename[18] = '0' + nb / 100;
	filename[19] = '0' + nb / 10 - (nb / 100) * 10;
	filename[20] = '0' + nb % 10;
}

int			save_img(t_data *data)
{
	int			size[2];
	t_color		*img;
	char		filename[26];
	int			fd;
	static int	nb = 0;

	if (data->env.save_img == 0)
		return (SUCCESS);
	data->env.save_img = 0;
	size[0] = data->mlx.win[MAIN_WIN].height;
	size[1] = data->mlx.win[MAIN_WIN].width;
	img = data->mlx.win[MAIN_WIN].img;
	get_filename(nb, filename);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		return (ERROR);
	ft_putstr("Saving image... ");
	write_header(fd, size);
	write_dibheader(fd, size);
	write_img(fd, size, img);
	close(fd);
	nb++;
	ft_putstr("Image saved in ");
	ft_putendl(filename);
	return (SUCCESS);
}
