/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_complex.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:39:14 by vparis            #+#    #+#             */
/*   Updated: 2018/01/18 14:53:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_COMPLEX_H
# define FT_COMPLEX_H

# include "ft_type.h"

typedef t_f128	t_cplex_v __attribute__((vector_size(32),aligned(32)));

#endif
