/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:49:10 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 19:12:21 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_windows(t_minirt *s, double x, double y)
{
	s->r.t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
	s->r.t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
	s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.start,
						mul_(s->r.horizon, s->r.t_u)),
					mul_(s->r.vertical, s->r.t_v)), s->cam_origin));
	s->r.pixel_color = color_add_(s->r.pixel_color, ray_color(&s->r.r, s));
}

void	get_pixels(t_minirt *s)
{
	char	*dst;
	int		y;
	int		x;
	int		i;

	y = HEIGHT;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WIDTH)
		{
			s->r.pixel_color = init_color(0, 0, 0);
			i = -1;
			while (++i < s->s_pixel)
				init_windows(s, x, y);
			dst = s->img.add_r + ((HEIGHT - y - 1) * s->img.line_length
					+ x * (s->img.bits_ppix / 8));
			*(unsigned int *)dst = write_color(s->r.pixel_color, s->s_pixel);
		}
	}
}

int	get_pixels_to_img(t_minirt *s)
{
	const t_vector	vup = init_vector(0, 1, 0);

	s->r.w = norm_(mul_(s->cam_vec_dir, -1));
	s->r.u = norm_(vec_cross(vup, s->r.w));
	s->r.v = vec_cross(s->r.w, s->r.u);
	s->r.theta = degrees_to_radians(s->cam_fov);
	s->r.h = tan(s->r.theta / 2);
	s->r.viewport_height = 2.0 * s->r.h;
	s->r.viewport_width = ((double)WIDTH / HEIGHT) * s->r.viewport_height;
	s->r.horizon = mul_(s->r.u, s->r.viewport_width);
	s->r.vertical = mul_(s->r.v, s->r.viewport_height);
	s->r.start = sub_(sub_(sub_(s->cam_origin, mul_(s->r.horizon, 0.5)),
				mul_(s->r.vertical, 0.5)), s->r.w);
	get_pixels(s);
	return (0);
}
