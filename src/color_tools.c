#include "miniRT.h"

t_color	color_mul_scalar(t_color a, double b)
{
	return ((t_color){a.r * b, a.g * b, a.b * b});
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

int	print_color(t_color color)
{	
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}
