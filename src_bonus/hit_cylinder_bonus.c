#include "miniRT_bonus.h"




int hit_disk(t_vector center, t_vector normal, double radius, const t_rayon *r, double t_min, double t_max, t_hit_record *rec)
{
    double t = dot(sub_(center, r->origine), normal) / dot(r->direction, normal);
    if (t < t_min || t_max < t)
        return (0);
    t_vector p = add_(r->origine, mul_(r->direction, t));
    t_vector distance = sub_(p, center);
    if (vec3_length(distance) > radius)
        return (0);
    rec->t = t;
    rec->p = p;
    set_face_normal(r, rec, normal);
    return (1);
}


int hit_cylinder_body(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	t_vector oc = sub_(r->origine, cyl->center);
	double a = length_squared(r->direction) - pow(dot(r->direction, cyl->dir_ax), 2);
	double half_b = dot(oc, r->direction) - dot(oc, cyl->dir_ax) * dot(r->direction, cyl->dir_ax);
	double c = length_squared(oc) - pow(dot(oc, cyl->dir_ax), 2) - cyl->radius * cyl->radius;
	double delta = half_b * half_b - a * c;
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
	t_vector p = sub_(rec->p, cyl->center);
	double v = dot(p, cyl->dir_ax);
	if (v < 0 || cyl->height < v)
		return (0);
	t_vector normal = sub_(rec->p, cyl->center);
	normal = sub_(normal, mul_(cyl->dir_ax, dot(normal, cyl->dir_ax)));
	normal = div_(normal, cyl->radius);
	set_face_normal(r, rec, normal);
	return (1);
}

int hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	int	hit_anything = 0;
	double closest_so_far = t_max;
	t_hit_record temp_rec;

	int t = hit_disk(cyl->center, cyl->dir_ax, cyl->radius, r, t_min, closest_so_far, &temp_rec);
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

