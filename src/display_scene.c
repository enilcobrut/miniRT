/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 16:49:10 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 12:46:07 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	display_scene(t_minirt *s)
{
	get_pixels_to_img(s);
	push_img_to_win(s);
	if (s->cam_param_display == 1)
		display_param_cam(s);
	display_hit_obj_params(s);
}

void	get_prompt_color(t_minirt *s)
{
	int		x;
	int		y;
	char	*dst;
	t_color	color;

	x = 0;
	y = 0;
	color = init_color(100, 100, 100);
	while (y < 32)
	{
		x = 0;
		while (x < WIDTH)
		{
			dst = s->img.add_r + (y * s->img.line_length
					+ x * (s->img.bits_ppix / 8));
			*(unsigned int *)dst = get_hexa_color(color);
			x++;
		}
		y++;
		color.r = color.r - 2;
		color.g = color.g - 2;
		color.b = color.b - 2;
	}
}

void	init_windows(t_minirt *s, double x, double y)
{
	s->r.t_u = 1 - ((double)x + random_double()) / (double)(WIDTH - 1);
	s->r.t_v = ((double)y + random_double()) / (double)(HEIGHT - 1);
	s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.start,
						mul_(s->r.horizon, s->r.t_u)),
					mul_(s->r.vertical, s->r.t_v)), s->cam_origin));
	s->r.pixel_color = color_add_(s->r.pixel_color, ray_color(&s->r.r, s));
}

void	get_no_multi_threading(t_minirt *s)
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
	get_no_multi_threading(s);
	return (0);
}
