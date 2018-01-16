/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:39:14 by vparis            #+#    #+#             */
/*   Updated: 2018/01/16 14:26:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMPLEX_H
# define FT_COMPLEX_H

#include "ft_type.h"

typedef struct	s_cplex {
	t_f64		r;
	t_f64		i;
}				t_cplex;

t_cplex			*ft_cplex_new(t_f64 r, t_f64 i);
void			ft_cplex_del(t_cplex *cplex);
void			ft_cplex_set(t_cplex *cplex, t_f64 r, t_f64 i);
t_f64			ft_cplex_mod(t_cplex *cplex);
t_f64			ft_cplex_mod_f(double r, double i);

#endif
