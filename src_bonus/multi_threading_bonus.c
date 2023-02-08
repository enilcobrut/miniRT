#include "miniRT_bonus.h"

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


void get_pixels2(t_minirt *s, t_vector co)
{
	/*int size_x = 10;
	int size_y = 10;
*/
	int y = co.y + 100 - 1;
	int x = 0;
	int i = 0;
	t_rtx r;

	while (y >= co.y)
	{
		x = 0;
		while (x < co.x + 100)
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
			if (y == 1024 - 1 && x == 768 - 1)
				printf("%d\n", s->buf[HEIGHT - y - 1][x]);
			x++;
		}
		y--;
	}
}


void *dispatch_thread(void *arg)
{
	t_minirt *s;
	
	s = (t_minirt *)arg;
	static t_vector co;
	
	while (co.y < HEIGHT)
	{
		co.x = 0;
		while (co.x < WIDTH)
		{
			get_pixels2(s, co);
			co.x = co.x + 100;
		}
		co.y = co.y + 100;
	}


	
	/*static int max;
	pthread_mutex_lock(&s->count);
	if (s->on == 0)
	{
		max = HEIGHT + (HEIGHT / NUM_THREADS);
		s->on = 1;
	}
	max = max - (HEIGHT / NUM_THREADS);
	get_pixels(s, max - (HEIGHT / NUM_THREADS), max);
	pthread_mutex_unlock(&s->count);*/
	return (arg);
}

void	get_multi_threading(t_minirt *s)
{
	pthread_mutex_init(&s->count, NULL);
	s->on = 0;
	pthread_t *t = NULL;
	t = ft_calloc(NUM_THREADS, sizeof(pthread_t));
	int i = 0;
	s->buf[HEIGHT - 1][WIDTH - 1] = -1;
	//printf("%d\n", s->buf[HEIGHT - 1][WIDTH - 1]);
	while (1)
	{
		if (s->buf[HEIGHT - 1][WIDTH - 1] != -1)
			break;
		pthread_create(&t[i], NULL, &dispatch_thread, s);
		pthread_join(t[i], NULL);
		i++;
		if (i == NUM_THREADS)
			i = 0;
		printf("%d\n", i);
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