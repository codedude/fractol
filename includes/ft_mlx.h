/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:44:18 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 15:27:38 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "libft.h"
# include "mlx.h"
# include "ft_mlx_key.h"

# define MLX_MAX_WINDOW	4
# define MAIN_WIN		0

# define C_RED			0x00FF0000
# define C_GREEN		0x0000FF00
# define C_BLUE			0x000000FF
# define C_WHITE		0x00FFFFFF
# define C_BLACK		0x00000000
# define C_GREY			0x00999999
# define C_MOUNT		0x0080461B
# define C_WATER		0x002EA3BF
# define C_GRASS		0x00257F03
# define C_SNOW			0x00DDDDDD
# define C_DEEP			0x00003F69

typedef int		t_color;

typedef struct	s_win {
	void		*win;
	char		*img;
	void		*img__;
	int			width;
	int			height;
	char		*title;
}				t_win;

typedef struct	s_mlx {
	void		*mlx;
	t_win		win[MLX_MAX_WINDOW];
}				t_mlx;

typedef struct	s_pixel {
	int			x;
	int			y;
	t_color		c;
}				t_pixel;

typedef struct	s_env {
	double		**map;
}				t_env;

/*
** MLX and window management
*/

void			ft_mlx_init(t_mlx *mlx);
int				ft_mlx_win(t_mlx *mlx, int width, int height, char *title);
void			ft_mlx_destroy(t_mlx *mlx, int win);
int				ft_mlx_exit(void);

/*
** Drawing management
*/

void			ft_mlx_clear(t_mlx *mlx, int win);
void			ft_mlx_pixel(t_mlx *mlx, int win, t_pixel *pix);
void			ft_mlx_string(t_mlx *mlx, int win, t_pixel *pix, char *str);

/*
** Pixel manipulation
*/

t_color			ft_mlx_getcolor(int r, int g, int b);

#endif
