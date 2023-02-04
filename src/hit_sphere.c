#include "miniRT.h"

int	hit_sphere(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector oc = sub_(r->origine, sp->center_axis);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) -  sp->radius *  sp->radius;
	double delta = half_b*half_b - a*c;
	if (delta < 0)
		return (0);
	double sqrtd = sqrt(delta);
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	set_face_normal(r, rec, div_(sub_(rec->p, sp->center_axis), sp->radius));
	//rec->normal = div_(sub_(rec->p, sp->center_axis), sp->radius);
	return (1);
}

int	hit_sphere_2(t_sphere *sp, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector oc = sub_(r->origine, sp->center_axis);
	double a = length_squared(r->direction);
	double half_b = dot(oc, r->direction);
	double c = length_squared(oc) -  sp->radius *  sp->radius;
	double delta = half_b*half_b - a*c;
	if (delta < 0)
		return (0);
	double sqrtd = sqrt(delta);
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	//set_face_normal(r, rec, div_(sub_(rec->p, sp->center_axis), sp->radius));
	//rec->normal = div_(sub_(rec->p, sp->center_axis), sp->radius);
	return (1);
}