/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:33:26 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:33:28 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit *rec, double t_max)
{
	t_vector	oc;
	t_quadra	qe;
	double		root;

	oc = sub_(r->origine, sp->center_axis);
	qe.a = length_squared(r->direction);
	qe.half_b = dot(oc, r->direction);
	qe.c = length_squared(oc) - sp->radius * sp->radius;
	qe.delta = qe.half_b * qe.half_b - qe.a * qe.c;
	if (qe.delta < 0)
		return (0);
	root = (-qe.half_b - sqrt(qe.delta)) / qe.a;
	if (root < T_MIN || t_max < root)
	{
		root = (-qe.half_b + sqrt(qe.delta)) / qe.a;
		if (root < T_MIN || t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	set_face_normal(r, rec, div_(sub_(rec->p, sp->center_axis), sp->radius));
	return (1);
}
