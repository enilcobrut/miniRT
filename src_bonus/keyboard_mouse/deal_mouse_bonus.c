/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_mouse_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:18:11 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/13 12:43:53 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

void	clic_button(t_minirt *s, int i, int x, int y)
{
	s->hit_obj = NULL;
	push_img_to_win(s, PROMPT);
	if (i == LEFT_MOUSE && s->prompt_stat == 0)
	{
		hit_something(s, x, y);
		display_hit_obj_params(s);
		display_prompt_status(s);
	}
}

void	scroll_on_cylinder(t_minirt *s, int i)
{
	if (i == SCROLL_UP)
	{
		s->hit_obj->u_.cy.height += INTERVAL * s->hit_obj->u_.cy.ratio;
		s->hit_obj->u_.cy.diameter += INTERVAL;
	}
	else if (i == SCROLL_DOWN && s->hit_obj->u_.cy.radius > 0)
	{
		s->hit_obj->u_.cy.height -= INTERVAL * s->hit_obj->u_.cy.ratio;
		s->hit_obj->u_.cy.diameter -= INTERVAL;
	}
	s->hit_obj->u_.cy.radius = s->hit_obj->u_.cy.diameter / 2;
}

void	scroll_on_sphere(t_minirt *s, int i)
{
	if (i == SCROLL_UP)
		s->hit_obj->u_.sp.diameter += INTERVAL;
	else if (i == SCROLL_DOWN && s->hit_obj->u_.sp.radius > 0)
		s->hit_obj->u_.sp.diameter -= INTERVAL;
	s->hit_obj->u_.sp.radius = s->hit_obj->u_.sp.diameter / 2;
}

void	scroll_on_cone(t_minirt *s, int i)
{
	if (i == SCROLL_UP)
	{
		s->hit_obj->u_.cy.height += INTERVAL * s->hit_obj->u_.co.ratio;
		s->hit_obj->u_.co.diameter += INTERVAL;
	}
	else if (i == SCROLL_DOWN && s->hit_obj->u_.co.radius > 0)
	{
		s->hit_obj->u_.cy.height -= INTERVAL * s->hit_obj->u_.co.ratio;
		s->hit_obj->u_.co.diameter -= INTERVAL;
	}
	s->hit_obj->u_.co.radius = s->hit_obj->u_.co.diameter / 2;
}

int	button_press(int i, int x, int y, t_minirt *s)
{
	if (s->prompt_stat == 0 && (i == RIGHT_MOUSE || i == LEFT_MOUSE))
		clic_button(s, i, x, y);
	else if (s->prompt_stat == 0 && (i == SCROLL_UP || i == SCROLL_DOWN))
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
				scroll_on_sphere(s, i);
			else if (s->hit_obj->type == CYLINDER)
				scroll_on_cylinder(s, i);
			else if (s->hit_obj->type == CONE)
				scroll_on_cone(s, i);
		}
	}
	display_scene(s);
	return (0);
}
