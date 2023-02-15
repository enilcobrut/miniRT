#include "miniRT_bonus.h"

void rtx_test(t_minirt *s, int y, t_th *t)
{
	int x;
	int i;
	char *dst;
	t_rtx r;
	(void)t;
	x = 0;
	i = 0;
	while (x < WIDTH)
	{
		r.pixel_color.r = 0;
		r.pixel_color.g = 0;
		r.pixel_color.b = 0;
		r.t_u = 1 - (double)x / (double)(WIDTH - 1);
		r.t_v = (double)y / (double)(HEIGHT - 1);
		r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.start, mul_(s->r.horizon, r.t_u)), mul_(s->r.vertical, r.t_v)), s->cam_origin));
		r.pixel_color = color_add_(r.pixel_color, ray_color(&r.r, s));
		dst = s->img.add_r[0] + ((HEIGHT - y - 1) * s->img.line_length[0] + x * (s->img.bits_ppix[0] / 8));
		*(unsigned int *)dst = write_color(r.pixel_color, s->s_pixel);
		x++;
	}
}
/*
void	rtx_test2(t_minirt *s, int y, int x, t_th *t)
{

	char	*dst;
	t_rtx	r;
	
		r.pixel_color.r = 0;
		r.pixel_color.g = 0;
		r.pixel_color.b = 0;
		// i = 0;
		// while (i < s->samples_per_pixel)
		// {
		 	r.mul_t_u = 1 - (double)x  / (double)(WIDTH - 1);
		 	r.mul_t_v = (double)y / (double)(HEIGHT - 1);
			pthread_mutex_lock(&t->counter_mutex);
			r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner, mul_(s->r.horizon, r.mul_t_u)), mul_(s->r.vertical, r.mul_t_v)), s->cam_origin));
			r.pixel_color = color_add_(r.pixel_color, ray_color(&r.r, s));
			pthread_mutex_unlock(&t->counter_mutex);
			//i++;
		//}
		pthread_mutex_lock(&t->counter_mutex);
		dst = s->img.add_r[0] + ((HEIGHT - y - 1) * s->img.line_length[0] + x * (s->img.bits_ppix[0] / 8));
		*(unsigned int *)dst = write_color(r.pixel_color, s->samples_per_pixel);
		pthread_mutex_unlock(&t->counter_mutex);

}*/
/*
void	*test3(void *arg)
{
	t_th *t;
	t = (t_th *)arg;
	
	while (1)
	{
		//printf("x %d y %d, ", t->s->x, t->s->y);
		//pthread_mutex_lock(&t->counter_mutex);
		if (t->s->y == 0 && t->s->x == WIDTH - 1)
			break;
		//pthread_mutex_unlock(&t->counter_mutex);
		//pthread_mutex_lock(&t->counter_mutex);
		if (t->s->y != 0 && t->s->x != WIDTH - 1)
		{
			
			if (t->s->x == WIDTH)
			{
				t->s->x = 0;
				t->s->y--;
			}
			else
				t->s->x++;
			
		}
		//pthread_mutex_unlock(&t->counter_mutex);
		//pthread_mutex_lock(&t->counter_mutex);
		rtx_test2(t->s, t->s->y, t->s->x, t);
		//pthread_mutex_unlock(&t->counter_mutex);
		
		
	}
	return NULL;
}*/

void *test2(void *arg)
{
	t_th *t;
	int y_tmp;
	t = (t_th *)arg;

	while (1)
	{
		pthread_mutex_lock(&t->s->mutex);
		if (t->s->y == 0)
		{
			pthread_mutex_unlock(&t->s->mutex);
			break;
		}
		else
			t->s->y--;
		y_tmp = t->s->y;
		pthread_mutex_unlock(&t->s->mutex);
		rtx_test(t->s, y_tmp, t);
	}
	return NULL;
}

void	get_multi_threading(t_minirt *s)
{
	t_th *t = NULL;
	int	nb = NUM_THREADS;
	t = ft_calloc(nb, sizeof(t_th));
	int i = 0;
	//int ret;
	pthread_mutex_init(&s->mutex, NULL);
	s->y = HEIGHT - 1;
	s->x = 0;
	s->on = 0;
	//t_th *th = NULL;
	/*while (i < nb)
	{
		th = lst_add__th(&t, lst_new_th(i));
		th->s = s;
		i++;
	}
	th = t;
	while (th)
	{
		pthread_create(&th->thread, NULL, &test2, th);
		th = th->next;
	}
	th = t;
	while (th)
	{
		pthread_join(th->thread, NULL);
		th = th->next;
	}
	th = t;
	while (th)
	{
		free(th);
		th = th->next;
	}*/
	while (i < nb)
	{
		t[i].s = s;
		i++;
	}
	i = 0;
	while (i < nb)
	{
		pthread_create(&t[i].thread, NULL, &test2, &t[i]);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		pthread_join(t[i].thread, NULL);
		i++;
	}
	free(t);
}