/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjunker <cjunker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:31:50 by cjunker           #+#    #+#             */
/*   Updated: 2023/02/15 13:32:04 by cjunker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_bonus.h"

static void	register_hit(int *h, double *c, t_hit *tp, t_hit *rec)
{
	*h = 1;
	*c = tp->t;
	*rec = *tp;
}

int	hit_disk(t_disk *disk, const t_rayon *r, double t_max, t_hit *rec)
{
	double		t;
	t_vector	p;
	t_vector	distance;

	t = dot(sub_(disk->center, r->origine), disk->normal)
		/ dot(r->direction, disk->normal);
	if (t < T_MIN || t_max < t)
		return (0);
	p = add_(r->origine, mul_(r->direction, t));
	distance = sub_(p, disk->center);
	if (vec3_length(distance) > disk->radius)
		return (0);
	rec->t = t;
	rec->p = p;
	set_face_normal(r, rec, disk->normal);
	return (1);
}

int	hit_cylinder2(t_cylinder *cyl, const t_rayon *r, t_hit *rec, double root)
{
	t_vector	p;
	t_vector	normal;
	double		v;

	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	p = sub_(rec->p, cyl->center);
	v = dot(p, cyl->dir_ax);
	if (v < 0 || cyl->height < v)
		return (1);
	normal = sub_(rec->p, cyl->center);
	normal = sub_(normal, mul_(cyl->dir_ax, dot(normal, cyl->dir_ax)));
	normal = div_(normal, cyl->radius);
	set_face_normal(r, rec, normal);
	return (0);
}

int	hit_cyl_body(t_cylinder *cyl, const t_rayon *r, t_hit *rec, double t_max)
{
	t_vector	oc;
	t_quadra	qe;
	double		root;

	oc = sub_(r->origine, cyl->center);
	qe.a = length_squared(r->direction)
		- pow(dot(r->direction, cyl->dir_ax), 2);
	qe.half_b = dot(oc, r->direction)
		- dot(oc, cyl->dir_ax) * dot(r->direction, cyl->dir_ax);
	qe.c = length_squared(oc) - pow(dot(oc, cyl->dir_ax), 2)
		- cyl->radius * cyl->radius;
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
	if (hit_cylinder2(cyl, r, rec, root))
		return (0);
	return (1);
}

int	hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit *rec, double t_max)
{
	int				hit;
	double			c;
	t_hit			tp;
	int				t;
	t_disk			disk;

	c = t_max;
	hit = 0;
	disk.center = cyl->center;
	disk.normal = cyl->dir_ax;
	disk.radius = cyl->radius;
	t = hit_disk(&disk, r, c, &tp);
	if (t)
		register_hit(&hit, &c, &tp, rec);
	disk.center = add_(cyl->center, mul_(cyl->dir_ax, cyl->height));
	t = hit_disk(&disk, r, c, &tp);
	if (t)
		register_hit(&hit, &c, &tp, rec);
	t = hit_cyl_body(cyl, r, &tp, c);
	if (t)
		register_hit(&hit, &c, &tp, rec);
	return (hit);
}
