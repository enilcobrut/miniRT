#include "miniRT.h"

void get_pixels(t_minirt *s, int min, int max)
{
	int y = max - 1;
	int x = 0;
	int i = 0;
	t_rtx r;

	while (y >= min)
	{
		x = 0;
		while (x < WIDTH)
		{
			r.pixel_color.r = 0;
			r.pixel_color.g = 0;
			r.pixel_color.b = 0;
			i = 0;
			while (i < s->samples_per_pixel)
			{
				r.mul_t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
				r.mul_t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
				r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner, mul_(s->r.horizon, r.mul_t_u)), mul_(s->r.vertical, r.mul_t_v)), s->cam_origin));
				r.pixel_color = color_add_(r.pixel_color, ray_color(&r.r, s, s->depth));
				i++;
			}
			s->buf[HEIGHT - y - 1][x] = write_color(r.pixel_color, s->samples_per_pixel);
			x++;
		}
		y--;
	}
}

void *dispatch_thread(void *arg)
{
	t_minirt *s;
	static int max;

	s = (t_minirt *)arg;
	pthread_mutex_lock(&s->count);
	if (s->on == 0)
	{
		max = HEIGHT + (HEIGHT / s->nt);
		s->on = 1;
	}
	max = max - (HEIGHT / s->nt);
	pthread_mutex_unlock(&s->count);
	get_pixels(s, max - (HEIGHT / s->nt), max);
	return (arg);
}
