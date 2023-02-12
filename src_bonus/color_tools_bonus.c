/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:25:40 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 21:25:42 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

t_vector	hexa_to_rgb(int hexa, unsigned char *red, unsigned char *green, unsigned char *blue)
{
	t_vector	v_color;

	*red = (hexa >> 16) & 0xff;
	*green = (hexa >> 8) & 0xff;
	*blue = hexa & 0xff;
	v_color.x = *red;
	v_color.y = *green;
	v_color.z = *blue;
	return (v_color);
}

int	get_hexa_color(t_color color)
{
	if (color.r > 255)
		color.r = 255;
	else if (color.r < 0)
		color.r = 0;
	if (color.g > 255)
		color.g = 255;
	else if (color.g < 0)
		color.g = 0;
	if (color.b > 255)
		color.b = 255;
	else if (color.b < 0)
		color.b = 0;
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

t_color	map_color(t_color color)
{
	return ((t_color){color.r / 255.0, color.g / 255.0, color.b / 255.0});
}

int	write_color(t_color	 pixel_color, int sample_per_pixel)
{
	double	scale;
	t_color	new_c;
	
	scale = 1.0 / (double)sample_per_pixel;
	new_c.r = pixel_color.r * scale;
	new_c.g = pixel_color.g * scale;
	new_c.b = pixel_color.b * scale;
	return (create_trgb(0, new_c.r  * 255,  new_c.g * 255,  new_c.b*255));
}
