/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flemaitr <flemaitr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 11:04:43 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 19:12:21 by flemaitr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit_plane(t_plane *p, const t_rayon *r, t_hit *rec, double t_max)
{
	t_vector	norm;
	double		t;

	norm = norm_(p->dir_ax);
	t = dot(norm, sub_(p->axis, r->origine)) / dot(norm, r->direction);
	if (t < T_MIN || t > t_max)
		return (0);
	rec->t = t;
	rec->p = add_(r->origine, mul_(r->direction, t));
	rec->normal = norm;
	rec->front_face = dot(r->direction, rec->normal) < 0;
	if (!rec->front_face)
		rec->normal = mul_(rec->normal, -1);
	return (1);
}
