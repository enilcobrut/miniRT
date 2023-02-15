/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_random_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:46:37 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:46:39 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vector	vec_random(void)
{
	return ((t_vector){(double)random_double(), (double)random_double(),
		(double)random_double()});
}

t_vector	vec_random_2(double min, double max)
{
	return ((t_vector){random_double_2(min, max), random_double_2(min, max),
		random_double_2(min, max)});
}

t_vector	random_in_unit_sphere(void)
{
	double		len;
	t_vector	p;

	while (1)
	{
		p = vec_random_2(-1, 1);
		len = length_squared(p);
		if (len <= 1 && len > 0)
			return (get_normalize_vector(p));
	}
}

t_vector	random_in_unit_sphere_2(void)
{
	double		len;
	t_vector	p;

	while (1)
	{
		p = vec_random_2(-1, 1);
		len = length_squared(p);
		if (len <= 1 && len > 0)
			return (p);
	}
}
