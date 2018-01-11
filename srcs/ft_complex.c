/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:45:09 by vparis            #+#    #+#             */
/*   Updated: 2018/01/11 16:48:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "ft_complex.h"

t_cplex			*ft_cplex_new(double r, double i)
{
	t_cplex	*tmp;

	if ((tmp = (t_cplex *)malloc(sizeof(t_cplex))) == NULL)
		return (NULL);
	tmp->i = i;
	tmp->r = r;
	return (tmp);
}

void			ft_cplex_del(t_cplex *cplex)
{
	free(cplex);
}

void			ft_cplex_set(t_cplex *cplex, double r, double i)
{
	cplex->r = r;
	cplex->i = i;
}

double			ft_cplex_mod(t_cplex *cplex)
{
	return (sqrt(cplex->r * cplex->r + cplex->i * cplex->i));
}
