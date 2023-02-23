/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threading_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:33:56 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 19:25:53 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	get_pixel_line(t_minirt *s, int y, t_th *t)
{
	int		x;
	char	*dst;
	t_rtx	r;

	(void)t;
	x = -1;
	while (++x < WIDTH)
	{
		r.pixel_color.r = 0;
		r.pixel_color.g = 0;
		r.pixel_color.b = 0;
		r.t_u = 1 - (double)x / (double)(WIDTH - 1);
		r.t_v = (double)y / (double)(HEIGHT - 1);
		r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.start,
							mul_(s->r.horizon, r.t_u)),
						mul_(s->r.vertical, r.t_v)), s->cam_origin));
		r.pixel_color = color_add_(r.pixel_color, ray_color(&r.r, s));
		dst = s->img.add_r[0] + ((HEIGHT - y - 1) * s->img.line_length[0]
				+ x * (s->img.bits_ppix[0] / 8));
		*(unsigned int *)dst = write_color(r.pixel_color, s->s_pixel);
	}
}

void	*get_y(void *arg)
{
	t_th	*t;
	int		y_tmp;

	t = (t_th *)arg;
	while (1)
	{
		pthread_mutex_lock(&t->s->mutex);
		if (t->s->y == 0)
		{
			pthread_mutex_unlock(&t->s->mutex);
			break ;
		}
		else
			t->s->y--;
		y_tmp = t->s->y;
		pthread_mutex_unlock(&t->s->mutex);
		get_pixel_line(t->s, y_tmp, t);
	}
	return (NULL);
}

void	get_multi_threading(t_minirt *s)
{
	t_th	*t;
	int		i;

	i = -1;
	t = ft_calloc(NUM_THREADS, sizeof(t_th));
	if (!t)
		exit_error(s, "Error with malloc", 1);
	pthread_mutex_init(&s->mutex, NULL);
	s->y = HEIGHT - 1;
	while (++i < NUM_THREADS)
		t[i].s = s;
	i = -1;
	while (++i < NUM_THREADS)
		pthread_create(&t[i].thread, NULL, &get_y, &t[i]);
	i = -1;
	while (++i < NUM_THREADS)
		pthread_join(t[i].thread, NULL);
	free(t);
}
