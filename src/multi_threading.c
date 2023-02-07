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
	//pthread_mutex_lock(&s->count);
	if (s->on == 0)
	{
		max = HEIGHT + (HEIGHT / s->nt);
		s->on = 1;
	}
	max = max - (HEIGHT / s->nt);
	get_pixels(s, max - (HEIGHT / s->nt), max);
	//pthread_mutex_unlock(&s->count);
	return (arg);
}


void	get_multi_threading(t_minirt *s)
{
	pthread_mutex_init(&s->count, NULL);
	s->on = 0;
	pthread_t *t = NULL;
	t = ft_calloc(s->nt, sizeof(pthread_t));
	int i = 0;
	while (i < s->nt)
	{
		pthread_create(&t[i], NULL, &dispatch_thread, s);
		//printf("i: %d, ret :%d\n", i, pthread_create(&t[i], NULL, &dispatch_thread, s));
		i++;
	}
	i = 0;
	while (i < s->nt)
	{
		//printf("i: %d, ret :%d\n",i, pthread_join(t[i], NULL));
		pthread_join(t[i], NULL);
		i++;
	}
	pthread_mutex_destroy(&s->count);
	free (t);
	
}

void get_no_multi_threading(t_minirt *s)
{
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
			s->buf[HEIGHT - y - 1][x] = write_color(s->r.pixel_color, s->samples_per_pixel);
			x++;
		}
		y--;
	}
}