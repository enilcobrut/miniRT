#include "miniRT.h"

int hit_cylinder(t_cylinder *cyl, const t_rayon *r, t_hit_record *rec, double t_min, double t_max)
{
	double radius = cyl->diameter / 2;
	t_vector oc = sub_(r->origine, cyl->axis);
	double a = length_squared(r->direction) - pow(dot(r->direction, cyl->axis), 2);
	double half_b = dot(oc, r->direction) - dot(oc, cyl->axis) * dot(r->direction, cyl->axis);
	double c = length_squared(oc) - pow(dot(oc, cyl->axis), 2) - radius * radius;
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
	t_vector normal = sub_(rec->p, cyl->axis);
	normal = sub_(normal, mul_(cyl->axis, dot(normal, cyl->axis)));
	normal = vec3_unit_vector(normal);
	rec->normal = normal;
	rec->front_face = dot(r->direction, normal) < 0;
	if (!rec->front_face)
	rec->normal = mul_(rec->normal, -1);
	return (1);
}