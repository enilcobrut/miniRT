/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scene_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:46:22 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 14:11:41 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	display_scene(t_minirt *s)
{
	get_pixels_to_img(s);
	push_img_to_win(s, SCENE);
	if (s->cam_param_display == 1)
		display_param_cam(s);
	display_hit_obj_params(s);
}

void	set_face_normal(const t_rayon *r, t_hit *rec, t_vector outward_normal)
{
	rec->front_face = dot(r->direction, outward_normal) < 0;
	if (rec->front_face)
	{
		rec->normal = outward_normal;
		rec->front_face = 1;
	}
	else
	{
		rec->normal = mul_(outward_normal, -1);
		rec->front_face = 0;
	}
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
			dst = s->img.add_r[1] + (y * s->img.line_length[1]
					+ x * (s->img.bits_ppix[1] / 8));
			*(unsigned int *)dst = get_hexa_color(color);
			x++;
		}
		y++;
		color.r = color.r - 2;
		color.g = color.g - 2;
		color.b = color.b - 2;
	}
}

void	get_pixels_to_img(t_minirt *s)
{
	const t_vector	vup = init_vector(0, 1, 0);
	clock_t			start;
	clock_t			end;
	double			elapsed;

	start = clock();
	s->r.w = norm_(mul_(s->cam_vec_dir, -1));
	s->r.u = norm_(vec_cross(vup, s->r.w));
	s->r.v = vec_cross(s->r.w, s->r.u);
	s->r.theta = degrees_to_radians(s->cam_fov);
	s->r.h = tan(s->r.theta / 2);
	s->r.viewport_height = 2.0 * s->r.h;
	s->r.viewport_width = ((double)WIDTH / HEIGHT) * s->r.viewport_height;
	s->r.horizon = mul_(s->r.u, s->r.viewport_width);
	s->r.vertical = mul_(s->r.v, s->r.viewport_height);
	s->r.start = sub_(sub_(sub_(s->cam_origin,
					mul_(s->r.horizon, 0.5)),
				mul_(s->r.vertical, 0.5)), s->r.w);
	get_multi_threading(s);
	end = clock();
	elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Temps d'exécution : %lf secondes\n", elapsed);
}
