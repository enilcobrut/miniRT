/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:04:13 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 11:04:16 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	clamp_color(t_color color)
{
	return ((t_color){clamp(color.r, 0, 1), clamp(color.g, 0, 1),
		clamp(color.b, 0, 1)});
}

t_color	color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color	color_add_(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

int	write_color(t_color pixel_color, int sample_per_pixel)
{
	double	scale;
	t_color	new_c;

	scale = 1.0 / (double)sample_per_pixel;
	new_c.r = pixel_color.r * scale;
	new_c.g = pixel_color.g * scale;
	new_c.b = pixel_color.b * scale;
	return (create_trgb(0, new_c.r * 255, new_c.g * 255, new_c.b * 255));
}

t_color	init_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}
