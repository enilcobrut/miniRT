#include "miniRT.h"

t_color color_add_(t_color a, t_color b)
{
	return ((t_color){a.r + b.r, a.g + b.g, a.b + b.b});
}

t_color color_mul(t_color a, t_color b)
{
	return ((t_color){a.r * b.r, a.g * b.g, a.b * b.b});
}

t_color init_color(double r, double g, double b)
{
	return ((t_color){r, g, b});
}

t_color	color_mul_scalar(t_color a, double b)
{
	return ((t_color){a.r * b, a.g * b, a.b * b});
}

t_vector 	hexa_to_rgb(int hexa, unsigned char *red, unsigned char *green, unsigned char *blue)
{
	t_vector v_color;

	*red = (hexa >> 16) & 0xff;
	*green = (hexa >> 8) & 0xff;
	*blue = hexa & 0xff;
	v_color.x = *red;
	v_color.y = *green;
	v_color.z = *blue;
	return (v_color);
}

t_color map_color(t_color color)
{
	return ((t_color) {color.r / 255.0, color.g / 255.0, color.b / 255.0});

}

int	write_color(t_color	 pixel_color, int sample_per_pixel)
{
	double scale = 1.0 / (double)sample_per_pixel;
	t_color new_c;
	new_c.r = pixel_color.r * scale;//sqrt(pixel_color.r * scale);
	new_c.g = pixel_color.g * scale; //sqrt(pixel_color.g * scale);
	new_c.b = pixel_color.b * scale;//sqrt(pixel_color.b * scale);
	return (create_trgb(0, new_c.r  * 255,  new_c.g * 255,  new_c.b*255));
	//return (create_trgb(0, clamp(new_c.r, 0.0, 0.999) * 256,  clamp(new_c.g, 0.0, 0.999) * 256,  clamp(new_c.b, 0.0, 0.999) * 255));
}