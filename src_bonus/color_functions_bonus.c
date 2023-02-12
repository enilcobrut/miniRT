/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_functions_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:25:55 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 21:26:15 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_color	color_add_(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color	color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	init_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

t_color	color_mul_scalar(t_color a, double b)
{
	return ((t_color){a.r * b, a.g * b, a.b * b});
}
