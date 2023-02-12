#include "miniRT_bonus.h"

int	hit_disk(t_vector center, t_vector normal, double radius, const t_rayon *r, double t_min, double t_max, t_hit_record *rec)
{
	double		t;
	t_vector	p;
	t_vector	distance;

	t = dot(sub_(center, r->origine), normal) / dot(r->direction, normal);
	if (t < t_min || t_max < t)
		return (0);
	p = add_(r->origine, mul_(r->direction, t));
	distance = sub_(p, center);
	if (vec3_length(distance) > radius)
		return (0);
	rec->t = t;
	rec->p = p;
	set_face_normal(r, rec, normal);
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

int	hit_cylinder_body(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
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
	if (root < t_min || t_max < root)
	{
		root = (-qe.half_b + sqrt(qe.delta)) / qe.a;
		if (root < t_min || t_max < root)
			return (0);
	}
	if (hit_cylinder_body_next(cyl, r, rec, root))
		return (0);
	return (1);
}

int hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	int				hit_anything;
	double			closest_so_far;
	t_hit_record	temp_rec;
	int				t;

	closest_so_far = t_max;
	hit_anything = 0;
	t = hit_disk(cyl->center, cyl->dir_ax, cyl->radius, r, t_min, closest_so_far, &temp_rec);
	if (t)
	{
		hit_anything = 1;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
	t = hit_disk(add_(cyl->center, mul_(cyl->dir_ax, cyl->height)), cyl->dir_ax, cyl->radius, r, t_min, closest_so_far, &temp_rec);
	if (t)
	{
		hit_anything = 1;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
	t = hit_cylinder_body(cyl, r, &temp_rec, t_min, closest_so_far);
	if (t)
	{
		hit_anything = 1;
		closest_so_far = temp_rec.t;
		*rec = temp_rec;
	}
	return (hit_anything);
}

