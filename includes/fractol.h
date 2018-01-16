/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/01/16 15:59:03 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_mlx.h"
# include "ft_tpool.h"

# define WIDTH		600
# define HEIGHT		600
# define TITLE		"FRACTOL DX4000"

# define THREADS	4
# define TASKS		32

# define ZOOM		0.2
# define FRACTAL_MANDEL	1
# define FRACTAL_JULIA	2

typedef struct	s_area {
	t_f64		x1;
	t_f64		y1;
	t_f64		x2;
	t_f64		y2;
	t_f64		zoom[2];
	int			max;
	int			size[2];
}				t_area;

typedef struct	s_env {
	t_tpool		*tp;
	t_area		area;
	int			keydown;
	int			show_fps;
	int			fractal;
	int			width;
	int			height;
	t_color		cs[64];
}				t_env;

typedef struct	s_data {
	t_env		env;
	t_mlx		mlx;
}				t_data;

typedef struct	s_algo {
	t_data		*data;
	int			start;
	int			end;
}				t_algo;


int				env_init(t_env *env, int fractal, int width, int height);
void			env_destroy(t_data *data);

void			check_key(t_env *env);
int				manage_key_down(int keycode, void *param);
int				manage_key_up(int keycode, void *param);
int				manage_mouse(int keycode, int x, int y, void *param);

void			draw_img(t_data *data);
void			clean_maps(t_data *data);
void			zoom(t_env *env, int zoom, int x, int y);

#endif
