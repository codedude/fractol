/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 04:21:59 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 15:14:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "ft_mlx.h"

# define WIDTH		1024
# define HEIGHT		768
# define TITLE		"FRACTOL DX4000"

typedef struct	s_data {
	t_env		env;
	t_mlx		mlx;
}				t_data;

int				env_init(t_env *env, int width, int height);
void			env_destroy(t_data *data);
int				manage_key_down(int keycode, void *param);
int				manage_key_up(int keycode, void *param);
int				manage_mouse(int keycode, int x, int y, void *param);
int				compute_img(t_env *env);

#endif
