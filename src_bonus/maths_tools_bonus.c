/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:33:43 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/16 11:26:56 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}

double	degrees_to_radians(double degrees)
{
	return (degrees * PI / 180.0);
}

double	ft_sqrt(double number)
{
	long			i;
	double			x2;
	double			y;
	const double	threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(double *)&i;
	y = y * (threehalfs - (x2 * y * y));
	return (y);
}

double	length_squared(t_vector v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

double	dot(t_vector u, t_vector v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}
