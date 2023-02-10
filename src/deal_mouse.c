/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:37:01 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/10 17:37:12 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void display_hit_obj_params(t_minirt *s)
{
	// center axis -> 4
	// dir_ax pl cy co
	// diam sp cy co
	// height cy, co
	push_img_to_win(s, PROMPT);
	mlx_string_put(s->mlx, s->win, 30, HEIGHT + 2, 0xBA55D3, "OBJECT SELECTED #");
	itoa_to_win(s, s->hit_obj->n, 200, HEIGHT + 2);
	if (s->hit_obj->type == PLANE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "PLANE");
	else if (s->hit_obj->type == SPHERE)
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "SPHERE");
	else if (s->hit_obj->type == CYLINDER)
	{
		mlx_string_put(s->mlx, s->win, 250, HEIGHT + 2, 0xBA55D3, "CYLINDER");

		/*mlx_string_put(s->mlx, s->win, 30, 10, 0xFFFFFF, "CENTER [");
		itof_to_win(s, s->hit_obj->u_.cy.center.x, 125, HEIGHT + 2);
		itof_to_win(s, s->hit_obj->u_.cy.center.y, 125, HEIGHT + 2);
		itof_to_win(s, s->hit_obj->u_.cy.center.z, 125, HEIGHT + 2);

		mlx_string_put(s->mlx, s->win, 30, 30, 0xFFFFFF, "2");
		itof_to_win(s, s->cam_origin.y, 125, 30);
		mlx_string_put(s->mlx, s->win, 30, 50, 0xFFFFFF, "3");
		itof_to_win(s, s->cam_origin.z, 125, 50);
		mlx_string_put(s->mlx, s->win, 30, HEIGHT - 20, 0xFFFFFF, "4");
		itof_to_win(s, s->cam_vec_dir.x, 125, HEIGHT - 20);*/
	}
	/*
	mlx_string_put(s->mlx, s->win, 30, 10, 0xFFFFFF, "1");
	itof_to_win(s, s->cam_origin.x, 125, 10);
	mlx_string_put(s->mlx, s->win, 30, 30, 0xFFFFFF, "2");
	itof_to_win(s, s->cam_origin.y, 125, 30);
	mlx_string_put(s->mlx, s->win, 30, 50, 0xFFFFFF, "3");
	itof_to_win(s, s->cam_origin.z, 125, 50);
	mlx_string_put(s->mlx, s->win, 30, HEIGHT - 20, 0xFFFFFF, "4");
	itof_to_win(s, s->cam_vec_dir.x, 125, HEIGHT - 20);*/
}

void	hit_something(t_minirt *s, int x, int y)
{
	t_hit_record	rec;

	s->r.mul_t_u = 1 - (double)x / (double)(WIDTH - 1);
	s->r.mul_t_v = 1 - (double)y / (double)(HEIGHT - 1);
	s->r.r = init_rayon(s->cam_origin, sub_(add_(add_(s->r.lower_left_corner,
			mul_(s->r.horizon, s->r.mul_t_u)), mul_(s->r.vertical, s->r.mul_t_v)),
			s->cam_origin));
	if (hit(&s->r.r, 0.001, INF, &rec, s->obj))
	{
		s->hit_obj = rec.hit_obj;
	}
}

int	button_press(int i, int x, int y, t_minirt *s)
{
	push_img_to_win(s, PROMPT);
	if (i == RIGHT_MOUSE || i == LEFT_MOUSE)
	{
		s->hit_obj = NULL;
		if (i == LEFT_MOUSE)
			hit_something(s, x, y);
	}
	else if (i == SCROLL_UP || i == SCROLL_DOWN)
	{
		if (!s->hit_obj)
		{
			if (i == SCROLL_UP)
				s->cam_origin.z += INTERVAL;
			else if (i == SCROLL_DOWN)
				s->cam_origin.z -= INTERVAL;
		}
		else if (s->hit_obj)
		{
			if (s->hit_obj->type == SPHERE)
			{
				if (i == SCROLL_UP)
					s->hit_obj->u_.sp.radius += INTERVAL;
				else if (i == SCROLL_DOWN && s->hit_obj->u_.sp.radius > 0)
					s->hit_obj->u_.sp.radius -= INTERVAL;
			}
			/*else if (s->hit_obj->type == PLANE)
			{
				if (i == 4)
					s->hit_obj->u_.pl.radius += INTERVAL;
				else if (i == SCROLL_DOWN && s->hit_obj->u_.sp.radius > 0)
					s->hit_obj->u_.sp.radius -= INTERVAL;
			}*/
			else if (s->hit_obj->type == CYLINDER)
			{
				if (i == SCROLL_UP)
					s->hit_obj->u_.cy.radius += INTERVAL;
				else if (i == SCROLL_DOWN && s->hit_obj->u_.cy.radius > 0)
					s->hit_obj->u_.cy.radius -= INTERVAL;
			}
		}
	}
	display_scene(s);
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	return (0);
}
