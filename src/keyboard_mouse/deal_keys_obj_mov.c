/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_obj_mov.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:50:28 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 20:50:29 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_sp_or(t_minirt *s, int key)
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

void	move_pl_or(t_minirt *s, int key)
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

void	move_pl_vec(t_minirt *s, int key)
{
	if (key == FOUR)
		s->hit_obj->u_.pl.dir_ax.x -= INTERVAL_VEC;
	else if (key == SIX)
		s->hit_obj->u_.pl.dir_ax.x += INTERVAL_VEC;
	else if (key == EIGHT)
		s->hit_obj->u_.pl.dir_ax.z += INTERVAL_VEC;
	else if (key == FIVE)
		s->hit_obj->u_.pl.dir_ax.z -= INTERVAL_VEC;
	else if (key == ONE)
		s->hit_obj->u_.pl.dir_ax.y -= INTERVAL_VEC;
	else if (key == THREE)
		s->hit_obj->u_.pl.dir_ax.y += INTERVAL_VEC;
}
