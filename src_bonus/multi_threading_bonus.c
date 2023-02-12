#include "miniRT_bonus.h"

/*void get_pixels(t_minirt *s, int min, int max)
{
	int y = max - 1;
	int x = 0;
	int i = 0;
	char *dst;
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
			dst = s->img.add_r[0] + ((HEIGHT - y - 1) * s->img.line_length[0]
					+ x * (s->img.bits_ppix[0] / 8));
			*(unsigned int *)dst = write_color(s->r.pixel_color, s->samples_per_pixel);
			x++;
		}
		y--;
	}
}*/

void	rtx_test(t_minirt *s, int y)
{
	int		x;
	int		i;
	char	*dst;
	t_rtx	r;

	x = 0;
	i = 0;
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
		dst = s->img.add_r[0] + ((HEIGHT - y - 1) * s->img.line_length[0] + x * (s->img.bits_ppix[0] / 8));
		*(unsigned int *)dst = write_color(r.pixel_color, s->samples_per_pixel);
		x++;
	}
}

void	*test2(void *arg)
{
	t_th *t;
	t = (t_th *)arg;
	static int y;
	
	pthread_mutex_lock(&t->counter_mutex);
	if (t->s->on == 0)
	{
		y = HEIGHT - 1;
		t->s->on = 1;
	}
	pthread_mutex_unlock(&t->counter_mutex);
	while (1)
	{
		pthread_mutex_lock(&t->counter_mutex);
		if (y == 0)
			break;
		else
			y--;
		pthread_mutex_unlock(&t->counter_mutex);
		rtx_test(t->s, y);
	}
	return NULL;
}

void	get_multi_threading(t_minirt *s)
{
	t_th *t = NULL;
	int	nb = NUM_THREADS * 10;
	t = ft_calloc(nb + 1, sizeof(t_th));
	int i = 0;
	int ret;
	s->on = 0;
	while (i < nb)
	{
		t[i].s = s;
		pthread_mutex_init(&t[i].counter_mutex, NULL);
		pthread_mutex_init(&t[i].mutex, NULL);
		ret = pthread_create(&t[i].thread, NULL, &test2, &t[i]);
		//printf("%d, ", ret);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		pthread_join(t[i].thread, NULL);
		i++;
	}
	free (t);
}