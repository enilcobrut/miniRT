#include "miniRT_bonus.h"

int hit_cone_body(t_cone *cone, const t_rayon *r, t_hit *rec, double t_max)
{
  //  cone->dir_ax = mul_(cone->dir_ax, -1);
	t_vector oc = sub_(r->origine, cone->center);
	double k = cone->tan_angle * cone->tan_angle;
	double a = length_squared(r->direction) - (1.0 + k) * dot(r->direction, cone->dir_ax) * dot(r->direction, cone->dir_ax);
	double half_b = dot(oc, r->direction) - (1.0 + k) * dot(oc, cone->dir_ax) * dot(r->direction, cone->dir_ax);
	double c = length_squared(oc) - (1.0 + k) * dot(oc, cone->dir_ax) * dot(oc, cone->dir_ax);
	double delta = half_b * half_b - a * c;
	if (delta < 0)
		return (0);
	double sqrtd = sqrt(delta);
	double root = (-half_b - sqrtd) / a;
	if (root < T_MIN || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < T_MIN || t_max < root)
			return (0);
	}
	rec->t = root;
	rec->p = add_(r->origine, mul_(r->direction, rec->t));
	t_vector p = sub_(rec->p, cone->center);
	double v = dot(p, cone->dir_ax);
	if (v < 0 || cone->height < v)
		return (0);
	double d = vec3_length(p) * cone->tan_angle;
	if (d * d > v * v)
		return (0);
	t_vector normal = sub_(p, mul_(cone->dir_ax, v));
	normal = div_(normal, d);
	set_face_normal(r, rec, normal);
	return (1);
}

int hit_cone(t_cone *cone, const t_rayon *r, t_hit *rec, double t_max)
{
    int				hit_anything;
	double			c;
	t_hit	tp;
	int				t;
	
	hit_anything = 0;
	c = t_max;
	t = hit_disk(add_(cone->center, mul_(cone->dir_ax, cone->height)), cone->dir_ax, cone->radius, r, c, &tp);
    if (t)
    {
        hit_anything = 1;
        c = tp.t;
        *rec = tp;
    }
    t = hit_cone_body(cone, r, &tp, c);
    if (t)
    {
        hit_anything = 1;
        c = tp.t;
        *rec = tp;
    }
    return (hit_anything);
}