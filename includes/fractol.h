/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/02/09 11:44:40 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_mlx.h"
# include "ft_tpool.h"

# define WIDTH			1000
# define HEIGHT			1000
# define TITLE			"FRACTOL DX4000"
# define FILE_NAME		"saved_img/fractal_XXX.bmp"

# define THREADS		8
# define TASKS			32

# define ZOOM			0.2
# define MOVE			0.01
# define FRACTAL_MANDEL	1
# define FRACTAL_JULIA	2
# define FRACTAL_BURN	3

typedef struct	s_area {
	t_f128		x1;
	t_f128		y1;
	t_f128		x2;
	t_f128		y2;
	t_f128		zoom[2];
	t_u32		max;
	t_u32		size[2];
}				t_area;

typedef struct	s_env {
	t_tpool		*tp;
	t_area		area;
	int			keydown;
	int			refresh;
	int			mmove[3];
	int			show_fps;
	int			fractal;
	int			width;
	int			height;
	int			save_img;
	t_color		cs[16];
}				t_env;

typedef struct	s_data {
	t_env		env;
	t_mlx		mlx;
}				t_data;

typedef struct	s_algo {
	t_data		*data;
	t_u32		start;
	t_u32		end;
}				t_algo;

int				env_init(t_env *env, int fractal, int width, int height);
void			env_destroy(t_data *data);
void			mandel_init(t_area *area);
void			julia_init(t_area *area);
void			burn_init(t_area *area);

void			color_rot(t_color cs[16]);
t_f128			pix_to_cplex_x(t_area *area, int x);
t_f128			pix_to_cplex_y(t_area *area, int y);
t_f128			pix_to_cplex_mdb_x(int x);
t_f128			pix_to_cplex_mdb_y(int y);

void			check_key(t_env *env);
void			check_key2(t_env *env);
int				manage_key_down(int keycode, void *param);
int				manage_key_up(int keycode, void *param);
int				manage_mouse(int keycode, int x, int y, void *param);
int				manage_mouse_move(int x, int y, void *param);

void			draw_img(t_data *data);
void			clean_maps(t_data *data);
void			zoom(t_env *env, int zoom, int x, int y);

int				draw_julia(void *data);
int				draw_burn(void *data);
int				draw_mandel(void *data);
void			color_rot(t_color cs[16]);
void			init_color(t_color cs[16]);
void			init_color_r(t_color cs[16]);

int				write_header(int fd, int size[2]);
int				write_dibheader(int fd, int size[2]);
int				write_img(int fd, int size[2], t_color *map);
void			write_int(int fd, int n, int bytes);
int				save_img(t_data *data);

#endif
