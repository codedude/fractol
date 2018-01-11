/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:39:14 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 16:44:41 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMPLEX_H
# define FT_COMPLEX_H

typedef struct	s_cplex {
	double		r;
	double		i;
}				t_cplex;

t_cplex			*ft_cplex_new(double r, double i);
void			ft_cplex_del(t_cplex *cplex);
void			ft_cplex_set(t_cplex *cplex, double r, double i);
double			ft_cplex_mod(t_cplex *cplex);

#endif
