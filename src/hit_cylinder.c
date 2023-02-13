#include "miniRT.h"

int	hit_disk(t_disk *d, const t_rayon *r, double t_max, t_hit_record *rec)
{
	double		t;
	t_vector	p;
	t_vector	distance;

	t = dot(sub_(d->center, r->origine), d->normal) / dot(r->direction, d->normal);
	if (t < T_MIN || t_max < t)
		return (0);
	p = add_(r->origine, mul_(r->direction, t));
	distance = sub_(p, d->center);
	if (vec3_length(distance) > d->radius)
		return (0);
	rec->t = t;
	rec->p = p;
	set_face_normal(r, rec, d->normal);
	return (1);
}

int	hit_cylinder_body_next(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double root)
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

int	hit_cylinder_body(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_max)
{
	t_vector				oc;
	t_quadratic_equation	qe;
	double					root;

	oc = sub_(r->origine, cyl->center);
	qe.a = length_squared(r->direction) - pow(dot(r->direction, cyl->dir_ax), 2);
	qe.half_b = dot(oc, r->direction) - dot(oc, cyl->dir_ax) * dot(r->direction, cyl->dir_ax);
	qe.c = length_squared(oc) - pow(dot(oc, cyl->dir_ax), 2) - cyl->radius * cyl->radius;
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
	if (hit_cylinder_body_next(cyl, r, rec, root))
		return (0);
	return (1);
}

int hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_max)
{
	int				hit_anything;
	double			closest_so_far;
	t_hit_record	temp_rec;
	t_disk			d;

	closest_so_far = t_max;
	d.center = cyl->center;
	d.normal = cyl->dir_ax;
	d.radius = cyl->radius;
	if (hit_disk(&d, r, closest_so_far, &temp_rec))
	{
		hit_anything = 1;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
	d.center = add_(cyl->center, mul_(cyl->dir_ax, cyl->height));
	d.normal = cyl->dir_ax;
	d.radius = cyl->radius;
	if (hit_disk(&d, r, closest_so_far, &temp_rec))
	{
		hit_anything = 1;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
	if (hit_cylinder_body(cyl, r, &temp_rec, closest_so_far))
	{
		hit_anything = 1;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
	return (hit_anything);
}

