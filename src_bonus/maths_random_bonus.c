/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_random_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:33:37 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 14:14:01 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Returns a random real in [0,1).
double	random_double(void)
{
	return ((double)rand() / (RAND_MAX + 1.0));
}
// Returns a random real in [min,max).

double	random_double_2(double min, double max)
{
	return (min + (max - min) * random_double());
}
