#include "miniRT_bonus.h"

void get_pixels(t_minirt *s, int min, int max)
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
}


void get_pixels2(t_minirt *s, t_vector co)
{
	/*int size_x = 10;
	int size_y = 10;*/
	
	char *dst;
	int y = co.y + 200 - 1;
	int x = co.x;
	int i = 0;
	t_rtx r;
	
	while (y >= co.y)
	{
		x = co.x;
		while (x < co.x + 200)
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
			printf("%x", write_color(s->r.pixel_color, s->samples_per_pixel));
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
	

	pthread_mutex_lock(&s->count);
	if (s->on == 0)
	{
		co.x = 0;
		co.y = 0;
		s->on = 1;
		get_pixels2(s, co);
	}
	pthread_mutex_unlock(&s->count);
	/*get_pixels2(s, co);
	pthread_mutex_lock(&s->count);
	co.x += 200;
	pthread_mutex_unlock(&s->count);*/
	
	/*while (co.y < HEIGHT)
	{
		pthread_mutex_lock(&s->count);
		co.x = 0;
		pthread_mutex_unlock(&s->count);
		while (co.x < WIDTH)
		{
			get_pixels2(s, co);
			pthread_mutex_lock(&s->count);
			co.x = co.x + 100;
			pthread_mutex_unlock(&s->count);
		}
		pthread_mutex_lock(&s->count);
		co.y = co.y + 100;
		pthread_mutex_unlock(&s->count);
	}
	pthread_mutex_lock(&s->count);*/
	/*if (co.x < WIDTH - 100 && co.y < HEIGHT - 100)
	{

		pthread_mutex_unlock(&s->count);
		dispatch_thread(arg);

	}*/
	//pthread_mutex_unlock(&s->count);

	
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

typedef struct s_th
{
	pthread_t	thread;
	t_minirt	*s;
	int block_counter;
	pthread_mutex_t mutex;
	pthread_mutex_t counter_mutex;
} t_th;

#define BLOCK_SIZE 10
void *test(void *arg)
{
	t_th *t;
	
	t = (t_th *)arg;

	int y;
	int x;
	int i;
	char *dst;
	t_rtx r;
	while (1)
	{
		pthread_mutex_lock(&t->counter_mutex);
		int current_block = t->block_counter++;
		pthread_mutex_unlock(&t->counter_mutex);
		if (current_block >= WIDTH / BLOCK_SIZE * HEIGHT / BLOCK_SIZE)
			break;
		int start_row = (current_block / (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
		int start_col = (current_block % (WIDTH / BLOCK_SIZE)) * BLOCK_SIZE;
		int end_row = start_row + BLOCK_SIZE;
		int end_col = start_col + BLOCK_SIZE;

		pthread_mutex_lock(&t->mutex);
		y = start_row - 1;
		pthread_mutex_unlock(&t->mutex);
		while (y >= end_row)
		{
			pthread_mutex_lock(&t->mutex);
			x = 0;
			pthread_mutex_unlock(&t->mutex);
			while (x < end_col)
			{
				pthread_mutex_lock(&t->mutex);
				r.pixel_color.r = 0;
				r.pixel_color.g = 0;
				r.pixel_color.b = 0;
				i = 0;
				while (i < t->s->samples_per_pixel)
				{
					r.mul_t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
					r.mul_t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
					r.r = init_rayon(t->s->cam_origin, sub_(add_(add_(t->s->r.lower_left_corner, mul_(t->s->r.horizon, r.mul_t_u)), mul_(t->s->r.vertical, r.mul_t_v)), t->s->cam_origin));
					r.pixel_color = color_add_(r.pixel_color, ray_color(&r.r, t->s, t->s->depth));
					i++;
				}
				dst = t->s->img.add_r[0] + ((HEIGHT - y - 1) * t->s->img.line_length[0] + x * (t->s->img.bits_ppix[0] / 8));
				*(unsigned int *)dst = write_color(t->s->r.pixel_color, t->s->samples_per_pixel);
				x++;
				pthread_mutex_unlock(&t->mutex);
				
			}
			pthread_mutex_lock(&t->mutex);
			y--;
			pthread_mutex_unlock(&t->mutex);
		}
	}
	return NULL;
}

void	get_multi_threading(t_minirt *s)
{
	pthread_mutex_init(&s->count, NULL);
	s->on = 0;
	t_th *t = NULL;
	t = ft_calloc(NUM_THREADS + 1, sizeof(t_th));
	int i = 0;
	while (i < NUM_THREADS)
	{
		t[i].s = s;
		pthread_mutex_init(&t[i].counter_mutex, NULL);
		pthread_mutex_init(&t[i].mutex, NULL);
		pthread_create(&t[i].thread, NULL, &test, &t[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(t[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&s->count);
	free (t);
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
					+ x * (s->img.bits_ppix[0] / 8));
			*(unsigned int *)dst = write_color(s->r.pixel_color, s->samples_per_pixel);
			x++;
		}
		y--;
	}
}