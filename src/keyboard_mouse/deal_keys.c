/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:51:40 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 20:51:53 by flemaitr         ###   ########.fr       */
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
			s->hit_obj = NULL;
			ft_free(&s->prompt);
			s->prompt = NULL;
		}
		else if (s->prompt_stat == 0)
			s->prompt_stat = 1;
		push_img_to_win(s, PROMPT);
	}
}

void	move_cam_or_obj(t_minirt *s, int key)
{
	if (!s->hit_obj)
	{
		move_cam_or(s, key);
		move_cam_vec(s, key);
	}
	else if (s->hit_obj)
	{
		if (s->hit_obj->type == SPHERE)
			move_sp_or(s, key);
		else if (s->hit_obj->type == PLANE)
		{
			move_pl_or(s, key);
			move_pl_vec(s, key);
		}
		else if (s->hit_obj->type == CYLINDER)
		{
			move_cy_or(s, key);
			move_cy_vec(s, key);
		}
	}
}

int	key_press(int key, t_minirt *s)
{
	if (key == ESCAPE)
		red_cross(s);
	else if (key == F1 || key == F2)
		function_keys(key, s);
	else if (is_key_move(key) && s->prompt_stat == 0)
	{
		move_cam_or_obj(s, key);
		display_scene(s);
	}
	else if (s->prompt_stat == 1)
		get_prompt(s, key);
	return (0);
}
