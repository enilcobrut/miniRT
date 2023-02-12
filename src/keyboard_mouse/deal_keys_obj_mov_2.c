/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_keys_obj_mov_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:50:15 by flemaitr          #+#    #+#             */
/*   Updated: 2023/02/12 20:50:17 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	move_cy_or(t_minirt *s, int key)
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

void	move_cy_vec(t_minirt *s, int key)
{
	if (key == FOUR)
		s->hit_obj->u_.cy.dir_ax.x -= INTERVAL_VEC;
	else if (key == SIX)
		s->hit_obj->u_.cy.dir_ax.x += INTERVAL_VEC;
	else if (key == EIGHT)
		s->hit_obj->u_.cy.dir_ax.z += INTERVAL_VEC;
	else if (key == FIVE)
		s->hit_obj->u_.cy.dir_ax.z -= INTERVAL_VEC;
	else if (key == ONE)
		s->hit_obj->u_.cy.dir_ax.y -= INTERVAL_VEC;
	else if (key == THREE)
		s->hit_obj->u_.cy.dir_ax.y += INTERVAL_VEC;
	s->hit_obj->u_.cy.dir_ax = vec3_unit_vector(s->hit_obj->u_.cy.dir_ax);
}
