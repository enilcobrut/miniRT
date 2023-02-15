/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cone_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:50:10 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 14:13:30 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	register_hit(int *h, double *c, t_hit *tp, t_hit *rec)
{
	*h = 1;
	*c = tp->t;
	*rec = *tp;
}

static void	init_quadra_value(t_quadra	*qe, t_cone *cone, const t_rayon *r)
{
	t_vector				oc;

	oc = sub_(r->origine, cone->center);
	qe->k = cone->tan_angle * cone->tan_angle;
	qe->a = length_squared(r->direction) - (1.0 + qe->k)
		* dot(r->direction, cone->dir_ax) * dot(r->direction, cone->dir_ax);
	qe->half_b = dot(oc, r->direction)
		- (1.0 + qe->k) * dot(oc, cone->dir_ax)
		* dot(r->direction, cone->dir_ax);
	qe->c = length_squared(oc)
		- (1.0 + qe->k) * dot(oc, cone->dir_ax) * dot(oc, cone->dir_ax);
	qe->delta = qe->half_b * qe->half_b - qe->a * qe->c;
}

int	check_soluce(t_quadra *qe, double t_max, const t_rayon *r, t_hit *rec)
{
	double	sqrtd;
	double	root;

	if (qe->delta < 0)
		return (0);
	sqrtd = sqrt(qe->delta);
	root = (-qe->half_b - sqrtd) / qe->a;
	if (root < T_MIN || t_max < root)
	{
		root = (-qe->half_b + sqrtd) / qe->a;
		if (root < T_MIN || t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	return (1);
}

int	hit_cone_body(t_cone *cone, const t_rayon *r, t_hit *rec, double t_max)
{
	t_quadra	qe;
	double		d;
	double		v;
	t_vector	p;
	t_vector	normal;

	init_quadra_value(&qe, cone, r);
	if (!check_soluce(&qe, t_max, r, rec))
		return (0);
	p = sub_(rec->p, cone->center);
	v = dot(p, cone->dir_ax);
	if (v < 0 || cone->height < v)
		return (0);
	d = vec3_length(p) * cone->tan_angle;
	if (d * d > v * v && cone->tan_angle < 1)
		return (0);
	normal = sub_(p, mul_(cone->dir_ax, v));
	normal = div_(normal, d);
	set_face_normal(r, rec, normal);
	return (1);
}

int	hit_cone(t_cone *cone, const t_rayon *r, t_hit *rec, double t_max)
{
	int		hit;
	double	c;
	t_hit	tp;
	int		t;
	t_disk	disk;

	disk.center = add_(cone->center, mul_(cone->dir_ax, cone->height));
	disk.normal = cone->dir_ax;
	disk.radius = cone->radius;
	hit = 0;
	c = t_max;
	t = hit_disk(&disk, r, c, &tp);
	if (t)
		register_hit(&hit, &c, &tp, rec);
	t = hit_cone_body(cone, r, &tp, c);
	if (t)
		register_hit(&hit, &c, &tp, rec);
	return (hit);
}
