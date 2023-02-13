/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 17:31:50 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/11 11:20:11 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	function_keys(int key, t_minirt *s)
{
	if (key == F2)
	{
		if (s->cam_param_display == 1)
			s->cam_param_display = 0;
		else
			s->cam_param_display = 1;
		display_scene(s);
	}
	else if (key == F1)
	{
		if (s->prompt_stat == 1)
		{
			s->prompt_stat = 0;
			s->prompt = NULL;
		}
		else if (s->prompt_stat == 0)
			s->prompt_stat = 1;
		push_img_to_win(s, PROMPT);
	}
}

void	movement_keys(int key, t_minirt *s)
{
	if (!s->hit_obj)
	{
		if (key == A)
			s->cam_origin.x -= INTERVAL;
		else if (key == S)
			s->cam_origin.z -= INTERVAL;
		else if (key == D)
			s->cam_origin.x += INTERVAL;
		else if (key == W)
			s->cam_origin.z += INTERVAL;
		else if (key == SPACE)
			s->cam_origin.y += INTERVAL;
		else if (key == BACKSP)
			s->cam_origin.y -= INTERVAL;
		else if (key == EIGHT)
			key_up_vec(&s->cam_vec_dir.y);
		else if (key == FOUR)
			key_down_vec(&s->cam_vec_dir.x);
		else if (key == FIVE)
			key_down_vec(&s->cam_vec_dir.y);
		else if (key == SIX)
			key_up_vec(&s->cam_vec_dir.x);
		else if (key == ONE)
			key_down_vec(&s->cam_vec_dir.z);
		else if (key == THREE)
			key_up_vec(&s->cam_vec_dir.z);
		
	}
	else if (s->hit_obj)
	{
		if (s->hit_obj->type == SPHERE)
		{
			if (key == A)
				s->hit_obj->u_.sp.center_axis.x -= INTERVAL;
			else if (key == S)
				s->hit_obj->u_.sp.center_axis.z -= INTERVAL;
			else if (key == D)
				s->hit_obj->u_.sp.center_axis.x += INTERVAL;
			else if (key == W)
				s->hit_obj->u_.sp.center_axis.z += INTERVAL;
			else if (key == SPACE)
				s->hit_obj->u_.sp.center_axis.y += INTERVAL;
			else if (key == BACKSP)
				s->hit_obj->u_.sp.center_axis.y -= INTERVAL;
		}
		else if (s->hit_obj->type == PLANE)
		{
			if (key == A)
				s->hit_obj->u_.pl.axis.x -= INTERVAL;
			else if (key == S)
				s->hit_obj->u_.pl.axis.z -= INTERVAL;
			else if (key == D)
				s->hit_obj->u_.pl.axis.x += INTERVAL;
			else if (key == W)
				s->hit_obj->u_.pl.axis.z += INTERVAL;
			else if (key == SPACE)
				s->hit_obj->u_.pl.axis.y += INTERVAL;
			else if (key == BACKSP)
				s->hit_obj->u_.pl.axis.y -= INTERVAL;
		}
		else if (s->hit_obj->type == CYLINDER)
		{
			if (key == A)
				s->hit_obj->u_.cy.center.x -= INTERVAL;
			else if (key == S)
				s->hit_obj->u_.cy.center.z -= INTERVAL;
			else if (key == D)
				s->hit_obj->u_.cy.center.x += INTERVAL;
			else if (key == W)
				s->hit_obj->u_.cy.center.z += INTERVAL;
			else if (key == SPACE)
				s->hit_obj->u_.cy.center.y += INTERVAL;
			else if (key == BACKSP)
				s->hit_obj->u_.cy.center.y -= INTERVAL;
		}
	}
}

int	key_press(int key, t_minirt *s)
{
	if (key == ESCAPE)
		red_cross(s);
	if (key == F1 || key == F2)
		function_keys(key, s);
	else if (is_key_move(key) && s->prompt_stat == 0)
	{
		movement_keys(key, s);
		display_scene(s);
	}
	else
		get_prompt(s, key);
	if (s->prompt_stat == 1)
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0x00FF00, "*");
	else
		mlx_string_put(s->mlx, s->win, 10, HEIGHT + 2, 0xF00020, "*");
	return (0);
}
