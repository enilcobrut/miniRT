/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_cam_mov.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:51:00 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 20:51:08 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_cam_or(t_minirt *s, int key)
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
}

void	move_cam_vec(t_minirt *s, int key)
{
	if (key == EIGHT)
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
