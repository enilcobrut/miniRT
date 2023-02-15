/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_mouse_hit_obj_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:14:06 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/14 17:03:49 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	display_hit_obj_params(t_minirt *s)
{
	push_img_to_win(s, PROMPT);
	if (!s->hit_obj)
		return ;
	mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3,
		"OBJECT SELECTED #");
	itoa_to_win(s, s->hit_obj->n, 200, HEIGHT + 2);
	if (s->hit_obj->type == PLANE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "PLANE");
	else if (s->hit_obj->type == SPHERE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "SPHERE");
	else if (s->hit_obj->type == CYLINDER)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "CYLINDER");
	else if (s->hit_obj->type == CONE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "CONE");
}

void	hit_something(t_minirt *s, int x, int y)
{
	t_hit	rec;

	s->r.t_u = 1 - (double)x / (double)(WIDTH - 1);
	s->r.t_v = 1 - (double)y / (double)(HEIGHT - 1);
	s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.start,
						mul_(s->r.horizon, s->r.t_u)), mul_(s->r.vertical,
						s->r.t_v)), s->cam_origin));
	if (hit(&s->r.r, INF, &rec, s->obj))
		s->hit_obj = rec.hit_obj;
}
