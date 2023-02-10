#include "miniRT.h"

void display_scene(t_minirt *s)
{
	get_pixels_to_img(s);
	push_img_to_win(s, SCENE);
	if (s->cam_param_display == 1)
		display_param_cam(s);
	if (s->hit_obj)
		display_hit_obj_params(s);
}

void	get_prompt_color(t_minirt *s)
{
	int x = 0;
	int y = 0;
	char *dst;
	
	t_color color = init_color(100,100,100);

	while (y < 32)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = s->img.add_r[1] + (y * s->img.line_length[1] 
					+ x * (s->img.bits_per_pixel[1] / 8));
			*(unsigned int *)dst = get_hexa_color(color);
			x++;
		}
		y++;
		color.r = color.r - 2;
		color.g = color.g - 2;
		color.b = color.b - 2;
	}
}

void get_no_multi_threading(t_minirt *s)
{
	char *dst;

	int y = HEIGHT - 1;
	int x = 0;
	int i = 0;
	while (y >= 0)
	{
		x = 0;
		while (x < WIDTH)
		{
			s->r.pixel_color.r = 0;
			s->r.pixel_color.g = 0;
			s->r.pixel_color.b = 0;
			i = 0;
			while (i < s->samples_per_pixel)
			{
				s->r.mul_t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
				s->r.mul_t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
				s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner, mul_(s->r.horizon, s->r.mul_t_u)), mul_(s->r.vertical, s->r.mul_t_v)), s->cam_origin));
				s->r.pixel_color = color_add_(s->r.pixel_color, ray_color(&s->r.r, s, s->depth));
				i++;
			}
			dst = s->img.add_r[0] + ((HEIGHT - y - 1) * s->img.line_length[0]
					+ x * (s->img.bits_per_pixel[0] / 8));
			*(unsigned int *)dst = write_color(s->r.pixel_color, s->samples_per_pixel);
			//s->buf[HEIGHT - y - 1][x] = write_color(s->r.pixel_color, s->samples_per_pixel);
			x++;
		}
		y--;
	}
}

int	get_pixels_to_img(t_minirt *s)
{
	const t_vector vup = init_vector(0, 1, 0);

	s->r.w = vec3_unit_vector(mul_(s->cam_vec_dir, -1));
	s->r.u = vec3_unit_vector(vec_cross(vup, s->r.w));
	s->r.v = vec_cross(s->r.w, s->r.u);
	s->r.theta = degrees_to_radians(s->cam_fov);
	s->r.h = tan(s->r.theta/2);
	s->r.viewport_height = 2.0 * s->r.h;
	s->r.viewport_width = ((double)WIDTH/HEIGHT) * s->r.viewport_height;
	s->r.horizon = mul_(s->r.u, s->r.viewport_width);
	s->r.vertical = mul_(s->r.v, s->r.viewport_height);
	s->r.lower_left_corner = sub_(sub_(sub_(s->cam_origin, mul_(s->r.horizon, 0.5)), mul_(s->r.vertical, 0.5)), s->r.w);
	get_no_multi_threading(s);
	return (0);
}
